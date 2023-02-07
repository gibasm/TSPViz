#include <gtest/gtest.h>
#include "../app/algorithms/phenotype.hpp"

TEST(PhenotypeTest, get_cost_should_return_correct_value) {
    /* Given: */
    Phenotype individual({0, 1, 2});
    
    GraphMatrix matrix = {
        {0, 1, 2},
        {1, 0, 1},
        {2, 1, 0}
    };

    /* When: */
    float path_cost = individual.get_cost(matrix);
    
    /* Then: */
    ASSERT_EQ(path_cost, 4);
}