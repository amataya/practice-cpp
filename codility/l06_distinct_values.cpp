// Write a function
//
// int solution(vector<int> &A);
//
// that, given an array A consisting of N integers, returns the number of
// distinct values in array A.
//
// For example, given array A consisting of six elements such that:
// A[0] = 2    A[1] = 1    A[2] = 1
// A[3] = 2    A[4] = 3    A[5] = 1
//
// the function should return 3, because there are 3 distinct values
// appearing in array A, namely 1, 2 and 3.
//
// Write an efficient algorithm for the following assumptions:
//
// N is an integer within the range [0..100,000];
// each element of array A is an integer within the range [−1,000,000..1,000,000].
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <set>
#include <algorithm>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
int distinct_values(vector<int> A)
{
    if (A.size() < 2)
        return A.size();

    int distinct = 0;
    sort(A.begin(), A.end());
    for (size_t i = 0; i < A.size(); ++i)
    {
        ++distinct;
        for(; (i < A.size() - 1) && (A[i] == A[i + 1]); ++i);
    }
    return distinct;
}

int distinct_values2(const vector<int> A)
{
    if (A.size() == 0)
        return 0;

    set<int> unique;
    for(const auto& i : A)
        unique.insert(i);

    return unique.size();
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Distinct Values", "[codility]")
{
    REQUIRE(distinct_values({2, 1, 1, 2, 3, 1}) == 3);
    REQUIRE(distinct_values2({2, 1, 1, 2, 3, 1}) == 3);
}
