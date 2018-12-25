// Find a maximum sum of a compact subsequence of array elements.
//
// A non-empty array A consisting of N integers is given. A pair of integers
// (P, Q), such that 0 ≤ P ≤ Q < N, is called a slice of array A. The sum of a
// slice (P, Q) is the total of A[P] + A[P+1] + ... + A[Q].
//
// Write a function:
//
// int solution(vector<int> &A);
//
// that, given an array A consisting of N integers, returns the maximum sum of
// any slice of A.
//
// For example, given array A such that:
// A[0] = 3  A[1] = 2  A[2] = -6
// A[3] = 4  A[4] = 0
//
// the function should return 5 because:
//
// (3, 4) is a slice of A that has sum 4,
// (2, 2) is a slice of A that has sum −6,
// (0, 1) is a slice of A that has sum 5,
// no other slice of A has sum greater than (0, 1).
//
// Write an efficient algorithm for the following assumptions:
//
// N is an integer within the range [1..1,000,000];
// each element of array A is an integer within the range [−1,000,000..1,000,000]
// the result will be an integer within the range [−2,147,483,648..2,147,483,647]
//
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
// Init values are very important when dealing with negative numbers and so is
// comparison with n in first max. Using INT_MIN will cause addition to overflow.
int max_slice_sum(const vector<int> &A)
{
    int max_ending_here = -1000001, max_slice_sum = -1000001;
    for(const auto &n : A)
    {
        max_ending_here = max(n, max_ending_here + n);
        max_slice_sum = max(max_slice_sum, max_ending_here);
    }
    return max_slice_sum;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Maximum Sum Slice", "[codility]")
{
    REQUIRE(max_slice_sum({3, 2, -6, 4, 0}) == 5);
    REQUIRE(max_slice_sum({-10}) == -10);
}
