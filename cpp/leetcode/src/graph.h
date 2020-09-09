#ifndef LEETCODE_GRAPH_H
#define LEETCODE_GRAPH_H

#include <vector>

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

#endif
