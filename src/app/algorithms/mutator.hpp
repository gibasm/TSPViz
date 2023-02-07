#ifndef MUTATOR_HPP
#define MUTATOR_HPP

#include <vector>
#include <cstddef>

class Mutator {
public:
    virtual void mutate(std::vector<size_t>& genome) const = 0;
};

#endif /* MUTATOR_HPP */