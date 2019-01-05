// Given a string, find the length of the longest substring without repeating
// characters.
//
// Example 1:
//
// Input: "abcabcbb"
// Output: 3
// Explanation: The answer is "abc", with the length of 3.
//
// Example 2:
//
// Input: "bbbbb"
// Output: 1
// Explanation: The answer is "b", with the length of 1.
//
// Example 3:
//
// Input: "pwwkew"
// Output: 3
// Explanation: The answer is "wke", with the length of 3.
// Note that the answer must be a substring, "pwke" is a subsequence and not
// a  substring.
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <string>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
// There is a difference between substring and subsequence
// Subsequence can jump characters. Substring cannot.

// Set two pointers, i and j, scan the string from the start to the end.
// Set a tracker to find if the character has occurred.
// - If character has occurred so far, compute current length and compare it to
// the max length and move our window. The set the occurrence to false.
// - If not, keep extending the right limit of our window.
// Picture this solution as a window moving over the string. The boundaries
// of window are given by i and j.
int lengthOfLongestSubstring(const string& s)
{
    if (s.empty())
        return 0;
    if (s.size() == 1)
        return 1;
    int i = 0, j = 0, index = 0, max_length = 0;
    // ASCII printable character range is from 32 to 255 = 223
    vector<bool> tracker(256);
    while (i < s.size() && j < s.size())
    {
        index = s[j]; // promotion from char to int
        if (tracker[index]) // We have seen this character before
        {
            max_length = max(max_length, j - i);
            index = s[i];
            tracker[index] = false;
            ++i; // Move the start point of window
        }
        else
        {
            tracker[index] = true;
            max_length = max(max_length, j - i + 1);
            ++j; // Keep pushing the end-point of our window
        }
    }
    return max_length;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Longest substring without repeating characters", "[leetcode]")
{
    REQUIRE(lengthOfLongestSubstring("abcabcbb") == 3);
    REQUIRE(lengthOfLongestSubstring("bbbbb") == 1);
    REQUIRE(lengthOfLongestSubstring("pwwkew") == 3);
    REQUIRE(lengthOfLongestSubstring(" ") == 1);
}