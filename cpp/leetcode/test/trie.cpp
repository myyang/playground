#include <vector>
#include <string>
#include <tuple>

#include "gtest/gtest.h"

#include "trie.h"

typedef std::tuple<std::string, bool> trie_result_t;

TEST(trie, Q208_implement_trie_array_tests)
{
    TrieArray* t = new TrieArray();
    std::vector<std::string> words = {"abc", "abd", "xcode"};

    for (std::string word: words) t->insert(word);

    std::vector<trie_result_t> results = {
        std::make_tuple("abc", true),
        std::make_tuple("abe", false),
        std::make_tuple("xcodec", false),
    };

    for (trie_result_t r: results)
    {
        std::string word;
        bool result;
        std::tie(word, result) = r;
        EXPECT_EQ(t->search(word), result);
    }
}

TEST(trie, Q208_implement_trie_map_tests)
{
    TrieMap* t = new TrieMap();
    std::vector<std::string> words = {"abc", "abd", "xcode"};

    for (std::string word: words) t->insert(word);

    std::vector<trie_result_t> results = {
        std::make_tuple("abc", true),
        std::make_tuple("abe", false),
        std::make_tuple("xcodec", false),
    };

    for (trie_result_t r: results)
    {
        std::string word;
        bool result;
        std::tie(word, result) = r;
        EXPECT_EQ(t->search(word), result);
    }
}
