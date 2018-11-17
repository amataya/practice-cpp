// You have a total of n coins that you want to form in a staircase shape,
// where every k-th row must have exactly k coins.
// Given n, find the total number of full staircase rows that can be formed.
// n is a non-negative integer and fits within the range of a 32-bit signed
// integer.
//
// Example 1:
// n = 5
// The coins can form the following rows:
// ¤
// ¤ ¤
// ¤ ¤
// Because the 3rd row is incomplete, we return 2.
//
// Example 2:
// n = 8
// The coins can form the following rows:
// ¤
// ¤ ¤
// ¤ ¤ ¤
// ¤ ¤
// Because the 4th row is incomplete, we return 3.
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <cmath>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
int arrangeCoins(int n)
{
    // 1 + 2 + 3 + 4...  <= n. This is arithmetic progression.
    // Sum of n elements of arithmetic progression is (n * (n + 1) ) / 2
    // We are looking for: (x * (x + 1)) / 2 <= n
    // or x^2 + x <= 2n
    // or x^2 + x - 2n <= 0
    // Dividing all sides by 2
    // 0.5x^2 + 0.5x -n <= 0
    // Using the quadratic formula to get solution
    // (-b +/- sqrt(b^2 - 4ac)) / 2a
    // Taking only positive root
    // where a = 0.5, b = 0.5, c = -n, we get
    // -0.5 + sqrt(0.25 - 4*0.5*-n) = sqrt(0.25 + 2*n) - 0.5
    return static_cast<int>(sqrt(0.25 + 2.0 * n) - 0.5);
}
int arrangeCoins2(int n)
{
    int count = 1;
    while (n >= count)
        n -= count++;
    return count - 1;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Arranging Coins", "[leetcode]")
{
    REQUIRE(arrangeCoins(5) == 2);
    REQUIRE(arrangeCoins(8) == 3);
    REQUIRE(arrangeCoins(1) == 1);
    REQUIRE(arrangeCoins(1804289383) == 60070);
}