// Given a 32-bit signed integer, reverse digits of an integer.
//
// Example 1:
// Input: 123
// Output: 321
//
// Example 2:
// Input: -123
// Output: -321
//
// Example 3:
// Input: 120
// Output: 21
//
// Note:
// Assume we are dealing with an environment which could only store integers
// within the 32-bit signed integer range: [−231,  231 − 1]. For the purpose of
// this problem, assume that your function returns 0 when the reversed
// integer overflows.
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <climits>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
int reverse(int x)
{
    int result = 0;
    while (x != 0)
    {
        if (result > INT_MAX/10 || result < INT_MIN/10)
            return 0;
        result = result * 10 + x % 10;
        x /= 10;
    }
    return result;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Reverse Integer", "[leetcode]")
{
    REQUIRE(reverse(123) == 321);
    REQUIRE(reverse(-123) == -321);
    REQUIRE(reverse(120) == 21);
}