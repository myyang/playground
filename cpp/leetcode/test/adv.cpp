#include <vector>

#include "gtest/gtest.h"

#include "adv.h"


TEST(adv, Q239_sliding_maximum_tests)
{
    std::vector<int> nums = {1,3,-1,-3,5,3,6,7};
    std::vector<int> exp = {3,3,5,5,6,7};
    EXPECT_EQ (sliding_maximum(nums, 3), exp);
}
