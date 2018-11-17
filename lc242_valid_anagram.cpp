////////////////////////////////////////////////////////////////////////////////
// Given two strings s and t , write a function to determine if t is an anagram
// of s.
//
// Example 1:
// Input: s = "anagram", t = "nagaram"
// Output: true
//
// Example 2:
// Input: s = "rat", t = "car"
// Output: false
//
// Note: You may assume the string contains only lowercase alphabets.
// Follow up: What if the inputs contain unicode characters? How would you adapt
// your solution to such case?
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <string>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
bool isAnagram(string s, string t)
{
    if (s.size() != t.size())
        return false;
    int characters[26] = {0};
    int i = 0;
    for (; i < s.size(); ++i)
    {
        characters[s[i] - 'a']++;
        characters[t[i] - 'a']--;
    }
    for (i = 0; i < 26; ++i)
        if (characters[i] != 0)
            return false;
    return true;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Valid Anagram", "[leetcode]")
{
    REQUIRE(isAnagram("anagram", "nagaram"));
    REQUIRE_FALSE(isAnagram("rat", "car"));
}
