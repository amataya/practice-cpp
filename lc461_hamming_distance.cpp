// The Hamming distance between two integers is the number of positions at which
// the corresponding bits are different.
// Given two integers x and y, calculate the Hamming distance.
// Note: 0 ≤ x, y < 231.
//
// Example:
// Input: x = 1, y = 4
// Output: 2
// Explanation:
// 1   (0 0 0 1)
// 4   (0 1 0 0)
//        ↑   ↑
// The above arrows point to positions where the corresponding bits are different.
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
int hammingDistance(int x, int y)
{
    int distance = 0;
    int val = x ^ y;
    while (val != 0)
    {
        ++distance;
        val &= val - 1;
    }
    return distance;
}
int hammingDistance2(int x, int y)
{
    // using intrinsic function
    return __builtin_popcount(x ^ y);
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Hamming Distance", "[leetcode]")
{
    REQUIRE(hammingDistance(1, 4) == 2);
    REQUIRE(hammingDistance2(1, 4) == 2);
}