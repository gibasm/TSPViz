#ifndef MUTATOR_HPP
#define MUTATOR_HPP

#include <vector>
#include <cstddef>

class Mutator {
public:
    virtual void mutate(std::vector<size_t>& genome) const = 0;
};

/**
 * @brief Performs a random swap of 2 genes in a genome, N-times
 */
class SwapMutator :public Mutator {
public:
    SwapMutator(size_t swap_count = 2);
    virtual ~SwapMutator();
    
    virtual void mutate(std::vector<size_t>& genome) const override;
private:
    size_t swap_count;
};

#endif /* MUTATOR_HPP */