#include "solver_factory.hpp"
#include "ga_builder.hpp"
#include <algorithm>
#include <stdexcept>

static const std::map<std::string, MutationType> STR_MUTATIONS{
    {"SWAP", MutationType::SWAP},
    {"INVERT", MutationType::INVERT},
    {"INSERT", MutationType::INSERT}
};

static const std::map<std::string, CrossoverType> STR_CROSSOVERS{
    {"OX", CrossoverType::OX},
    {"PMX", CrossoverType::PMX}
};

std::unique_ptr<TSPSolver> TSPSolverFactory::create(
    TSPInstance& instance, Graph& graph, 
    const Dictionary& ini_contents) {

    
    
    if(ini_contents.at("algorithm_type").compare("GA") == 0) {
        return create_ga(instance, graph, ini_contents);
    }

    throw std::runtime_error("Unknown algorithm type");
}

CrossoverType str_to_crossover_type(const std::string& str);
MutationType str_to_mutation_type(const std::string& str);

std::unique_ptr<TSPSolver> TSPSolverFactory::create_ga(
        TSPInstance& instance, Graph& graph,
        const Dictionary& ini) {

    return GeneticAlgorithmBuilder::with()
            .instance(instance)
            .graph(graph)
            .crossover_type(STR_CROSSOVERS.at(ini.at("crossover_method")))
            .mutation_type(STR_MUTATIONS.at(ini.at("mutation_method")))
            .max_iterations(std::atoi(ini.at("iterations").c_str()))
            .mutation_probability(std::atof(ini.at("p_mutation").c_str()))
            .population_size(std::atoi(ini.at("population_size").c_str()))
        .build();
}