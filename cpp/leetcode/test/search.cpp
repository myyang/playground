#include <vector>
#include <string>

#include "gtest/gtest.h"

#include "search.h"


TEST(search, letter_combination_tests)
{
    std::vector<std::string> exp = {};
    EXPECT_EQ (letter_combination(""), exp);

    std::vector<std::string> exp2 = {"a", "b", "c"};
    EXPECT_EQ (letter_combination("2"), exp2);

    std::vector<std::string> exp20 = {"a ", "b ", "c "};
    EXPECT_EQ (letter_combination("20"), exp20);

    std::vector<std::string> exp27 = {"ap", "aq", "ar", "as", "bp", "bq", "br", "bs", "cp", "cq", "cr", "cs"};
    EXPECT_EQ (letter_combination("27"), exp27);

    std::vector<std::string> exp23 = {"ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"};
    EXPECT_EQ (letter_combination("23"), exp23);

    std::vector<std::string> exp13 = {"d", "e", "f"};
    EXPECT_EQ (letter_combination("13"), exp13);

    std::vector<std::string> exp1 = {};
    EXPECT_EQ (letter_combination("1"), exp1);
}

TEST(search, combination_sum_tests)
{
    std::vector<int> nums = {2, 2, 3, 4, 5, 7};

    std::vector<std::vector<int>> exp7 = {{2, 2, 3}, {2, 5}, {2, 5}, {3, 4}, {7}};
    EXPECT_EQ (combination_sum(nums, 7), exp7);

    std::vector<std::vector<int>> exp21 = {{2, 3, 4, 5, 7},  {2, 3, 4, 5, 7}};
    EXPECT_EQ (combination_sum(nums, 21), exp21);
}

TEST(search, combination_sum_de_dup_tests)
{
    std::vector<int> nums = {2, 2, 3, 4, 5, 7};

    std::vector<std::vector<int>> exp7 = {{2, 2, 3}, {2, 5}, {3, 4}, {7}};
    EXPECT_EQ (combination_sum_de_dup(nums, 7), exp7);

    std::vector<std::vector<int>> exp21 = {{2, 3, 4, 5, 7}};
    EXPECT_EQ (combination_sum_de_dup(nums, 21), exp21);
}

TEST(search, combination_sum_3_tests)
{
    std::vector<std::vector<int>> exp37 = {{1,2,4}};
    EXPECT_EQ (combination_sum_3(3, 7), exp37);

    std::vector<std::vector<int>> exp39 = { {1,2,6}, {1,3,5}, {2,3,4} };
    EXPECT_EQ (combination_sum_3(3, 9), exp39);
}
