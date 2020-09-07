#include <vector>

#include "gtest/gtest.h"

#include "graph.h"


TEST(graph, Q200_number_of_islands_tests)
{
    std::vector<std::vector<int>> map1 = {
        {0, 1, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {0, 1, 1, 1, 1},
        {0, 1, 0, 0, 0},
        {0, 1, 1, 1, 1},
    };
    EXPECT_EQ (number_of_islands(map1), 3);

    std::vector<std::vector<int>> map2 = {};
    EXPECT_EQ (number_of_islands(map2), 0);
}
