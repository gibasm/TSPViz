#ifndef GENETIC_HPP
#define GENETIC_HPP

#include "tsp_solver.hpp"
#include "mutator.hpp"
#include "crossover.hpp"

class GeneticAlgorithm :public TSPSolver {
public:
    GeneticAlgorithm(TSPInstance& instance, Graph& graph);
    GeneticAlgorithm(const GeneticAlgorithm& other);
    virtual ~GeneticAlgorithm() = default;

    inline void set_iteration_delay_ms(unsigned int ms) { iteration_delay_ms = ms; }

    virtual void solve() override;

private:
    void rate_individuals();
    void generate_population();
    void select_parents();
    void crossover();
    void mutate();

    void select_best_path(const std::vector<size_t>& new_best);

    size_t population_size, max_iterations;
    float p_mutation;
    std::shared_ptr<Mutator> mutator;
    std::shared_ptr<CrossoverStrategy> crossover_method;
    
    std::unique_ptr<bool[]> selected;
    std::vector<Phenotype> population;
    std::vector<Phenotype> parents;

    std::vector<size_t> best_path;

    std::unique_ptr<float[]> costs;

    float global_best_cost;

    unsigned iteration_delay_ms = 0;

    friend class GeneticAlgorithmBuilder;
};

#endif /* GENETIC_HPP */