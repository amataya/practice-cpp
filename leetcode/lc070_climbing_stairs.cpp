////////////////////////////////////////////////////////////////////////////////
// You are climbing a stair case. It takes n steps to reach to the top.
// Each time you can either climb 1 or 2 steps. In how many distinct ways can
// you climb to the top?
// Note: Given n will be a positive integer.
// Example 1:
//      Input: 2
//      Output: 2
//      Explanation: There are two ways to climb to the top.
//          1. 1 step + 1 step
//          2. 2 steps
// Example 2:
//      Input: 3
//      Output: 3
//      Explanation: There are three ways to climb to the top.
//          1. 1 step + 1 step + 1 step
//          2. 1 step + 2 steps
//          3. 2 steps + 1 step
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;
////////////////////////////////////////////////////////////////////////////////
// The key here to note is that the distinct ways form a fibonacci sequence
// So one needs to generate the nth digit in fibonacci sequence
int climbStairs(int n)
{
    if (n < 3)
        return n;
    int a = 1, b = 1;
    for (int i = 2; i <= n; ++i)
    {
        b = a + b;
        a = b - a;
    }
    return b;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Test Climbing Stairs", "[leetcode]")
{
    REQUIRE(climbStairs(2) == 2);
    REQUIRE(climbStairs(3) == 3);
}