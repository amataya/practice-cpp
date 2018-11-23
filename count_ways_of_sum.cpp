//
// Given an integer n, return the number of ways it can be represented as a sum
// of 1s and 2s, order matters.
//
// Example: n = 3
// 1 + 1 + 1 | 1 + 2 | 2 + 1  = 3 ways
// Example: n = 4
// 1 + 1 + 1 + 1 | 2 + 2 | 2 + 1 + 1 | 1 + 2 + 1 | 1 + 1 + 2 = 5 ways
// Example: n = 5
// 1 + 1 + 1 + 1 | 2 + 2 + 1 | 1 + 2 + 2 | 1 + 1 + 1 + 2 | 2 + 1 + 1 + 1
// 1 + 2 + 1 + 1 | 1 + 1 + 2 + 1 | 2 + 1 + 2 = 8 ways
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <string>
#include <algorithm>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
// The key here to note is that the distinct ways form a fibonacci sequence
// So one needs to generate the nth digit in fibonacci sequence
int ways_of_sum(int n)
{
    int a = 1, b = 1;
    for (int i = 2; i <= n; ++i)
    {
        b = b + a;
        a = b - a;
    }
    return b;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Test number of ways to sum", "[bloomberg]")
{
    REQUIRE(ways_of_sum(3) == 3);
    REQUIRE(ways_of_sum(4) == 5);
    REQUIRE(ways_of_sum(5) == 8);
}