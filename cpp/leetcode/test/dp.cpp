#include <vector>
#include <tuple>

#include "gtest/gtest.h"

#include "dp.h"

TEST(dp, Q70_climbing_stairs_tests)
{
    std::vector<std::tuple<int, int>> tests = {
        std::make_tuple(0, 0),
        std::make_tuple(1, 1),
        std::make_tuple(2, 2),
        std::make_tuple(3, 3),
        std::make_tuple(4, 5),
        std::make_tuple(5, 8),
    };


    int input = 0;
    int output = 0;
    for (std::tuple<int, int> t: tests)
    {
        std::tie(input, output) = t;
        EXPECT_EQ(climbing_stairs(input), output);
    }
}

TEST(dp, Q1137_tribonacci_tests)
{
    std::vector<std::tuple<int, int>> tests = {
        std::make_tuple(0, 0),
        std::make_tuple(1, 1),
        std::make_tuple(2, 1),
        std::make_tuple(3, 2),
        std::make_tuple(4, 4),
        std::make_tuple(5, 7),
        std::make_tuple(6, 13),
    };

    int input = 0;
    int output = 0;
    for (std::tuple<int, int> t: tests)
    {
        std::tie(input, output) = t;
        EXPECT_EQ(tribonacci(input), output);
    }
}
