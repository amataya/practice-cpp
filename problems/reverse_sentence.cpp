//
// Reverse words within a sentence, in place.
//
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <string>
#include <algorithm>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
void reverse_sentence(string& sentence)
{
    int i = 0, j = 0, k = 0;

    // Reverse individual words
    while(i < sentence.size())
    {
        while (sentence[k] != ' ' && k < sentence.size())
            ++k;
        j = k - 1;
        while (j > i)
            swap(sentence[i++], sentence[j--]);
        i = ++k;
    }

    // Reverse whole sentence
    for (i = 0, j = j = sentence.size() - 1; j > i; --j, ++i)
        swap(sentence[j], sentence[i]);
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Reverse words in a sentence in place", "[bloomberg]")
{
    string sentence("hello world");
    reverse_sentence(sentence);
    REQUIRE(sentence == "world hello");

    sentence = "hello there everyone";
    reverse_sentence(sentence);
    REQUIRE(sentence == "everyone there hello");

    sentence = "hello";
    reverse_sentence(sentence);
    REQUIRE(sentence == "hello");
}