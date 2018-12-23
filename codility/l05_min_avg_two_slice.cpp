// Find the minimal average of any slice containing at least two elements.
// A non-empty array A consisting of N integers is given.
// A pair of integers (P, Q), such that 0 ≤ P < Q < N, is called a slice of
// array A (notice that the slice contains at least two elements). The average
// of a slice (P, Q) is the sum of A[P] + A[P + 1] + ... + A[Q] divided by the
// length of the slice.
// To be precise, the average equals (A[P] + A[P + 1] + ... + A[Q]) / (Q − P + 1).
//
// For example, array A such that:
// A[0] = 4
// A[1] = 2
// A[2] = 2
// A[3] = 5
// A[4] = 1
// A[5] = 5
// A[6] = 8
//
// contains the following example slices:
//
// slice (1, 2), whose average is (2 + 2) / 2 = 2;
// slice (3, 4), whose average is (5 + 1) / 2 = 3;
// slice (1, 4), whose average is (2 + 2 + 5 + 1) / 4 = 2.5.
//
// The goal is to find the starting position of a slice whose average is minimal.
//
// Write a function:
//
// int solution(vector<int> &A);
//
// that, given a non-empty array A consisting of N integers, returns the
// starting position of the slice with the minimal average. If there is more
// than one slice with a minimal average, you should return the smallest
// starting position of such a slice.
//
// Write an efficient algorithm for the following assumptions:
//
// N is an integer within the range [2..100,000];
// each element of array A is an integer within the range [−10,000..10,000].
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
// Every slice must be of size two or three. Slices of bigger sizes are created
// from such smaller slices. Therefore should any bigger slice have an optimal
// value, all sub-slices must be the same, for this case to hold true.
// If the sub-slices have different averages, some of them will have smaller
// average than minimum average. But it conflicts with the condition that,
// the minimum average is known as the global minimal average for all slices.
// By this contradictory, it's proved that all the sub-slices MUST
// have the same average.
// Therefore we check all possible slices of size 2/3 and return the smallest one.
int min_average_slice(vector<int> A)
{
    if (A.size() < 3)
        return 0;

    double min_avg = (A[0] + A[1]) / 2.0;
    double avg = 0;
    size_t i = 0, min_avg_index = 0;
    for (; i < A.size() - 2; ++i)
    {
        avg =  (A[i] + A[i + 1]) / 2.0;
        if (avg < min_avg)
        {
            min_avg = avg;
            min_avg_index = i;
        }
        avg =  (A[i] + A[i + 1] + A[i + 2]) / 3.0;
        if (avg < min_avg)
        {
            min_avg = avg;
            min_avg_index = i;
        }
    }
    // Try the last 2 element slice
    avg =  (A[i] + A[i + 1]) / 2.0;
    if (avg < min_avg)
        min_avg_index = i;

    return min_avg_index;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Minimum Average Two Slice", "[codility]")
{
    REQUIRE(min_average_slice({{4, 2, 2, 5, 1, 5, 8}}) == 1);
}
