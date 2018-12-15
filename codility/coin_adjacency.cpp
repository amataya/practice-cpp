////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include <vector>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
// Scored 100% in this task
////////////////////////////////////////////////////////////////////////////////
int coin_adjacency(vector<int> A)
{
    int n = A.size();
    int result = 0;
    for (int i = 1; i < n; i++)
    {
        if (A[i - 1] == A[i])
            result = result + 1;
    }
    int r = (n > 1) ? (A[0] == A[1] ? -1 : 1) : 0;
    for (int i = 0; i < n; i++)
    {
        int count = 0;
        if (i > 0)
        {
            if (A[i - 1] != A[i])
                count = count + 1;
            else
                count = count - 1;
        }
        if (i < n - 1)
        {
            if (A[i + 1] != A[i])
                count = count + 1;
            else
                count = count - 1;
        }
        r = max(r, count);
    }
    return result + r;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Coin Adjancency", "[codility]")
{
    REQUIRE(coin_adjacency({1, 1, 1, 1, 1, 1}) == 4);
    REQUIRE(coin_adjacency({1, 1, 0, 1, 0, 0}) == 4);
    REQUIRE(coin_adjacency({1, 1, 1, 1, 0, 1}) == 5);
    REQUIRE(coin_adjacency({0, 1, 1, 1, 0, 1}) == 4);
    REQUIRE(coin_adjacency({1, 1, 0, 1, 0, 0, 1, 1}) == 5);
    REQUIRE(coin_adjacency({}) == 0);
    REQUIRE(coin_adjacency({1}) == 0);
    REQUIRE(coin_adjacency({1, 1}) == 0);
}