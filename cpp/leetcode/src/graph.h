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

// #684
std::vector<int> redundant_connection_dfs(std::vector<std::vector<int>>& edges);
std::vector<int> redundant_connection_union_find(std::vector<std::vector<int>>& edges);

// #685
std::vector<int> redundant_connection_2_union_find(std::vector<std::vector<int>>& edges);

// #785
bool is_graph_bipartite(std::vector<std::vector<int>>& graph);

// #886
bool possible_bipartition(int n, std::vector<std::vector<int>>& dislikes);
bool possible_bipartition_bfs(int n, std::vector<std::vector<int>>& dislikes);

// #443
int minimum_genetic_mutation(std::string start, std::string end, std::vector<std::string>& bank);

// #815
int min_bus_to_destination(std::vector<std::vector<int>> &routers, int src, int tgr);

// #1129
std::vector<int> shortest_alternating_path(
        int n,
        std::vector<std::vector<int>>& red_edges,
        std::vector<std::vector<int>>& blue_edges);

// #743
int network_delay_time_bellmanford(std::vector<std::vector<int>>& time, int n, int k);
int network_delay_time_floydwarshall(std::vector<std::vector<int>>& time, int n, int k);

// #787
int find_cheapest_price_bellmanford(int n, std::vector<std::vector<int>>& flights, int src, int tgr, int k);
int find_cheapest_price_bellmanford_2(int n, std::vector<std::vector<int>>& flights, int src, int tgr, int k);

#endif
