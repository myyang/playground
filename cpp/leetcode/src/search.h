#ifndef LEETCODE_SEARCH_H
#define LEETCODE_SEARCH_H

#include <vector>
#include <string>

// #17
std::vector<std::string> letter_combination(std::string digits);

// #39
std::vector<std::vector<int>> combination_sum(std::vector<int>& nums, int target);

// #40
std::vector<std::vector<int>> combination_sum_de_dup(std::vector<int>& nums, int target);

// #216
std::vector<std::vector<int>> combination_sum_3(int k, int n);

// #46
std::vector<std::vector<int>> permutations(std::vector<int>& nums);

// #47
std::vector<std::vector<int>> permutations_de_dup(std::vector<int>& nums);

// #784
std::vector<std::string> letter_case_permutation(std::string raw);

// #22
std::vector<std::string> generate_parenthes(int n);

// #301
std::vector<std::string> remove_invalid_parenthes(std::string raw);

// #79
bool search_word(std::vector<std::vector<char>>& board, std::string word);

// #698
bool partition_k_equal_sum_subset(std::vector<int>& nums, int k);

#endif //LEETCODE_SEARCH_H
