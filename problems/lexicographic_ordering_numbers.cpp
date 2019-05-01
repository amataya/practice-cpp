// Given an integer N, print numbers from 1 to N in lexicographic order.
// To be implemented without using character conversion (or Strings).
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
void ordered_numbers(long v, int n, vector<int>& r)
{
    if (v > n)
        return;
    for (int i = 0; i < 10; ++i)
    {
        if (v <= n)
            r.push_back(v);
        v *= 10;
        ordered_numbers(v, n, r);
        v /= 10;
        ++v;
        if (v % 10 == 0)
            return;
    }
}

vector<int> lexicographic_ordering_numbers(int n)
{
    if (n <= 0)
        return {0};
    vector<int> result;
    ordered_numbers(1, 25, result);
    return result;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Lexicographic ordering of numbers", "[bloomberg]")
{
    REQUIRE(lexicographic_ordering_numbers(25) ==
    vector<int>{1, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
                2, 20, 21, 22, 23, 24, 25,
                3, 4, 5, 6, 7, 8, 9});
}