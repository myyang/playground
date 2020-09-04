#include <vector>
#include <string>
#include "gtest/gtest.h"

#include "search.h"


TEST(search, Q17_letter_combination_tests)
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

TEST(search, Q39_combination_sum_tests)
{
    std::vector<int> nums = {2, 2, 3, 4, 5, 7};

    std::vector<std::vector<int>> exp7 = {{2, 2, 3}, {2, 5}, {2, 5}, {3, 4}, {7}};
    EXPECT_EQ (combination_sum(nums, 7), exp7);

    std::vector<std::vector<int>> exp21 = {{2, 3, 4, 5, 7},  {2, 3, 4, 5, 7}};
    EXPECT_EQ (combination_sum(nums, 21), exp21);
}

TEST(search, Q40_combination_sum_de_dup_tests)
{
    std::vector<int> nums = {2, 2, 3, 4, 5, 7};

    std::vector<std::vector<int>> exp7 = {{2, 2, 3}, {2, 5}, {3, 4}, {7}};
    EXPECT_EQ (combination_sum_de_dup(nums, 7), exp7);

    std::vector<std::vector<int>> exp21 = {{2, 3, 4, 5, 7}};
    EXPECT_EQ (combination_sum_de_dup(nums, 21), exp21);
}

TEST(search, Q216_combination_sum_3_tests)
{
    std::vector<std::vector<int>> exp37 = {{1,2,4}};
    EXPECT_EQ (combination_sum_3(3, 7), exp37);

    std::vector<std::vector<int>> exp39 = { {1,2,6}, {1,3,5}, {2,3,4} };
    EXPECT_EQ (combination_sum_3(3, 9), exp39);
}

TEST(search, Q46_permutations_tests)
{
    std::vector<int> nums3 = {1,2,3};
    std::vector<std::vector<int>> exp3 = {
        {1,2,3}, {1,3,2}, {2,1,3}, {2,3,1}, {3,1,2}, {3,2,1}
    };
    EXPECT_EQ (permutations(nums3), exp3);
}

TEST(search, Q47_permutations_de_dup_tests)
{
    std::vector<int> nums3 = {1,1,2};
    std::vector<std::vector<int>> exp3 = {
        {1,1,2}, {1,2,1}, {2,1,1}
    };
    EXPECT_EQ (permutations_de_dup(nums3), exp3);

    std::vector<int> nums4 = {1,1,1,2};
    std::vector<std::vector<int>> exp4 = {
        {1,1,1,2}, {1,1,2,1}, {1,2,1,1}, {2,1,1,1}
    };
    EXPECT_EQ (permutations_de_dup(nums4), exp4);
}

TEST(search, Q784_letter_case_permutation_tests)
{
    std::vector<std::string> exp1 = {"a1b2", "a1B2", "A1b2", "A1B2"};
    EXPECT_EQ (letter_case_permutation("a1b2"), exp1);

    std::vector<std::string> exp2 = {"12345"};
    EXPECT_EQ (letter_case_permutation("12345"), exp2);
}

TEST(search, Q22_generate_parenthes_tests)
{
    std::vector<std::string> exp1 = {"()"};
    EXPECT_EQ (generate_parenthes(1), exp1);

    std::vector<std::string> exp3 = {"((()))", "(()())", "(())()", "()(())", "()()()" };
    EXPECT_EQ (generate_parenthes(3), exp3);
}

TEST(search, Q301_remove_invalid_parenthes_tests)
{
    std::vector<std::string> exp1 = {"(())()", "()()()"};
    EXPECT_EQ (remove_invalid_parenthes("()())()"), exp1);

    std::vector<std::string> exp2 = {"(a())()", "(a)()()"};
    EXPECT_EQ (remove_invalid_parenthes("(a)())()"), exp2);

    std::vector<std::string> exp3 = {""};
    EXPECT_EQ (remove_invalid_parenthes(")("), exp3);

}

TEST(search, Q698_partition_k_equal_sum_subset_tests)
{
    std::vector<int> nums = {4, 3, 2, 3, 5, 2, 1};
    EXPECT_EQ (partition_k_equal_sum_subset(nums, 4), true);
    EXPECT_EQ (partition_k_equal_sum_subset(nums, 3), false);
    EXPECT_EQ (partition_k_equal_sum_subset(nums, 2), true);
    EXPECT_EQ (partition_k_equal_sum_subset(nums, 1), true);
}

TEST(search, Q201_diff_ways_to_add_parentheses_tests)
{
    std::vector<int> exp1 = {2, 0};
    EXPECT_EQ (diff_ways_to_add_parentheses("2-1-1"), exp1);

    std::vector<int> exp2 = {-34, -10, -14, -10, 10};
    EXPECT_EQ (diff_ways_to_add_parentheses("2*3-4*5"), exp2);
}

