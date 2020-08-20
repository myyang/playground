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
