#include <gtest/gtest.h>
#include "../app/algorithms/mutator.hpp"

/*
    Those mutator tests only check whether the mutated genome
    can be considered valid (there are no cycles in the path)
*/

TEST(MutatorTest, test_SwapMutator) {
    /* Given: */
    std::vector<size_t> genome = {0, 1, 2, 3, 4};
    /* this array indicates if a gene at selected index was found in the child's genome */
    std::unique_ptr<bool[]> gene_found = std::make_unique<bool[]>(genome.size());
    for(size_t i = 0; i < genome.size(); ++i) {
        gene_found[i] = false;
    }

    SwapMutator mutator;

    /* When: */
    mutator.mutate(genome);

    /* Then: */

    /* all genes are included [0, N] */
    for(auto& gene : genome) {
        gene_found[gene] = true;
    }

    for(size_t i = 0; i < genome.size(); ++i) {
        ASSERT_EQ(gene_found[genome[i]], true);
    }
}

TEST(MutatorTest, test_InvertMutator) {
    /* Given: */
    std::vector<size_t> genome = {0, 1, 2, 3, 4};
    /* this array indicates if a gene at selected index was found in the child's genome */
    std::unique_ptr<bool[]> gene_found = std::make_unique<bool[]>(genome.size());
    for(size_t i = 0; i < genome.size(); ++i) {
        gene_found[i] = false;
    }

    InvertMutator mutator;

    /* When: */
    mutator.mutate(genome);

    /* Then: */

    /* all genes are included [0, N] */
    for(auto& gene : genome) {
        gene_found[gene] = true;
    }

    for(size_t i = 0; i < genome.size(); ++i) {
        ASSERT_EQ(gene_found[genome[i]], true);
    }
}