// Determine whether a given string of parentheses (single type) is properly
// nested.
//
// A string S consisting of N characters is called properly nested if:
// - S is empty;
// - S has the form "(U)" where U is a properly nested string;
// - S has the form "VW" where V and W are properly nested strings.
//
// For example, string "(()(())())" is properly nested but string "())" isn't.
//
// Write a function:
//
// int solution(string &S);
//
// that, given a string S consisting of N characters, returns 1 if string S
// is properly nested and 0 otherwise.
//
// For example, given S = "(()(())())", the function should return 1 and
// given S = "())", the function should return 0, as explained above.
//
// Write an efficient algorithm for the following assumptions:
//
// - N is an integer within the range [0..1,000,000];
// - string S consists only of the characters "(" and/or ")".
//
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <string>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
// If the string is odd size it cannot be balanced
int balanced_braces(const string S)
{
    if (S.empty())
        return 1;

    if (S.size() % 2 > 0)
        return 0;

    int counter = 0;
    for(const char &c : S)
    {
        counter += c == ')' ? -1 : 1;
        if (counter < 0) // Invalid nesting - Not allowed
            return 0;
    }
    return counter == 0 ? 1 : 0;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Braces are balanced", "[codility]")
{
    REQUIRE(balanced_braces("(()(())())") == 1);
    REQUIRE(balanced_braces("())") == 0);
}