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

#endif //LEETCODE_SEARCH_H
