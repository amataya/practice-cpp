////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;
////////////////////////////////////////////////////////////////////////////////
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