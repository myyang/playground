#ifndef LEETCODE_GRAPH_H
#define LEETCODE_GRAPH_H

#include <vector>
#include <string>

// #200
int number_of_islands(std::vector<std::vector<int>>& nums);

// #547
int find_circule_number(std::vector<std::vector<int>>& nums);

// #733
std::vector<std::vector<int>>& flood_fill(std::vector<std::vector<int>>& nums, int sc, int sr, int new_color);

// #827
int making_a_large_land(std::vector<std::vector<int>>& nums);

// #1162
int as_far_as_possible_from_land(std::vector<std::vector<int>>& nums);

// #841
bool keys_and_rooms(std::vector<std::vector<int>>& nums);

// #207
bool can_finish_course(int courseNum, std::vector<std::vector<int>>& nums);

// #210
std::vector<int> can_finish_course_order(int courseNum, std::vector<std::vector<int>>& nums);

// #1202
std::string swap_to_smallest_string(std::string s, std::vector<std::vector<int>>& nums);

// #399
std::vector<double> calcEq_dfs(
        std::vector<std::vector<std::string>> eqs,
        std::vector<double>& values,
        std::vector<std::vector<std::string>> queries);

// #802
std::vector<int> find_final_state_nodes(std::vector<std::vector<int>>& graph);

#endif
