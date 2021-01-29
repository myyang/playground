#include <vector>
#include <tuple>
#include <memory>

#include "gtest/gtest.h"

#include "dp.h"

TEST(dp, Q70_climbing_stairs_tests)
{
    std::vector<std::tuple<int, int>> tests = {
        std::make_tuple(0, 0),
        std::make_tuple(1, 1),
        std::make_tuple(2, 2),
        std::make_tuple(3, 3),
        std::make_tuple(4, 5),
        std::make_tuple(5, 8),
    };


    int input = 0;
    int output = 0;
    for (std::tuple<int, int> t: tests)
    {
        std::tie(input, output) = t;
        EXPECT_EQ(climbing_stairs(input), output);
    }
}

TEST(dp, Q1137_tribonacci_tests)
{
    std::vector<std::tuple<int, int>> tests = {
        std::make_tuple(0, 0),
        std::make_tuple(1, 1),
        std::make_tuple(2, 1),
        std::make_tuple(3, 2),
        std::make_tuple(4, 4),
        std::make_tuple(5, 7),
        std::make_tuple(6, 13),
    };

    int input = 0;
    int output = 0;
    for (std::tuple<int, int> t: tests)
    {
        std::tie(input, output) = t;
        EXPECT_EQ(tribonacci(input), output);
    }
}

TEST(dp, Q303_range_query_tests)
{
    std::vector<int> nums = {-2, 0, 3, -5, 2, -1};

    std::unique_ptr<RangeQuery> rq = std::make_unique<RangeQuery>(nums);

    EXPECT_EQ(rq->get_sum_between(0, 3), -4);
    EXPECT_EQ(rq->get_sum_between(1, 3), -2);
    EXPECT_EQ(rq->get_sum_between(5, 5), -1);

}

TEST(dp, Q1218_longest_subsequence_tests)
{
    std::vector<int> nums0 = {1,2,3,4};
    EXPECT_EQ(longest_subsequence(nums0, 1), 4);
    std::vector<int> nums1 = {1,3,5,7};
    EXPECT_EQ(longest_subsequence(nums1, 1), 1);
    std::vector<int> nums2 = {1,5,7,8,5,3,4,2,1};
    EXPECT_EQ(longest_subsequence(nums2, -2), 4);
}

TEST(dp, Q53_maximum_subarray_tests)
{
    std::vector<int> nums0 = {-2,1,-3,4,-1,2,1,-5,4};
    EXPECT_EQ(maximum_subarray(nums0), 6);
    std::vector<int> nums1 = {1,2,3,4,-11,1,3,5,7};
    EXPECT_EQ(maximum_subarray(nums1), 16);
    std::vector<int> nums2 = {-1,2,-3,4,-11,-1,5,-5,7};
    EXPECT_EQ(maximum_subarray(nums2), 7);
    std::vector<int> nums3 = {-1,2,-3,4,-11,-1,6,-5,7};
    EXPECT_EQ(maximum_subarray(nums3), 8);

}

TEST(dp, Q62_unique_paths_tests)
{
    EXPECT_EQ(unique_paths(3, 2), 3);
    EXPECT_EQ(unique_paths(5, 3), 15);
}

TEST(dp, Q63_unique_paths_2_tests)
{
    std::vector<std::vector<int>> grids0 = {
        {0, 0, 0, 0, 0},
        {0, 1, 0, 1, 1},
        {0, 1, 0, 1, 0},
    };
    EXPECT_EQ(unique_paths_2(grids0), 0);

    std::vector<std::vector<int>> grids1 = {
        {0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0},
    };
    EXPECT_EQ(unique_paths_2(grids1), 1);

    std::vector<std::vector<int>> grids2 = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0},
    };
    EXPECT_EQ(unique_paths_2(grids2), 0);

    std::vector<std::vector<int>> grids3 = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
    };
    EXPECT_EQ(unique_paths_2(grids3), 0);

    std::vector<std::vector<int>> grids4 = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0},
    };
    EXPECT_EQ(unique_paths_2(grids4), 10);
}

TEST(dp, Q64_min_path_sum_tests)
{
    std::vector<std::vector<int>> grids0 = {
        {1, 1, 2, 3, 4},
        {2, 1, 1, 1, 1},
        {3, 4, 5, 6, 1},
    };
    EXPECT_EQ(min_path_sum(grids0), 7);

    std::vector<std::vector<int>> grids1 = {
        {1, 1, 2, 3, 4},
        {2, 2, 1, 1, 1},
        {3, 4, 5, 6, 1},
    };
    EXPECT_EQ(min_path_sum(grids1), 8);
}

TEST(dp, Q120_min_total_tests)
{
    std::vector<std::vector<int>> grids0 = {
        {2},
        {3,4},
        {5,6,1},
        {8,9,10,11},
    };
    EXPECT_EQ(min_total(grids0), 17);

    std::vector<std::vector<int>> grids1 = {
        {2},
        {3,4},
        {6,5,7},
        {4,1,8,3},
    };
    EXPECT_EQ(min_total(grids1), 11);
}

