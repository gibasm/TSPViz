#include <gtest/gtest.h>
#include "utils.hpp"
#include "../app/algorithms/crossover.hpp"

TEST(CrossoverTest, test_XOCrossover) {
    /* Given: */
    Phenotype parent_a({0, 1, 2, 3, 4});
    Phenotype parent_b({0, 4, 3, 2, 1});
    /* this array indicates if a gene at selected index was found in the child's genome */
    std::unique_ptr<bool[]> gene_found = std::make_unique<bool[]>(parent_a.get_genome().size());
    for(size_t i = 0; i < parent_a.get_genome().size(); ++i) {
        gene_found[i] = false;
    }

    OXCrossover method;

    /* When: */
    Phenotype child = method.crossover({parent_a, parent_b});

    /* Then: */

    /* the child has the same length as it's parents */
    ASSERT_EQ(child.get_genome().size(), parent_a.get_genome().size());
    ASSERT_EQ(child.get_genome().size(), parent_b.get_genome().size());

    /* the child has the same set of elements as parents */
    for(auto& gene : child.get_genome()) {
        gene_found[gene] = true;
    }

    for(size_t i = 0; i < child.get_genome().size(); ++i) {
        ASSERT_EQ(gene_found[child.get_genome()[i]], true);
    }
}