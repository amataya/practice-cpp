// Determine whether a given string of parentheses (multiple types) is properly
// nested.
//
// A string S consisting of N characters is considered to be properly nested
// if any of the following conditions is true:
//
// S is empty;
// S has the form "(U)" or "[U]" or "{U}" where U is a properly nested string;
// S has the form "VW" where V and W are properly nested strings.
//
// For example, the string "{[()()]}" is properly nested but "([)()]" is not.
//
// Write a function:
//
// int solution(string &S);
//
// that, given a string S consisting of N characters, returns 1 if S is
// properly nested and 0 otherwise.
//
// For example, given S = "{[()()]}", the function should return 1 and
// given S = "([)()]", the function should return 0, as explained above.
//
// Write an efficient algorithm for the following assumptions:
//
// - N is an integer within the range [0..200,000];
// - string S consists only of the following characters:
//  "(", "{", "[", "]", "}" and/or ")".
//
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <string>
#include <stack>
#include <unordered_map>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
int string_nested0(const string s)
{
    // If the number of characters is not even then the string is unbalanced
    if (s.size() % 2 > 0)
        return 0;

    unordered_map<char, char> tokens;
    tokens.insert({'(', ')'});
    tokens.insert({')', '('});
    tokens.insert({'[', ']'});
    tokens.insert({']', '['});
    tokens.insert({'{', '}'});
    tokens.insert({'}', '{'});

    stack<char> order;
    for(const char &c : s)
    {
        if (order.empty())
            order.push(c);
        else if (c == tokens[order.top()])
            order.pop();
        else
            order.push(c);
    }
    return order.empty() ? 1 : 0;
}

int string_nested(const string s)
{
    // If the number of characters is not even then the string is unbalanced
    if (s.size() % 2 > 0)
        return 0;

    stack<char> order;
    bool to_pop = false;
    for (const char &c : s)
    {
        switch (c)
        {
            case '(':
            case '[':
            case '{':
                // Push happens in else-statement below
                break;
            case ')':
                to_pop = order.top() == '(';
                break;
            case ']':
                to_pop = order.top() == '[';
                break;
            case '}':
                to_pop = order.top() == '{';
                break;
        }

        to_pop ? order.pop() : order.push(c);
        to_pop = false;
    }
    return order.empty() ? 1 : 0;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("String is Nested", "[codility]")
{
    REQUIRE(string_nested("{[()()]}") == 1);
    REQUIRE(string_nested("([)()]") == 0);
    REQUIRE(string_nested0("{[()()]}") == 1);
    REQUIRE(string_nested0("([)()]") == 0);
}