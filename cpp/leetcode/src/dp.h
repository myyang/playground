#ifndef LEETCODE_DP_H
#define LEETCODE_DP_H

#include <vector>
#include <string>

// #70
int climbing_stairs(int n);

// #1137
int tribonacci(int n);

// #303
class RangeQuery {
    public:
        RangeQuery(std::vector<int>&);
        int get_sum_between(int, int);
    private:
        std::vector<int> sums;
};

// #1218
int longest_subsequence(std::vector<int>&, int diff);

// #53
int maximum_subarray(std::vector<int>&);

// #62
int unique_paths(int, int);

// #63
int unique_paths_2(std::vector<std::vector<int>>&);

// #64
int min_path_sum(std::vector<std::vector<int>>&);

// #120
int min_total(std::vector<std::vector<int>>&);

// #174
int min_hp(std::vector<std::vector<int>>&);

// #85
int max_rectangle(std::vector<std::vector<int>>&);

// #221
class RangeQuery2D {
    public:
        RangeQuery2D(std::vector<std::vector<int>>&);
        int get_sum(int, int, int, int);
    private:
        std::vector<std::vector<int>> dp;
};

// #1277
int count_sqr(std::vector<std::vector<int>>&);

// #198
int rob_top_down(std::vector<int>&);
int rob_bottom_up(std::vector<int>&);

// #213
int rob_in_circle(std::vector<int>&);

// #279
int perfect_squares(int);

// #139
bool word_break(std::string, std::vector<std::string>&);

// #140
std::vector<std::string> word_break_2(std::string, std::vector<std::string>&);

#endif
