#ifndef GA_BUILDER_HPP
#define GA_BUILDER_HPP

#include "genetic.hpp"

enum CrossoverType {
    OX,
    PMX
};

enum MutationType {
    SWAP,
    INVERT,
    INSERT
};

class GeneticAlgorithmBuilder;

class GeneticAlgorithmBuilder {
public:
    GeneticAlgorithmBuilder();
    virtual ~GeneticAlgorithmBuilder() = default;

    static GeneticAlgorithmBuilder& with();

    GeneticAlgorithmBuilder& crossover_type(CrossoverType type);
    GeneticAlgorithmBuilder& mutation_type(MutationType type);
    GeneticAlgorithmBuilder& max_iterations(size_t max_iterations);
    GeneticAlgorithmBuilder& population_size(size_t population_size);
    GeneticAlgorithmBuilder& instance(TSPInstance& instance);
    GeneticAlgorithmBuilder& graph(Graph& graph);
    GeneticAlgorithmBuilder& mutation_probability(float p_mutation);

    std::unique_ptr<GeneticAlgorithm> build();
private:
    static GeneticAlgorithmBuilder builder;

    std::shared_ptr<CrossoverStrategy> crossover_strategy;
    std::shared_ptr<Mutator> mutator;
    
    size_t _max_iterations;
    size_t _population_size;
    
    TSPInstance* instance_ptr;
    Graph* graph_ptr;
    
    float p_mutation;

    std::unique_ptr<GeneticAlgorithm> algorithm;
};

#endif /* GA_BUILDER_HPP */