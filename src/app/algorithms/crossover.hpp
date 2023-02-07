#ifndef CROSSOVER_HPP
#define CROSSOVER_HPP

#include "phenotype.hpp"

class CrossoverStrategy {
public:
    virtual Phenotype crossover(const std::vector<Phenotype>& parents) = 0;
};

/**
 * @brief Two-point order crossover implementation.
 */
class OXCrossover :public CrossoverStrategy {
public:
    constexpr OXCrossover() = default;
    virtual ~OXCrossover() = default;

    virtual Phenotype crossover(const std::vector<Phenotype>& parents) override;
};

#endif /* CROSSOVER_HPP */