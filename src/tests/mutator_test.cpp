#include <gtest/gtest.h>
#include "../app/algorithms/mutator.hpp"

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