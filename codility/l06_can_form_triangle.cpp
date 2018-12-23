// Determine whether a triangle can be built from a given set of edges.
//
// An array A consisting of N integers is given. A triplet (P, Q, R) is
// triangular if 0 ≤ P < Q < R < N and:
//
// A[P] + A[Q] > A[R],
// A[Q] + A[R] > A[P],
// A[R] + A[P] > A[Q].
//
// For example, consider array A such that:
// A[0] = 10    A[1] = 2    A[2] = 5
// A[3] = 1     A[4] = 8    A[5] = 20
//
// Triplet (0, 2, 4) is triangular.
//
// Write a function:
//
// int solution(vector<int> &A);
//
// that, given an array A consisting of N integers, returns 1 if there
// exists a triangular triplet for this array and returns 0 otherwise.
//
// For example, given array A such that:
// A[0] = 10    A[1] = 2    A[2] = 5
// A[3] = 1     A[4] = 8    A[5] = 20
//
// the function should return 1, as explained above. Given array A such that:
// A[0] = 10    A[1] = 50    A[2] = 5
// A[3] = 1
//
// the function should return 0.
//
// Write an efficient algorithm for the following assumptions:
//
// N is an integer within the range [0..100,000];
// each element of array A is an integer within the range
//  [−2,147,483,648 ... 2,147,483,647].
//
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <climits>
#include <algorithm>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
// If we sort the array, then we have guaranteed that P + R > Q and Q + R > P
// (because R is always the biggest). Now what remains, is the proof that
// P + Q > R, that can be found out by traversing the array.
// Thus we need to find three adjacent values as they provide the highest
// P and Q.
int can_form_triangle(vector<int> A)
{
    if (A.size() < 3)
        return 0;

    sort(A.begin(), A.end());
    for (size_t i = 0; i < A.size() - 2; ++i)
        if (long(A[i]) + A[i + 1] > A[i + 2])
            return 1;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Triangle Possible?", "[codility]")
{
    REQUIRE(can_form_triangle({10, 1, 5, 1, 8, 20}) == 1);
    REQUIRE(can_form_triangle({10, 50, 5, 1}) == 0);
    REQUIRE(can_form_triangle({10, 10, 10}) == 1);
    REQUIRE(can_form_triangle({INT_MAX, INT_MAX, INT_MAX}) == 1);
    REQUIRE(can_form_triangle({INT_MIN, INT_MIN, INT_MIN}) == 1);
}