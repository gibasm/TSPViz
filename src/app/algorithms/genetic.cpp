#include "genetic.hpp"
#include <random>
#include <chrono>
#include <thread>
#include <list>
#include <algorithm>
#include <spdlog/spdlog.h>

static std::random_device r;
static std::mt19937 e(r());

bool ga_stop = false;

GeneticAlgorithm::GeneticAlgorithm(TSPInstance& instance, Graph& graph)
:TSPSolver(instance, graph) {}

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

    for(size_t iteration = 0; iteration < max_iterations; ++iteration) {
        if(ga_stop) break;

        rate_individuals();
        select_parents();
        crossover();
        mutate();


        std::this_thread::sleep_for(std::chrono::milliseconds(iteration_delay_ms));
        spdlog::debug("iteration #{} (best path cost: {})", iteration+1, global_best_cost);
    }

    spdlog::debug("Best path cost found: {}", global_best_cost);
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
    /* clear the parents vector */
    parents.clear();
    /* fill the selected[] array with flase values */
    std::fill(selected.get(), selected.get() + population_size, false);

    /* tournament-like selection */
    std::uniform_int_distribution<size_t> dist(0, population_size-1);

    /* choose (population/2) individuals */
    for(size_t i = 0; i < (population_size/2); ++i) {
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

        parents.push_back(population.at(best_index));

        /* mark found individual as selected */
        selected[best_index] = true;
    } 
}

void GeneticAlgorithm::crossover() {
    population.clear();

    for(size_t i = 0; i < (population_size / 2); ++i) {
        auto children = crossover_method->crossover({
            parents.at(i % (population_size / 2)), 
            parents.at( (i+1) % (population_size / 2) )
        });
        
        for(auto child : children) {
            population.push_back(child);
        }
    }
}

void GeneticAlgorithm::mutate() {
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    for(size_t i = 0; i < population_size; ++i) {
        /* choose to mutate an individual with p_mutate probability */
        if(dist(e) <= p_mutation) {
            population.at(i).mutate(*mutator);
        }
    }
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