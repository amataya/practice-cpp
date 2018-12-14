// Given a string containing digits from 2-9 inclusive, return all possible
// letter combinations that the number could represent.
// A mapping of digit to letters (just like on the telephone buttons) is given
// below. Note that 1 does not map to any letters.
//
// Example:
// Input: "23"
// Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <string>
#include <algorithm>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
vector<string> letterCombinations(string digits)
{
    if (digits.empty())
        return {};

    // Clang will warn that the destructor of this object will be executed
    // at exit time. Global and function static objects will get their
    // destructors called when your application is exiting. These destructors
    // are "exit time destructors". and are called in the reverse order
    // that they were constructed in. The warning is only to seek attention.
    static const string mapping[] = {"", "", "abc", "def", "ghi", "jkl",
                                    "mno", "pqrs", "tuv", "wxyz"};

    int i = 0, j = 0, k = 0, index = 0;

    vector<string> result;
    result.push_back("");
    for (i = 0; i < digits.size(); ++i)
    {
        index = digits[i] - '0';
        if (index < 0 || index > 9)
            break;
        vector<string> tmp;
        const auto chars = mapping[index];
        for (j = 0; j < chars.size(); ++j)
            for (k = 0; k < result.size(); ++k)
                tmp.push_back(result[k] + chars[j]);
        result.swap(tmp);
    }

    sort(result.begin(), result.end());
    return result;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Letter combination of phone number", "[leetcode]")
{
    REQUIRE(letterCombinations("23") ==
    vector<string>{"ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"});
}