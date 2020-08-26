#include <vector>

#include "gtest/gtest.h"

#include "two_pointers.h"


TEST(two_pointer, contain_most_water_tests)
{
    std::vector<int> nums = {1,3,2,4};
    EXPECT_EQ (contain_most_water(nums), 6);
}

TEST(two_pointer, trap_most_water_tests)
{
    std::vector<int> nums = {0,1,0,2,1,0,1,3,2,1,2,1};
    EXPECT_EQ (trap_most_water(nums), 6);
}
