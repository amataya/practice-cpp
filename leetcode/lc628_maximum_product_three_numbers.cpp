// Given an integer array, find three numbers whose product is maximum and
// output the maximum product.  When considering maximum ignore the sign but the
// final result should not ignore sign.
//
// Example 1:
// Input: [1,2,3]
// Output: 6
//
// Example 2:
// Input: [1,2,3,4]
// Output: 24
//
// Note:
// - The length of the given array will be in range [3,104] and all elements are
// in the range [-1000, 1000].
// - Multiplication of any three numbers in the input won't exceed the range of
// 32-bit signed integer.
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <climits>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
int maximumProduct(vector<int> nums)
{
    int max1 = INT_MIN, max2 = INT_MIN, max3 = INT_MIN,
        min1 = INT_MAX, min2 = INT_MAX; // To cater for negative numbers
    for (const auto& n : nums)
    {
        if (n > max1)
        {
            max3 = max2;
            max2 = max1;
            max1 = n;
        }
        else if (n> max2)
        {
            max3 = max2;
            max2 = n;
        }
        else if (n > max3)
        {
            max3 = n;
        }

        if (n < min1)
        {
            min2 = min1;
            min1 = n;
        }
        else if (n < min2)
        {
            min2 = n;
        }
    }
    return max(max1 * max2 * max3, min1 * min2 * max1);
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Maximum Product of Three Numbers", "[leetcode]")
{
    REQUIRE(maximumProduct({1,2,3}) == 6);
    REQUIRE(maximumProduct({1,2,3,4}) == 24);
    REQUIRE(maximumProduct({-1,-2,-3,-4, 60}) == 720);
}