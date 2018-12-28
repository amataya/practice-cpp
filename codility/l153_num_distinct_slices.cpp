//  Count the number of distinct slices (containing only unique numbers).
//
// An integer M and a non-empty array A consisting of N non-negative integers
// are given. All integers in array A are less than or equal to M.
//
// A pair of integers (P, Q), such that 0 ≤ P ≤ Q < N, is called a slice of
// array A. The slice consists of the elements A[P], A[P + 1], ..., A[Q].
// A distinct slice is a slice consisting of only unique numbers. That is,
// no individual number occurs more than once in the slice.
//
// For example, consider integer M = 6 and array A such that:
// A[0] = 3
// A[1] = 4
// A[2] = 5
// A[3] = 5
// A[4] = 2
//
// There are exactly nine distinct slices: (0, 0), (0, 1), (0, 2), (1, 1),
// (1, 2), (2, 2), (3, 3), (3, 4) and (4, 4).
//
// The goal is to calculate the number of distinct slices.
//
// Write a function:
//
// int solution(int M, vector<int> &A);
//
// that, given an integer M and a non-empty array A consisting of N integers,
// returns the number of distinct slices.
//
// If the number of distinct slices is greater than 1,000,000,000, the function
// should return 1,000,000,000.
//
// For example, given integer M = 6 and array A such that:
// A[0] = 3
// A[1] = 4
// A[2] = 5
// A[3] = 5
// A[4] = 2
//
// the function should return 9, as explained above.
//
// Write an efficient algorithm for the following assumptions:
//
// N is an integer within the range [1..100,000];
// M is an integer within the range [0..100,000];
// each element of array A is an integer within the range [0..M].
//
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
// Using the caterpillar method expand the caterpillar to the right as long as
// a duplicate element is found. We then in a way retract to find the position
// from which next slice needs to be started.
// An observation showed that the number of sub-slices is equal to front-back+1.
int num_distinct_slices(const int M, const vector<int> &A)
{
    const int UPPER_LIMIT = 1000000000;
    int num_slices = 0, back = 0;
    vector<bool> seen(M + 1);
    for (size_t i = 0; i < A.size(); ++i)
    {
        const int &num = A[i];
        if (!seen[num])
        {
            seen[num] = true;
            num_slices += i - back + 1;
        }
        else
        {
            while(A[back] != num)
            {
                seen[A[back]] = false;
                ++back;
            }
            ++back;
            num_slices += i - back + 1;
        }
        if (num_slices > UPPER_LIMIT)
            return UPPER_LIMIT;
    }
    return num_slices;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Num Distinct Slices", "[codility]")
{
    REQUIRE(num_distinct_slices(6, {3, 4, 5, 5, 2}) == 9);
}