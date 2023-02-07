#include "phenotype.hpp"

float Phenotype::get_cost(GraphMatrix distances) {
    float cost = 0.0f;
    for(size_t i = 0; i < genome.size(); ++i) {
        cost += distances
            .at(genome.at( i ))
            .at(genome.at( (i+1) % genome.size() ));
    }

    return cost;
}

Phenotype::Phenotype(std::vector<size_t> genome)
:genome(genome){}

Phenotype::~Phenotype() {}