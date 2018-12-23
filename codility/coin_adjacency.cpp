////////////////////////////////////////////////////////////////////////////////
// Codility Fix Bug Task - Scored 100% in this task
////////////////////////////////////////////////////////////////////////////////
// Consider N coins aligned in a row. Each coin is showing either heads or tails.
// The adjacency of these coins is the number of adjacent pairs of coins with
// the same side facing up.
//
// Write a C++ function
//
// int solution(const vector<int> &A);
//
// that, given a non-empty zero-indexed array A consisting of N integers
// representing the coins, returns the maximum possible adjacency that can be
// obtained by reversing exactly one coin (that is, one of the coins must be
// reversed). Consecutive elements of array A represent consecutive coins in
// the row. Array A contains only 0s and/or 1s:
//
//     0 represents a coin with heads facing up;
//     1 represents a coin with tails facing up.
//
// For example, given array A consisting of eight numbers, such that:
//
// A[0] = 1
// A[1] = 1
// A[2] = 0
// A[3] = 1
// A[4] = 0
// A[5] = 0
// A[6] = 1
// A[7] = 1
//
// the function should return 5. The initial adjacency is 3, as there are three
// pairs of adjacent coins with the same side facing up, namely (0, 1), (4, 5)
// and (6, 7). After reversing the coin represented by A[2], the adjacency
// equals 5, as there are five pairs of adjacent coins with the same side
// facing up, namely: (0, 1), (1, 2), (2, 3), (4, 5) and (6, 7), and it is
// not possible to obtain a higher adjacency.
//
// The same adjacency can be obtained by reversing the coin represented by A[3].
//
// Assume that:
// - N is an integer within the range [1..100,000];
// - each element of array A is an integer within the range [0..1].
// http://ruslanledesma.com/2016/02/14/adjacent-coins.html
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include <vector>

using namespace std;
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