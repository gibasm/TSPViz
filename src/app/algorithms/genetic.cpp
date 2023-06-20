#include "genetic.hpp"
#include <cstdlib>
#include <random>
#include <chrono>
#include <thread>
#include <list>
#include <algorithm>
#include <spdlog/spdlog.h>
#include <cassert>

#include "../util/perf_clock.hpp"

extern PerfClock perf_clock;

static std::random_device r;
static std::mt19937 e(r());

bool ga_stop = false;

GeneticAlgorithm::GeneticAlgorithm(TSPInstance& instance, Graph& graph)
:TSPSolver(instance, graph) {
    assert(n_threads > 2UL);
}

void GeneticAlgorithm::solve() {
    spdlog::debug("Running genetic algorithm...");
    spdlog::debug("Iterations: {}", max_iterations);
    spdlog::debug("Population size: {}", population_size);
    spdlog::debug("Mutation probability: {}", p_mutation);

    /* generate a new random population */
    generate_population();
    
    /* choose a random best path at first*/
    select_best_path(population.at(0).get_genome());
    global_best_cost = INFINITY;

    selected = std::make_unique<bool[]>(population_size);
    costs = std::make_unique<float[]>(population_size);
    
    double total_time_ms = 0.0;

    for(size_t iteration = 0; iteration < max_iterations; ++iteration) {
        if(ga_stop) break;
        
        perf_clock.start();

        rate_individuals();
        select_parents();
        crossover();
        mutate();

        perf_clock.stop();
        total_time_ms += perf_clock.get_time_delta_ms();

        std::this_thread::sleep_for(std::chrono::milliseconds(iteration_delay_ms));
        spdlog::debug("iteration #{} (best path cost: {})", iteration+1, global_best_cost);
    }

    spdlog::info("Best path cost found: {}", global_best_cost);
    spdlog::info("Total time of execution: {0:.2f}ms", total_time_ms);
    spdlog::debug("Job finished");
}

GeneticAlgorithm::GeneticAlgorithm(const GeneticAlgorithm& other) 
:TSPSolver(other.instance, other.graph), population_size(other.population_size), max_iterations(other.max_iterations),
p_mutation(other.p_mutation), mutator(other.mutator),
crossover_method(other.crossover_method) {

}

void GeneticAlgorithm::generate_population() {
    if(population.size() > 0) {
        population.clear();
    }

    population.reserve(population_size);

    for(size_t i = 0; i < population_size; ++i) {
        /* create the randomly shuffled genome */
        std::vector<size_t> genome;
        genome.resize(instance.get_vertex_count());

        std::iota(genome.begin(), genome.end(), 0);

        std::shuffle(genome.begin(), genome.end(), e);
        
        population.push_back(genome);
    }
}

void GeneticAlgorithm::rate_individuals() {
    for(size_t i = 0; i < population_size; ++i) {
        costs[i] = population.at(i).get_cost(instance.get_neighborhood_matrix());

        if(costs[i] < global_best_cost) {
            select_best_path(population.at(i).get_genome());
            global_best_cost = costs[i];
        }
    }
}

/* TODO: implement other selection methods */
void GeneticAlgorithm::select_parents() {
    /* empty the mating_pool */ 
    while(!this->mating_pool.empty()) {
        this->mating_pool.pop();
    }

    /* fill the selected[] array with flase values */
    std::fill(selected.get(), selected.get() + population_size, false);

    /* tournament-like selection */
    std::uniform_int_distribution<size_t> dist(0, population_size-1);

    /* choose (population/2) individuals */
    while(this->mating_pool.size() < ((population_size / 2UL) + 1UL)) {
        size_t k = dist(e);

        /* for k random individuals, choose the best */
        float best_cost = INFINITY;
        size_t best_index = 0;
        
        for(size_t j = 0; j < k; ++j) {
            size_t generated_index;

            do {
                generated_index = dist(e);
            } while(selected[generated_index]);
            
            if(costs[generated_index] < best_cost) {
                best_index = generated_index;
                best_cost = costs[generated_index];
            }
        }

        mating_pool.push(population.at(best_index));

        /* mark found individual as selected */
        selected[best_index] = true;
    } 
}

void GeneticAlgorithm::crossover() {
    population.clear();
 
    const auto crossover_thread_func = [&] () {
        while(this->mating_pool.size() >= 2UL) {

            this->mating_pool_mtx.lock();
            // check if there are still any parents in the mating pool
            if(this->mating_pool.size() >= 2UL) {

                auto parentA = this->mating_pool.front();
                this->mating_pool.pop();
                
                auto parentB = this->mating_pool.front();
                // we don't pop the parentB because we want to leave it in the mating pool for now
                auto children = this->crossover_method->crossover({parentA, parentB});

                this->mating_pool_mtx.unlock();

                for(auto child : children) {
                    this->population.push_back(child);
                }
            } else {
                this->mating_pool_mtx.unlock();
            }
        }
    };

    for(size_t i = 0; i < n_threads - 2UL; ++i) {
        std::thread(crossover_thread_func).join();
    }

    while(this->mating_pool.size() >= 2UL) { asm volatile ("nop"); }
}

void GeneticAlgorithm::mutate() {
    this->mutation_no = 0;
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    const auto mutation_thread_func = [&] () {
        while(this->mutation_no < population_size) {
            this->mutation_no_mtx.lock();
            unsigned i = this->mutation_no;
            ++(this->mutation_no);
            this->mutation_no_mtx.unlock();
            
            /* choose to mutate an individual with p_mutate probability */
            if(dist(e) <= p_mutation) {
                population.at(i).mutate(*mutator);
            }
        }
        
        this->mutation_no_mtx.unlock();
    };
    
    for(size_t i = 0; i < n_threads - 2UL; ++i) {
        std::thread(mutation_thread_func).join();
    }

    while(this->mutation_no < population_size) { asm volatile ("nop"); }
}

void GeneticAlgorithm::select_best_path(const std::vector<size_t>& new_best) {
    /* change the color of the previous best path back to normal */
    for(size_t i = 0; i < best_path.size(); ++i) {
        graph.highlight_edge(best_path.at(i), best_path.at(((i+1) % best_path.size())), false);
    }

    best_path = new_best;

    /* change the color of the next best path as highlighted */
    for(size_t i = 0; i < best_path.size(); ++i) {
        graph.highlight_edge(best_path.at(i), best_path.at(((i+1) % best_path.size())));
    }
}
