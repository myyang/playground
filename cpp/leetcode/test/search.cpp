#include <vector>
#include <string>

#include "gtest/gtest.h"

#include "search.h"


TEST(search, letter_combination_tests)
{
    std::vector<std::string> exp = {};
    EXPECT_EQ (letter_combination(""), exp);

    std::vector<std::string> exp2 = {"a", "b", "c"};
    EXPECT_EQ (letter_combination("2"), exp2);

    std::vector<std::string> exp20 = {"a ", "b ", "c "};
    EXPECT_EQ (letter_combination("20"), exp20);

    std::vector<std::string> exp27 = {"ap", "aq", "ar", "as", "bp", "bq", "br", "bs", "cp", "cq", "cr", "cs"};
    EXPECT_EQ (letter_combination("27"), exp27);

    std::vector<std::string> exp23 = {"ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"};
    EXPECT_EQ (letter_combination("23"), exp23);

    std::vector<std::string> exp13 = {"d", "e", "f"};
    EXPECT_EQ (letter_combination("13"), exp13);

    std::vector<std::string> exp1 = {};
    EXPECT_EQ (letter_combination("1"), exp1);
}
