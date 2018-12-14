#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <iostream>

using namespace std;

int coin_adjacency_sum(vector<int> A) {
    int n = A.size();
    int result = 0;
    for (int i = 0; i < n - 1; i++) {
        if (A[i] == A[i + 1])
            result = result + 1;
    }
    int r = 0;
    for (int i = 0; i < n; i++) {
        int count = 0;
        if (i > 0) {
            if (A[i - 1] != A[i])
                count = count + 1;
            else
                count = count - 1;
        }
        if (i < n - 1) {
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
TEST_CASE("Coin Adjacency Sum", "[classic]")
{
    REQUIRE(coin_adjacency_sum({1, 1, 0, 1, 1, 0})  == 5);
}