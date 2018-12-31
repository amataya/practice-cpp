////////////////////////////////////////////////////////////////////////////////
// Write a function that takes a string as input and returns the string reversed.
// Example 1:
// Input: "hello"
// Output: "olleh"
//
// Example 2:
// Input: "A man, a plan, a canal: Panama"
// Output: "amanaP :lanac a ,nalp a ,nam A"
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <string>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
string reverseString(string s)
{
    char c;
    for(int i = 0, j = s.size() - 1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }

    return s;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Reverse String", "[leetcode]")
{
    REQUIRE(reverseString("hello") == "olleh");
    REQUIRE(reverseString("A man, a plan, a canal: Panama") == "amanaP :lanac a ,nalp a ,nam A");
}