TEST(dp, Q174_min_hp_tests)
{
    std::vector<std::vector<int>> grids0 = {
        {-2,-3,3},
        {-5,-10,1},
        {10,30,-5},
    };
    EXPECT_EQ(min_hp(grids0), 7);
}

TEST(dp, Q85_max_rectangle_tests)
{
    std::vector<std::vector<int>> grids0 = {
        {1,0,1,0,0,0},
        {1,0,1,1,1,0},
        {1,0,1,1,1,0},
        {0,0,1,1,0,0},
    };
    EXPECT_EQ(max_rectangle(grids0), 6);
}

TEST(dp, Q221_num_matrix_tests)
{
    std::vector<std::vector<int>> grids0 = {
        {3, 0, 1, 4, 2},
        {5, 6, 3, 2, 1},
        {1, 2, 0, 1, 5},
        {4, 1, 0, 1, 7},
        {1, 0, 3, 0, 5}
    };

    std::unique_ptr<RangeQuery2D> uni_ptr = std::make_unique<RangeQuery2D>(grids0);

    EXPECT_EQ(uni_ptr->get_sum(2, 1, 4, 3), 8);
    EXPECT_EQ(uni_ptr->get_sum(1, 1, 2, 2), 11);
    EXPECT_EQ(uni_ptr->get_sum(1, 2, 2, 4), 12);
}

TEST(dp, Q1277_count_sqr_tests)
{
    std::vector<std::vector<int>> grids0 = {
        {1, 1, 0, 1, 1, 1},
        {1, 1, 0, 1, 1, 1},
        {0, 0, 0, 1, 1, 1},
        {0, 0, 1, 0, 0, 0},
    };
    EXPECT_EQ(count_sqr(grids0), 14 + 1 + 5);

    std::vector<std::vector<int>> grids1 = {
        {1, 1, 0, 0, 1, 1},
        {1, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0},
    };
    EXPECT_EQ(count_sqr(grids1), 7);
}

TEST(dp, Q198_rob_house_tests)
{
    std::vector<int> money0 = {2,1,1,2};
    EXPECT_EQ(rob_top_down(money0), 4);
    EXPECT_EQ(rob_bottom_up(money0), 4);

    std::vector<int> money1 = {1,1,3,2,1,3};
    EXPECT_EQ(rob_top_down(money1), 7);
    EXPECT_EQ(rob_bottom_up(money1), 7);
}

TEST(dp, Q213_rob_in_circle_tests)
{
    std::vector<int> money0 = {2, 1, 1, 2};
    EXPECT_EQ(rob_in_circle(money0), 3);

    std::vector<int> money1 = {1,1,3,2,1,3};
    EXPECT_EQ(rob_in_circle(money1), 6);

    std::vector<int> money2 = {8,2,2,2,2,8};
    EXPECT_EQ(rob_in_circle(money2), 12);
}

TEST(dp, Q279_perfect_squares_tests)
{
    EXPECT_EQ(perfect_squares(12), 3);
    EXPECT_EQ(perfect_squares(13), 2);
}

TEST(dp, Q139_word_break_tests)
{
    std::vector<std::string> words = {"leet", "code"};
    EXPECT_EQ(word_break("leetcodes", words), false);
    EXPECT_EQ(word_break("leetscode", words), false);
    EXPECT_EQ(word_break("leetcode", words), true);
}

TEST(dp, Q140_word_break_2_tests)
{
    std::vector<std::string> words = {"cat","cats","and","sand","dog"};

    std::vector<std::string> ans0 = {"cat sand dog", "cats and dog"};
    EXPECT_EQ(word_break_2("catsanddog", words), ans0);

    std::vector<std::string> ans1 = {};
    EXPECT_EQ(word_break_2("cad", words), ans1);

    std::vector<std::string> ans2 = {"cat cat cat"};
    EXPECT_EQ(word_break_2("catcatcat", words), ans2);
}

TEST(dp, Q300_length_of_lis_tests)
{
    std::vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 180};
    EXPECT_EQ(length_of_lis(nums), 5);

    std::vector<int> nums1 = {10, 9, 2, 5, 3, 7, 101, 1};
    EXPECT_EQ(length_of_lis(nums1), 4);

    std::vector<int> nums2 = {10, 9, 8, 7, 6, 5};
    EXPECT_EQ(length_of_lis(nums2), 1);

    std::vector<int> nums3 = {};
    EXPECT_EQ(length_of_lis(nums3), 0);
}

TEST(dp, Q300_length_of_lis_rec_tests)
{
    std::vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 180};
    EXPECT_EQ(length_of_lis_rec(nums), 5);

    std::vector<int> nums1 = {10, 9, 2, 5, 3, 7, 101, 1};
    EXPECT_EQ(length_of_lis_rec(nums1), 4);

    std::vector<int> nums2 = {10, 9, 8, 7, 6, 5};
    EXPECT_EQ(length_of_lis_rec(nums2), 1);

    std::vector<int> nums3 = {};
    EXPECT_EQ(length_of_lis_rec(nums3), 0);
}

