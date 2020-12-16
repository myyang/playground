#ifndef LEETCODE_DP_H
#define LEETCODE_DP_H

#include <vector>

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

#endif
