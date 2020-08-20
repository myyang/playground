#include <vector>

#include "gtest/gtest.h"

#include "binary_search.h"

TEST(binary_search, search_insert_position_tests)
{
    std::vector<int> even = {3,5,7,9};
    EXPECT_EQ (search_insert_position(even, 0), 0);
    EXPECT_EQ (search_insert_position(even, 3), 1);
    EXPECT_EQ (search_insert_position(even, 4), 1);
    EXPECT_EQ (search_insert_position(even, 5), 2);
    EXPECT_EQ (search_insert_position(even, 6), 2);
    EXPECT_EQ (search_insert_position(even, 7), 3);
    EXPECT_EQ (search_insert_position(even, 8), 3);
    EXPECT_EQ (search_insert_position(even, 9), 4);
    EXPECT_EQ (search_insert_position(even, 10), 4);

    std::vector<int> odd = {3,5,7};
    EXPECT_EQ (search_insert_position(odd, 0), 0);
    EXPECT_EQ (search_insert_position(odd, 3), 1);
    EXPECT_EQ (search_insert_position(odd, 4), 1);
    EXPECT_EQ (search_insert_position(odd, 5), 2);
    EXPECT_EQ (search_insert_position(odd, 7), 3);
    EXPECT_EQ (search_insert_position(odd, 8), 3);

    std::vector<int> duplicates = {5,5,7,7};
    EXPECT_EQ (search_insert_position(duplicates, 0), 0);
    EXPECT_EQ (search_insert_position(duplicates, 3), 0);
    EXPECT_EQ (search_insert_position(duplicates, 4), 0);
    EXPECT_EQ (search_insert_position(duplicates, 5), 2);
    EXPECT_EQ (search_insert_position(duplicates, 7), 4);
    EXPECT_EQ (search_insert_position(duplicates, 8), 4);
}

TEST(binary_search, search_range_tests)
{
    std::vector<int> duplicates = {5,5,7,7};
    std::vector<int> not_found = {-1, -1}, found_5 = {0, 1}, found_7 = {2, 3};
    EXPECT_EQ (search_range(duplicates, 0), not_found);
    EXPECT_EQ (search_range(duplicates, 5), found_5);
    EXPECT_EQ (search_range(duplicates, 7), found_7);
    EXPECT_EQ (search_range(duplicates, 8), not_found);
}