TEST(search, Q93_restore_ip_addresses_tests)
{
    std::vector<std::string> exp1 = {"255.255.11.135", "255.255.111.35"};
    EXPECT_EQ (restore_ip_addresses("25525511135"), exp1);

    std::vector<std::string> exp2 = {"25.50.1.110", "25.50.11.10", "25.50.111.0", "255.0.1.110", "255.0.11.10", "255.0.111.0"};
    EXPECT_EQ (restore_ip_addresses("25501110"), exp2);

    std::vector<std::string> exp3 = {"0.0.0.0"};
    EXPECT_EQ (restore_ip_addresses("0000"), exp3);

    std::vector<std::string> exp4 = {"0.10.10.10", "0.10.101.0", "0.101.0.10"};
    EXPECT_EQ (restore_ip_addresses("0101010"), exp4);
}

TEST(search, Q131_palindrome_partition_tests)
{
    std::vector<std::vector<std::string>> exp1 = { {"a", "a", "b"}, {"aa", "b"} };
    EXPECT_EQ (palindrome_partition("aab"), exp1);

    std::vector<std::vector<std::string>> exp2 = { {"a", "a", "a"}, {"a", "aa"}, {"aa", "a"}, {"aaa"} };
    EXPECT_EQ (palindrome_partition("aaa"), exp2);
}

TEST(search, Q282_expression_add_operator_tests)
{
    std::vector<std::string> exp1 = {"1+2+3", "1*2*3"};
    EXPECT_EQ (expression_add_operator("123", 6), exp1);

    std::vector<std::string> exp2 = {"1*0+5","10-5"};
    EXPECT_EQ (expression_add_operator("105", 5), exp2);
}

TEST(search, Q842_fib_seq_tests)
{
    std::vector<int> exp1 = {1, 0, 1};
    EXPECT_EQ (fib_seq("101"), exp1);

    std::vector<int> exp2 = {11, 0, 11};
    EXPECT_EQ (fib_seq("11011"), exp2);

    std::vector<int> exp3 = {123, 456, 579};
    EXPECT_EQ (fib_seq("123456579"), exp3);
}

TEST(search, Q127_word_ladder_tests)
{
    std::vector<std::string> words1 = {"hot","dot","dog","lot","log","cog"};
    EXPECT_EQ (word_ladder("hit", "cog", words1), 5);
}

TEST(search, Q127_word_ladder_bi_dir_tests)
{
    std::vector<std::string> words1 = {"hot","dot","dog","lot","log","cog"};
    EXPECT_EQ (word_ladder_bi_dir("hit", "cog", words1), 5);
}

TEST(search, Q126_word_ladder_2_seq_tests)
{
    std::vector<std::string> words1 = {"hot","dot","dog","lot","log","cog"};
    std::vector<std::vector<std::string>> exp1 = {
        {"hit", "hot", "dot", "dog", "cog"},
        {"hit", "hot", "lot", "log", "cog"},
    };
    EXPECT_EQ (word_ladder_2_seq("hit", "cog", words1), exp1);
}

TEST(search, Q126_word_ladder_2_rev_tests)
{
    std::vector<std::string> words1 = {"hot","dot","dog","lot","log","cog"};
    std::vector<std::vector<std::string>> exp1 = {
        {"hit", "hot", "dot", "dog", "cog"},
        {"hit", "hot", "lot", "log", "cog"},
    };
    EXPECT_EQ (word_ladder_2_rev("hit", "cog", words1), exp1);
}

TEST(search, Q752_open_the_lock_tests)
{
    std::vector<std::string> deadends1 = {"0201","0101","0102","1212","2002"};
    EXPECT_EQ (open_the_lock("0202", deadends1), 6);

    std::vector<std::string> deadends2 = {"0201","0101","0102","1212","2002"};
    EXPECT_EQ (open_the_lock("0009", deadends2), 1);

    std::vector<std::string> deadends3 = {"8887","8889","8878","8898","8788","8988","7888","9888"};
    EXPECT_EQ (open_the_lock("8888", deadends3), -1);
}

TEST(search, Q752_open_the_lock_bi_dir_tests)
{
    std::vector<std::string> deadends1 = {"0201","0101","0102","1212","2002"};
    EXPECT_EQ (open_the_lock_bi_dir("0202", deadends1), 6);

    std::vector<std::string> deadends2 = {"0201","0101","0102","1212","2002"};
    EXPECT_EQ (open_the_lock_bi_dir("0009", deadends2), 1);

    std::vector<std::string> deadends3 = {"8887","8889","8878","8898","8788","8988","7888","9888"};
    EXPECT_EQ (open_the_lock_bi_dir("8888", deadends3), -1);
}
