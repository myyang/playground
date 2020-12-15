#include <vector>
#include <tuple>
#include <memory>

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

TEST(dp, Q303_range_query_tests)
{
    std::vector<int> nums = {-2, 0, 3, -5, 2, -1};

    std::unique_ptr<RangeQuery> rq = std::make_unique<RangeQuery>(nums);

    EXPECT_EQ(rq->get_sum_between(0, 3), -4);
    EXPECT_EQ(rq->get_sum_between(1, 3), -2);
    EXPECT_EQ(rq->get_sum_between(5, 5), -1);

}

TEST(dp, Q1218_longest_subsequence_tests)
{
    std::vector<int> nums0 = {1,2,3,4};
    EXPECT_EQ(longest_subsequence(nums0, 1), 4);
    std::vector<int> nums1 = {1,3,5,7};
    EXPECT_EQ(longest_subsequence(nums1, 1), 1);
    std::vector<int> nums2 = {1,5,7,8,5,3,4,2,1};
    EXPECT_EQ(longest_subsequence(nums2, -2), 4);
}

TEST(dp, Q53_maximum_subarray_tests)
{
    std::vector<int> nums0 = {-2,1,-3,4,-1,2,1,-5,4};
    EXPECT_EQ(maximum_subarray(nums0), 6);
    std::vector<int> nums1 = {1,2,3,4,-11,1,3,5,7};
    EXPECT_EQ(maximum_subarray(nums1), 16);
    std::vector<int> nums2 = {-1,2,-3,4,-11,-1,5,-5,7};
    EXPECT_EQ(maximum_subarray(nums2), 7);
    std::vector<int> nums3 = {-1,2,-3,4,-11,-1,6,-5,7};
    EXPECT_EQ(maximum_subarray(nums3), 8);

}
