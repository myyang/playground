#include <vector>
#include <string>

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

TEST(two_pointer, reverse_only_letters_tests)
{
    EXPECT_EQ (reverse_only_letters("a-bC-dEf-ghIj"), "j-Ih-gfE-dCba");
    EXPECT_EQ (reverse_only_letters("Test1ng-Leet=code-Q!"), "Qedo1ct-eeLg=ntse-T!");
}

TEST(two_pointer, long_pressed_name_tests)
{
    EXPECT_EQ (long_pressed_name("alex", "aaleex"), true);
    EXPECT_EQ (long_pressed_name("saeed", "ssaaedd"), false);
    EXPECT_EQ (long_pressed_name("leelee", "lleeelee"), true);
    EXPECT_EQ (long_pressed_name("laiden", "laiden"), true);
}