TEST(dp, Q673_number_length_of_list_tests) {
    std::vector<int> nums0 = {1, 3, 6, 5, 4, 7};
    EXPECT_EQ(number_length_of_lis(nums0), 3);

    std::vector<int> nums1 = {9,8,7,6,5};
    EXPECT_EQ(number_length_of_lis(nums1), 5);
}

TEST(dp, Q1105_fill_book_shelves_tests) {
    std::vector<std::vector<int>> books0 = {{1,1},{2,3},{2,3},{1,1},{1,1},{1,1},{1,2}};
    EXPECT_EQ(fill_book_shelves(books0, 4), 6);

    std::vector<std::vector<int>> books1 = {{1,1},{2,3}};
    EXPECT_EQ(fill_book_shelves(books1, 4), 3);

    std::vector<std::vector<int>> books2 = {{1,1},{2,3},{2,3}};
    EXPECT_EQ(fill_book_shelves(books2, 4), 4);
}

TEST(dp, Q87_gray_code_tests) {
    std::vector<int> ans0 = {0};
    EXPECT_EQ(gray_code(0), ans0);

    std::vector<int> ans1 = {0,1};
    EXPECT_EQ(gray_code(1), ans1);

    std::vector<int> ans2 = {0,2,1,3};
    EXPECT_EQ(gray_code(2), ans2);

    std::vector<int> ans3 = {0,4,2,6,1,5,3,7};
    EXPECT_EQ(gray_code(3), ans3);
}

TEST(dp, Q72_min_dest_tests)
{
    EXPECT_EQ(min_dest("abcc", "bcd"), 2);
    EXPECT_EQ(min_dest("abc", "bcd"), 2);
    EXPECT_EQ(min_dest("", ""), 0);
    EXPECT_EQ(min_dest("a", "a"), 0);
    EXPECT_EQ(min_dest("a", "b"), 1);
    EXPECT_EQ(min_dest("a", ""), 1);
    EXPECT_EQ(min_dest("", "a"), 1);
}

TEST(dp, Q72_min_dest_rec_tests)
{
    EXPECT_EQ(min_dest_rec("abcc", "bcd"), 2);
    EXPECT_EQ(min_dest_rec("abc", "bcd"), 2);
    EXPECT_EQ(min_dest_rec("", ""), 0);
    EXPECT_EQ(min_dest_rec("a", "a"), 0);
    EXPECT_EQ(min_dest_rec("a", "b"), 1);
    EXPECT_EQ(min_dest_rec("a", ""), 1);
    EXPECT_EQ(min_dest_rec("", "a"), 1);
}

TEST(dp, Q10_is_match_tests)
{
    EXPECT_EQ(is_match("ab", ".*"), true);
    EXPECT_EQ(is_match("aaab", "c*a*b"), true);
    EXPECT_EQ(is_match("aaabd", "c*a*b"), false);
    EXPECT_EQ(is_match("daaab", "c*a*b"), false);
    EXPECT_EQ(is_match("mississippi", "mis*is*p*."), false);
}

TEST(dp, Q97_interleave_tests)
{
    EXPECT_EQ(interleave("ab", "bc", "abbc"), true);
    EXPECT_EQ(interleave("ab", "bc", "babc"), true);
    EXPECT_EQ(interleave("ab", "bc", "bacb"), true);
    EXPECT_EQ(interleave("ab", "bc", "bcab"), true);
    EXPECT_EQ(interleave("ab", "bc", "cbba"), false);
}

TEST(dp, Q1143_longest_common_sub_seq_tests)
{
    EXPECT_EQ(longest_common_sub_seq("", ""), 0);
    EXPECT_EQ(longest_common_sub_seq("", "bacqe"), 0);
    EXPECT_EQ(longest_common_sub_seq("ba", ""), 0);
    EXPECT_EQ(longest_common_sub_seq("abcc", "aabc"), 3);
    EXPECT_EQ(longest_common_sub_seq("abc", "def"), 0);
    EXPECT_EQ(longest_common_sub_seq("bdaccqwer", "bacqe"), 5);
}

TEST(dp, Q1143_longest_common_sub_seq_v2_tests)
{
    EXPECT_EQ(longest_common_sub_seq_v2("", ""), 0);
    EXPECT_EQ(longest_common_sub_seq_v2("", "bacqe"), 0);
    EXPECT_EQ(longest_common_sub_seq_v2("ba", ""), 0);
    EXPECT_EQ(longest_common_sub_seq_v2("abcc", "aabc"), 3);
    EXPECT_EQ(longest_common_sub_seq_v2("abc", "def"), 0);
    EXPECT_EQ(longest_common_sub_seq_v2("bdaccqwer", "bacqe"), 5);
}
