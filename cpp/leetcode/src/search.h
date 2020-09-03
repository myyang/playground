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

// #201
std::vector<int> diff_ways_to_add_parentheses(std::string input);

// #93
std::vector<std::string> restore_ip_addresses(std::string input);

// #131
std::vector<std::vector<std::string>> palindrome_partition(std::string input);

// #282
std::vector<std::string> expression_add_operator(std::string input, int target);

// #842
std::vector<int> fib_seq(std::string input);

// #127
int word_ladder(std::string start, std::string end, std::vector<std::string> words);
int word_ladder_bi_dir(std::string start, std::string end, std::vector<std::string> words);

// #126
std::vector<std::vector<std::string>> word_ladder_2_seq(std::string start, std::string end, std::vector<std::string> words);
std::vector<std::vector<std::string>> word_ladder_2_rev(std::string start, std::string end, std::vector<std::string> words);

// #752
int open_the_lock(std::string target, std::vector<std::string> deadends);

#endif //LEETCODE_SEARCH_H
