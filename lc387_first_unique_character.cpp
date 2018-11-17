////////////////////////////////////////////////////////////////////////////////
// Given a string, find the first non-repeating character in it and return
// it's index. If it doesn't exist, return -1.
//
// Examples:
// s = "leetcode"
// return 0.
//
// s = "loveleetcode",
// return 2.
// Note: You may assume the string contain only lowercase letters.
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <string>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
int firstUniqChar(string s)
{
    vector<int> visited(26, 0);
    for(const char& c : s)
        visited[c - 'a']++;
    for (int i = 0; i < s.size(); ++i)
        if (visited[s[i] - 'a'] == 1)
            return i;
    return -1;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("First Unique Character", "[leetcode]")
{
    REQUIRE(firstUniqChar("leetcode") == 0);
    REQUIRE(firstUniqChar("loveleetcode") == 2);
}