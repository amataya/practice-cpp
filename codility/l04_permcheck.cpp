// A non-empty array A consisting of `N` integers is given. A permutation is a
// sequence containing each element from `1` to `N` once, and only once.
// For example, array `A` such that:
//     A[0] = 4
//     A[1] = 1
//     A[2] = 3
//     A[3] = 2
// is a permutation, but array A such that:
//     A[0] = 4
//     A[1] = 1
//     A[2] = 3
// is not a permutation, because value 2 is missing.
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>

using namespace std;
////////////////////////////////////////////////////////////////////////////////

int permcheck(vector<int> A)
{
    vector<bool> visited(A.size());
    for (const int& e : A)
    {
        if (e <= 0 || e > A.size())
            return 0;
        if (visited[e - 1])
            return 0;
        visited[e - 1] = true;
    }
    return 1;
}


////////////////////////////////////////////////////////////////////////////////

/*
TEST_CASE("Test with zero", "[classic]")
{
    REQUIRE(fizzbuzz(0) == "0");
}
*/