#ifndef PHENOTYPE_HPP
#define PHENOTYPE_HPP

#include "mutator.hpp"
#include "../instance.hpp"

class Phenotype {
public:
    Phenotype(std::vector<size_t> genome);
    virtual ~Phenotype();

    float get_cost(GraphMatrix distances);
    
    inline void mutate(const Mutator& mutator) { mutator.mutate(genome); }
    
    inline std::vector<size_t> get_genome() const { return genome; }
private:
    std::vector<size_t> genome;
};

#endif /* PHENOTYPE_HPP */