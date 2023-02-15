#include "ga_builder.hpp"
#include <stdexcept>


GeneticAlgorithmBuilder GeneticAlgorithmBuilder::builder = GeneticAlgorithmBuilder();

GeneticAlgorithmBuilder& GeneticAlgorithmBuilder::with() {
    return builder;
}

GeneticAlgorithmBuilder::GeneticAlgorithmBuilder() {}

GeneticAlgorithmBuilder& GeneticAlgorithmBuilder::crossover_type(CrossoverType type) {
    switch(type) {
        case CrossoverType::OX:{
            this->crossover_strategy = std::make_shared<OXCrossover>();
            break;
        }
        case CrossoverType::PMX:
        default: {
            throw std::runtime_error("This type of crossover is not yet supported!");
            break;
        }
    }

    return *this;
}

GeneticAlgorithmBuilder& GeneticAlgorithmBuilder::mutation_type(MutationType type) {
    switch(type) {
        case MutationType::SWAP:{
            this->mutator = std::make_shared<SwapMutator>();
            break;
        }
        case MutationType::INVERT:{
            this->mutator = std::make_shared<InvertMutator>();
            break;
        }
        case MutationType::INSERT:
        default: {
            throw std::runtime_error("This type of mutation is not yet supported!");
        }
    }
    return *this;
}

GeneticAlgorithmBuilder& GeneticAlgorithmBuilder::max_iterations(size_t max_iterations) {
    if(max_iterations == 0) {
        throw std::runtime_error("Max number of iterations should be > 0!");
    }
    this->_max_iterations = max_iterations;

    return *this;
}

GeneticAlgorithmBuilder& GeneticAlgorithmBuilder::population_size(size_t population_size) {
    if(population_size == 0) {
        throw std::runtime_error("Population size should be a number > 0!");
    }
    this->_population_size = population_size;

    return *this;
}

GeneticAlgorithmBuilder& GeneticAlgorithmBuilder::instance(TSPInstance& instance) {
    this->instance_ptr = &instance;
    return *this;
}

GeneticAlgorithmBuilder& GeneticAlgorithmBuilder::graph(Graph& graph) {
    this->graph_ptr = &graph;
    return *this;
}

GeneticAlgorithmBuilder& GeneticAlgorithmBuilder::mutation_probability(float p_mutation) {
    if((p_mutation < 0.0f) || (p_mutation > 1.0f)) {
        throw std::runtime_error("Mutation probability should be a number in range [0.0, 1.0]");
    }

    this->p_mutation = p_mutation;
    return *this;
}

std::unique_ptr<GeneticAlgorithm> GeneticAlgorithmBuilder::build() {
    algorithm = std::make_unique<GeneticAlgorithm>(*instance_ptr, *graph_ptr);
    algorithm->crossover_method = crossover_strategy;
    algorithm->mutator = mutator;
    algorithm->max_iterations = _max_iterations;
    algorithm->population_size = _population_size;
    algorithm->p_mutation = p_mutation;

    return std::move(algorithm);
}