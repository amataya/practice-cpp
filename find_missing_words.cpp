////////////////////////////////////////////////////////////////////////////////
// Given two strings. Second one is a subset of first. Find the missing words
//  Example: String 1 = "This is an example"
//           String 2 = "is example"
//          Answer: This, an
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <string>
#include <unordered_set>
#include <iostream>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
vector<string> find_missing_words(string str1, string str2)
{
    const string src = str1; //str1.size() > str2.size() ? str1 : str2;
    const string tgt = str2; //str1.size() > str2.size() ? str2 : str1;
    unordered_set<string> words;

    int i = 0, start = 0;
    for (;i < src.size(); ++i)
    {
        if (src[i] == ' ')
        {
            words.insert(src.substr(start, i - start));
            start = i + 1;
        }
    }

    words.insert(src.substr(start, i - start));

    for(i = 0, start = 0; i <= tgt.size(); ++i)
    {
        if (tgt[i] == ' ' || i == tgt.size())
        {
            auto iter = words.find(tgt.substr(start, i - start));
            if (iter != words.end())
                words.erase(iter);
            start = i + 1;
        }
    }
    vector<string> missing(words.begin(), words.end());
    return missing;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("First missing words between two strings", "[bloomberg]")
{
    REQUIRE(find_missing_words("This is an example", "is example") ==
    vector<string>{"an", "This"});
}