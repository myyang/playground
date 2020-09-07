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

TEST(graph, Q547_find_circule_number_tests)
{

    std::vector<std::vector<int>> fri1 = {
        {1, 0, 0, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 0, 0, 1},
    };
    EXPECT_EQ (find_circule_number(fri1), 3);

    std::vector<std::vector<int>> fri2 = { };
    EXPECT_EQ (find_circule_number(fri2), 0);

    std::vector<std::vector<int>> fri3 = {
        {1, 1, 0, 1, 0},
        {1, 1, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {1, 0, 0, 1, 1},
        {0, 0, 0, 1, 1},
    };
    EXPECT_EQ (find_circule_number(fri3), 2);
}

TEST(graph, Q733_flood_fill_tests)
{
    std::vector<std::vector<int>> img1 = {
        {1, 0, 0, 1, 0},
        {0, 1, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 0, 1, 1},
    };
    std::vector<std::vector<int>> img2 = {
        {2, 0, 0, 1, 0},
        {0, 1, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 0, 1, 1},
    };
    EXPECT_EQ (flood_fill(img1, 0, 0, 2), img2);

    std::vector<std::vector<int>> img3 = {
        {2, 0, 0, 1, 0},
        {0, 1, 1, 0, 0},
        {0, 1, 0, 3, 0},
        {0, 0, 3, 3, 0},
        {0, 0, 0, 3, 3},
    };
    EXPECT_EQ (flood_fill(img2, 3, 3, 3), img3);

    std::vector<std::vector<int>> img4 = {
        {2, 0, 0, 1, 0},
        {0, 4, 4, 0, 0},
        {0, 4, 0, 3, 0},
        {0, 0, 3, 3, 0},
        {0, 0, 0, 3, 3},
    };
    EXPECT_EQ (flood_fill(img3, 1, 2, 4), img4);
}
