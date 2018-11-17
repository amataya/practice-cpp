////////////////////////////////////////////////////////////////////////////////
// Implement atoi which converts a string to an integer.
//
// The function first discards as many whitespace characters as necessary until
// the first non-whitespace character is found. Then, starting from this
// character, takes an optional initial plus or minus sign followed by as
// many numerical digits as possible, and interprets them as a numerical value.
//
// The string can contain additional characters after those that form the
// integral number, which are ignored and have no effect on the behavior of
// this function.
//
// If the first sequence of non-whitespace characters in str is not a valid
// integral number, or if no such sequence exists because either str is empty
// or it contains only whitespace characters, no conversion is performed.
//
// If no valid conversion could be performed, a zero value is returned.
//
// Note:
//
// - Only the space character ' ' is considered as whitespace character.
// - Assume we are dealing with an environment which could only store integers
// within the 32-bit signed integer range: [−231,  231 − 1]. If the numerical
// value is out of the range of representable values, INT_MAX (2^31 − 1) or
// INT_MIN (−2^31) is returned.
//
// Example 1:
// Input: "42"
// Output: 42
//
// Example 2:
// Input: "   -42"
// Output: -42
// Explanation: The first non-whitespace character is '-', which is the minus
// sign.Then take as many numerical digits as possible, which gets 42.
//
// Example 3:
// Input: "4193 with words"
// Output: 4193
// Explanation: Conversion stops at digit '3' as the next character is not a
// numerical digit.
//
// Example 4:
// Input: "words and 987"
// Output: 0
// Explanation: The first non-whitespace character is 'w', which is not a
// numerical digit or a +/- sign. Therefore no valid conversion could be
// performed.
//
// Example 5:
// Input: "-91283472332"
// Output: -2147483648
// Explanation: The number "-91283472332" is out of the range of a 32-bit
// signed integer. Thefore INT_MIN (−231) is returned.
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <string>
#include <climits>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
int myAtoi(string str)
{
    if (str.size() == 0)
        return 0;

    int i = 0, sign = 1, num = 0;

    // Skip all leading spaces
    while (i < str.size() && str[i] == ' ')
        ++i;

    // Handle sign
    if (str[i] == '+' || str[i] == '-')
    {
        sign = (str[i] == '-') ? -1 : 1;
        ++i;
    }

    // Form the number
    // We divide the max/min by 10 because in next step we multiply by 10
    // if we multiply and test at the same time, it will exceed the limit
    while (i < str.size() && str[i] >= '0' && str[i] <= '9')
    {
        if (sign > 0 && (num > INT_MAX/10 || (num == INT_MAX/10 && str[i] >= '7')))
            return INT_MAX;
        else if (sign < 0 && (-num < INT_MIN/10 || (-num == INT_MIN/10 && str[i] >= '8')))
            return INT_MIN;
        else
            num = num * 10 + str[i] - '0';
        ++i;
    }
    return num * sign;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("String to Integer", "[leetcode]")
{
    REQUIRE(myAtoi("42") == 42);
    REQUIRE(myAtoi("   -42") == -42);
    REQUIRE(myAtoi("4193 with words") == 4193);
    REQUIRE(myAtoi("words and 987") == 0);
    REQUIRE(myAtoi("-91283472332") == -2147483648);
}