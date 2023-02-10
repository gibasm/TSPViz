#include "crossover.hpp"
#include <cassert>
#include <random>
#include <memory>
#include <algorithm>

static std::random_device r;
static std::mt19937 e(r());

static Phenotype get_ox_child(const Phenotype& parent_a, const Phenotype& parent_b, size_t start, size_t end);

std::vector<Phenotype> OXCrossover::crossover(const std::vector<Phenotype>& parents) {
    /* this OX crossover implementation works only for 2 parents! */
    assert(parents.size() == 2UL);
    size_t genome_length = parents.at(0).get_genome().size();

    /* choose the points of crossover randomly */
    std::uniform_int_distribution<size_t> dist(0UL, genome_length);
    size_t start = dist(e), end = dist(e);
    
    if(start > end) {
        std::swap(start, end);
    }
    
    std::vector<Phenotype> children;
    children.push_back(get_ox_child(parents.at(0), parents.at(1), start, end));
    children.push_back(get_ox_child(parents.at(1), parents.at(0), start, end));

    return children;
} 

Phenotype get_ox_child(const Phenotype& parent_a, const Phenotype& parent_b, size_t start, size_t end) {
    size_t genome_length = parent_a.get_genome().size();

    /* create an array indicating the already passed genes */
    std::unique_ptr<bool[]> used = std::make_unique<bool[]>(genome_length);


    for(size_t i = 0; i < genome_length; ++i) {
        used[i] = false;
    }

    /* create a child's genome */
    std::vector<size_t> child_genome;
    child_genome.resize(genome_length);

    /* pass the genes of the first parent between the points of crossover */
    for(size_t i = start; i < end; ++i) {
        child_genome[i] = parent_a.get_genome().at(i);
        used[parent_a.get_genome().at(i)] = true;
    }

    /* pass the rest of the genes from the second parent */
    size_t child_gene_index = 0;
    size_t parent_gene_index = 0;
    
    while((child_gene_index < genome_length) 
        && (parent_gene_index < genome_length)) {
        
        /* if the child_gene_index moves to the part of 
           the genome from the parent_a, skip the part */
        if((child_gene_index >= start) && (child_gene_index < end)) {
            child_gene_index = end;
        }

        size_t gene = parent_b.get_genome().at(parent_gene_index);
        /* if the gene at parent_gene_index is not present in the child pass it over */
        if(!used[gene]) {
            child_genome[child_gene_index] = gene;
            used[gene] = true;
            ++child_gene_index;
        }

        /* move to the next gene of the parent_b */
        ++parent_gene_index;
    } /* while */

    return Phenotype(child_genome);
}