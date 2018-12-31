////////////////////////////////////////////////////////////////////////////////
// Given a string containing just the characters '(', ')', '{', '}', '[' and ']',
// determine if the input string is valid.
// An input string is valid if:
// - Open brackets must be closed by the same type of brackets.
// - Open brackets must be closed in the correct order.
// Note that an empty string is also considered valid.
//
// Example 1:
// Input: "()"
// Output: true
//
// Example 2:
// Input: "()[]{}"
// Output: true
//
// Example 3:
// Input: "(]"
// Output: false
//
// Example 4:
// Input: "([)]"
// Output: false
//
// Example 5:
// Input: "{[]}"
// Output: true
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <string>
#include <stack>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
bool isValid(string s)
{
    stack<int> order;
    int code = 0;
    for (const char& c : s)
    {
        switch (c)
        {
            case '{':
                code = 1;
                break;
            case '}':
                code = -1;
                break;
            case '(':
                code = 2;
                break;
            case ')':
                code = -2;
                break;
            case '[':
                code = 3;
                break;
            case ']':
                code = -3;
                break;
        }
        if (!order.empty() && order.top() == -code)
            order.pop();
        else
            order.push(code);
    }
    return order.empty();
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Valid Parentheses", "[leetcode]")
{
    REQUIRE(isValid("()"));
    REQUIRE(isValid("()[]{}"));
    REQUIRE_FALSE(isValid("(]"));
    REQUIRE_FALSE(isValid("([)]"));
    REQUIRE(isValid("{[]}"));
}