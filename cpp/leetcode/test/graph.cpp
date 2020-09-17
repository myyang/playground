#include <vector>

#include "gtest/gtest.h"

#include "graph.h"


TEST(graph, Q200_number_of_islands_tests)
{
    std::vector<std::vector<int>> map1 = {
        {0, 1, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {0, 1, 1, 1, 1},
        {0, 1, 0, 0, 0},
        {0, 1, 1, 1, 1},
    };
    EXPECT_EQ (number_of_islands(map1), 3);

    std::vector<std::vector<int>> map2 = {};
    EXPECT_EQ (number_of_islands(map2), 0);
}

TEST(graph, Q547_find_circule_number_tests)
{

    std::vector<std::vector<int>> fri1 = {
        {1, 0, 0, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 0, 0, 1},
    };
    EXPECT_EQ (find_circule_number(fri1), 3);

    std::vector<std::vector<int>> fri2 = { };
    EXPECT_EQ (find_circule_number(fri2), 0);

    std::vector<std::vector<int>> fri3 = {
        {1, 1, 0, 1, 0},
        {1, 1, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {1, 0, 0, 1, 1},
        {0, 0, 0, 1, 1},
    };
    EXPECT_EQ (find_circule_number(fri3), 2);
}

TEST(graph, Q733_flood_fill_tests)
{
    std::vector<std::vector<int>> img1 = {
        {1, 0, 0, 1, 0},
        {0, 1, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 0, 1, 1},
    };
    std::vector<std::vector<int>> img2 = {
        {2, 0, 0, 1, 0},
        {0, 1, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 0, 1, 1},
    };
    EXPECT_EQ (flood_fill(img1, 0, 0, 2), img2);

    std::vector<std::vector<int>> img3 = {
        {2, 0, 0, 1, 0},
        {0, 1, 1, 0, 0},
        {0, 1, 0, 3, 0},
        {0, 0, 3, 3, 0},
        {0, 0, 0, 3, 3},
    };
    EXPECT_EQ (flood_fill(img2, 3, 3, 3), img3);

    std::vector<std::vector<int>> img4 = {
        {2, 0, 0, 1, 0},
        {0, 4, 4, 0, 0},
        {0, 4, 0, 3, 0},
        {0, 0, 3, 3, 0},
        {0, 0, 0, 3, 3},
    };
    EXPECT_EQ (flood_fill(img3, 1, 2, 4), img4);
}

TEST(graph, Q827_making_a_large_land_tests)
{
    std::vector<std::vector<int>> map1 = {
        {1, 0, 0, 1},
        {0, 0, 1, 1},
        {1, 0, 0, 1},
    };
    EXPECT_EQ (making_a_large_land(map1), 5);

    std::vector<std::vector<int>> map2 = {
        {1, 1, 0, 1},
        {0, 0, 1, 1},
        {1, 0, 0, 1},
    };
    EXPECT_EQ (making_a_large_land(map2), 7);

    std::vector<std::vector<int>> map3 = {
        {1, 1},
        {1, 1},
    };
    EXPECT_EQ (making_a_large_land(map3), 4);

    std::vector<std::vector<int>> map4 = {
        {0, 0},
        {0, 0},
    };
    EXPECT_EQ (making_a_large_land(map4), 1);
}

TEST(graph, Q1162_as_far_as_possible_from_land)
{

    std::vector<std::vector<int>> map1 = {
        {1, 0, 1},
        {0, 0, 0},
        {1, 0, 1},
    };
    EXPECT_EQ (as_far_as_possible_from_land(map1), 2);

    std::vector<std::vector<int>> map2 = {
        {1, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
    };
    EXPECT_EQ (as_far_as_possible_from_land(map2), 4);

    std::vector<std::vector<int>> map3 = {
        {1, 1},
        {1, 1},
    };
    EXPECT_EQ (as_far_as_possible_from_land(map3), -1);

    std::vector<std::vector<int>> map4 = {
        {0, 0},
        {0, 0},
    };
    EXPECT_EQ (as_far_as_possible_from_land(map4), -1);
}

TEST(graph, Q841_keys_and_rooms)
{
    std::vector<std::vector<int>> keys1 = { {1}, {2}, {3}, {} };
    EXPECT_EQ (keys_and_rooms(keys1), true);

    std::vector<std::vector<int>> keys2 = {
        {1, 3}, {0, 3, 1}, {2}, {0},
    };
    EXPECT_EQ (keys_and_rooms(keys2), false);
}

TEST(graph, Q207_can_finish_course_tests)
{
    std::vector<std::vector<int>> graph1 = {
        {0, 1}, {0, 7}, {7, 1}, {5, 0}, {4, 6}, {6, 2},
    };
    EXPECT_EQ (can_finish_course(8, graph1), true);

    std::vector<std::vector<int>> graph2 = {
        {0, 1}, {0, 7}, {7, 1}, {5, 0}, {4, 6}, {6, 2}, {1, 5},
    };
    EXPECT_EQ (can_finish_course(8, graph2), false);
}

TEST(graph, Q210_can_finish_course_order_tests)
{
    std::vector<std::vector<int>> graph1 = {
        {0, 1}, {0, 7}, {7, 1}, {5, 0}, {4, 6}, {6, 2},
    };
    std::vector<int> ans1 = {5, 4, 6, 3, 2, 0, 7, 1};
    EXPECT_EQ (can_finish_course_order(8, graph1), ans1);

    std::vector<std::vector<int>> graph2 = {
        {0, 1}, {0, 7}, {7, 1}, {5, 0}, {4, 6}, {6, 2}, {1, 5},
    };
    std::vector<int> ans2 = {};
    EXPECT_EQ (can_finish_course_order(8, graph2), ans2);

    std::vector<std::vector<int>> graph3 = {
        {1, 0}, {2, 0}, {3, 1}, {2, 1},
    };
    std::vector<int> ans3 = {3, 2, 1, 0};
    EXPECT_EQ (can_finish_course_order(4, graph3), ans3);
}

TEST(graph, Q1202_swap_to_smallest_string_tests)
{
    std::vector<std::vector<int>> pairs1 = {
        {0, 3}, {1, 2}
    };
    EXPECT_EQ(swap_to_smallest_string("dcab", pairs1), "bacd");

    std::vector<std::vector<int>> pairs2 = {
         {0, 3}, {0, 2}, {1, 2},
    };
    EXPECT_EQ(swap_to_smallest_string("dcab", pairs2), "abcd");
}

TEST(graph, Q399_calcEq_dfs_tests)
{
    std::vector<std::vector<std::string>> eqs1 = {
        {"a", "b"}, {"b", "c"}
    };
    std::vector<double> values1 = {2.0, 3.0};
    std::vector<std::vector<std::string>> queries1 = {
        {"a", "c"}, {"b", "a"}, {"a", "e"}, {"a", "a"}, {"x", "x"}
    };
    std::vector<double> ans1 = {6.0, 0.5, -1.0, 1.0, -1.0};
    EXPECT_EQ (calcEq_dfs(eqs1, values1, queries1), ans1);
}

TEST(graph, Q802_find_final_state_nodes_tests)
{
    std::vector<std::vector<int>> graph1 = {
        {1,2}, {2,3}, {5}, {0}, {5}, {}, {},
    };
    std::vector<int> ans1 = {2, 4, 5, 6};
    EXPECT_EQ (find_final_state_nodes(graph1), ans1);
}

TEST(graph, Q684_redundant_connection_dfs_tests)
{
    std::vector<std::vector<int>> edges1 = {
        {1,2}, {1,3}, {2,3}
    };
    std::vector<int> ans1 = {2,3};
    EXPECT_EQ (redundant_connection_dfs(edges1), ans1);

    std::vector<std::vector<int>> edges2 = {
        {1,2}, {2,3}, {3,4}, {1,4}, {1,5}
    };
    std::vector<int> ans2 = {1,4};
    EXPECT_EQ (redundant_connection_dfs(edges2), ans2);
}

TEST(graph, Q684_redundant_connection_union_find_tests)
{
    std::vector<std::vector<int>> edges1 = {
        {1,2}, {1,3}, {2,3}
    };
    std::vector<int> ans1 = {2,3};
    EXPECT_EQ (redundant_connection_union_find(edges1), ans1);

    std::vector<std::vector<int>> edges2 = {
        {1,2}, {2,3}, {3,4}, {1,4}, {1,5}
    };
    std::vector<int> ans2 = {1,4};
    EXPECT_EQ (redundant_connection_union_find(edges2), ans2);
}

TEST(graph, Q685_redundant_connection_2_union_find_tests)
{
    std::vector<std::vector<int>> edges1 = {
        {1,2}, {1,3}, {2,3}
    };
    std::vector<int> ans1 = {2,3};
    EXPECT_EQ (redundant_connection_2_union_find(edges1), ans1);

    std::vector<std::vector<int>> edges2 = {
        {1,2}, {2,3}, {3,4}, {4,1}, {1,5}
    };
    std::vector<int> ans2 = {4,1};
    EXPECT_EQ (redundant_connection_2_union_find(edges2), ans2);
}

TEST(graph, Q785_is_graph_bipartite_tests)
{
    std::vector<std::vector<int>> graph1 = {{1,3}, {0,2}, {1,3}, {0,2}};
    EXPECT_EQ (is_graph_bipartite(graph1), true);

    std::vector<std::vector<int>> graph2 = {{1,2,3}, {0,2}, {0,1,3}, {0,2}};
    EXPECT_EQ (is_graph_bipartite(graph2), false);
}

TEST(graph, Q886_possible_bipartition_tests)
{
    std::vector<std::vector<int>> dislikes1 = {{0,1}, {0,2}, {1,3}};
    EXPECT_EQ (possible_bipartition(4, dislikes1), true);

    std::vector<std::vector<int>> dislikes2 = {{0,1}, {0,2}, {1,2}};
    EXPECT_EQ (possible_bipartition(3, dislikes2), false);
}

TEST(graph, Q886_possible_bipartition_bfs_tests)
{
    std::vector<std::vector<int>> dislikes1 = {{0,1}, {0,2}, {1,3}};
    EXPECT_EQ (possible_bipartition_bfs(4, dislikes1), true);

    std::vector<std::vector<int>> dislikes2 = {{0,1}, {0,2}, {1,2}};
    EXPECT_EQ (possible_bipartition_bfs(3, dislikes2), false);
}
