#include <vector>
#include <string>

#include "gtest/gtest.h"

#include "two_pointers.h"


TEST(two_pointer, Q11_contain_most_water_tests)
{
    std::vector<int> nums = {1,3,2,4};
    EXPECT_EQ (contain_most_water(nums), 6);
}

TEST(two_pointer, Q42_trap_most_water_tests)
{
    std::vector<int> nums = {0,1,0,2,1,0,1,3,2,1,2,1};
    EXPECT_EQ (trap_most_water(nums), 6);
}

TEST(two_pointer, Q917_reverse_only_letters_tests)
{
    EXPECT_EQ (reverse_only_letters("a-bC-dEf-ghIj"), "j-Ih-gfE-dCba");
    EXPECT_EQ (reverse_only_letters("Test1ng-Leet=code-Q!"), "Qedo1ct-eeLg=ntse-T!");
}

TEST(two_pointer, Q925_long_pressed_name_tests)
{
    EXPECT_EQ (long_pressed_name("alex", "aaleex"), true);
    EXPECT_EQ (long_pressed_name("saeed", "ssaaedd"), false);
    EXPECT_EQ (long_pressed_name("leelee", "lleeelee"), true);
    EXPECT_EQ (long_pressed_name("laiden", "laiden"), true);
}

TEST(two_pointer, Q977_squares_of_sorted_array_tests)
{
    std::vector<int> nums1 = {0,1,2,3,4};
    std::vector<int> exp1 = {0, 1, 4, 9, 16};
    EXPECT_EQ (squares_of_sorted_array(nums1), exp1);

    std::vector<int> nums2 = {-3, -1, 0,2,4};
    std::vector<int> exp2 = {0, 1, 4, 9, 16};
    EXPECT_EQ (squares_of_sorted_array(nums2), exp2);
}

TEST(two_pointer, Q992_subarray_with_k_diff_tests)
{
    std::vector<int> nums1 = {1,2,1,2,3};
    EXPECT_EQ (subarray_with_k_diff(nums1, 2), 7);

    std::vector<int> nums2 = {1,2,1,3,4};
    EXPECT_EQ (subarray_with_k_diff(nums2, 3), 3);
}

TEST(two_pointer, Q885_boats_to_save_people_tests)
{
    std::vector<int> nums1 = {1,2};
    EXPECT_EQ (boats_to_save_people(nums1, 3), 1);

    std::vector<int> nums2 = {3,2,2,1};
    EXPECT_EQ (boats_to_save_people(nums2, 3), 3);

    std::vector<int> nums3 = {3, 5, 3, 4};
    EXPECT_EQ (boats_to_save_people(nums3, 5), 4);
}

TEST(two_pointer, Q986_intersections_of_lists_test)
{
    std::vector<std::vector<int>> A = {{0,2},{5,10},{13,23},{24,25}};
    std::vector<std::vector<int>> B = {{1,5},{8,12},{15,24},{25,26}};
    std::vector<std::vector<int>> exp = {{1,2},{5,5},{8,10},{15,23},{24,24},{25,25}};

    EXPECT_EQ (intersections_of_lists(A, B), exp);
}
