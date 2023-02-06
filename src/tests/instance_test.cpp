#include <gtest/gtest.h>
#include "utils.hpp"

#include "../app/instance.hpp"

class TSPInstanceTest :public ::testing::Test {
protected:
    void SetUp() override {
        if(instance != nullptr) {
            instance.reset();
        }

        instance = std::make_shared<TSPInstance>(vertices);
    }

    std::shared_ptr<TSPInstance> instance = nullptr;
    static const std::vector<std::array<float, 2>> vertices;
};

/* sample instance */
const std::vector<std::array<float, 2>> TSPInstanceTest::vertices({
    {1, 1}, //0
    {1, 2}, //1
    {1, 3}, //2
    {1, 4}, //3
    {1, 5}, //4
});

/* 
    The neighborhood matrix should be 
    created from the vertex list with 
    2D euclidean distances.
*/
TEST_F(TSPInstanceTest, should_constructNeighborhoodMatrix_with_euclideanDistances) {

    auto matrix = instance->get_neighborhood_matrix();
    
    ASSERT_EQ(matrix.size(), instance->get_vertex_count());

    GraphMatrix expected({
    //   0  1  2  3  4
        {0, 1, 2, 3, 4}, //0
        {1, 0, 1, 2, 3}, //1
        {2, 1, 0, 1, 2}, //2
        {3, 2, 1, 0, 1}, //3
        {4, 3, 2, 1, 0}, //4
    });

    ASSERT_MATRICES_EQ(expected, matrix, matrix.size(), matrix.size());
}