////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "trie.h"

using namespace std;
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Trie", "[classic]")
{
    // Initialize Trie
    Trie::TrieNode *root = new Trie::TrieNode();
    Trie::add_word(root, "word");
    Trie::add_word(root, "wonder");
    Trie::add_word(root, "alphabet");
    Trie::add_word(root, "soup");
    Trie::add_word(root, "sulphur");
    Trie::add_word(root, "wind");
    Trie::add_word(root, "whale");
    Trie::add_word(root, "artist");
    Trie::add_word(root, "palace");

    CHECK(Trie::find_word(root, "wonder"));
    CHECK_FALSE(Trie::find_word(root, "wonderful"));
    CHECK_FALSE(Trie::find_word(root, "annoy"));
    CHECK(Trie::find_word(root, "artist"));

    Trie::destroy_trie(root);
}
