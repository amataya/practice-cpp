//  Find the maximal sum of any double slice.
//
// A non-empty array A consisting of N integers is given.
//
// A triplet (X, Y, Z), such that 0 ≤ X < Y < Z < N, is called a double slice.
//
// The sum of double slice (X, Y, Z) is the total of
// A[X + 1] + A[X + 2] + ... + A[Y − 1] + A[Y + 1] + A[Y + 2] + ... + A[Z − 1].
//
// For example, array A such that:
// A[0] = 3
// A[1] = 2
// A[2] = 6
// A[3] = -1
// A[4] = 4
// A[5] = 5
// A[6] = -1
// A[7] = 2
//
// contains the following example double slices:
//
// double slice (0, 3, 6), sum is 2 + 6 + 4 + 5 = 17,
// double slice (0, 3, 7), sum is 2 + 6 + 4 + 5 − 1 = 16,
// double slice (3, 4, 5), sum is 0.
//
// The goal is to find the maximal sum of any double slice.
//
// Write a function:
//
// int solution(vector<int> &A);
//
// that, given a non-empty array A consisting of N integers, returns the
// maximal sum of any double slice.
//
// For example, given:
// A[0] = 3
// A[1] = 2
// A[2] = 6
// A[3] = -1
// A[4] = 4
// A[5] = 5
// A[6] = -1
// A[7] = 2
//
// the function should return 17, because no double slice of array A has a
// sum of greater than 17.
//
// Write an efficient algorithm for the following assumptions:
//
// N is an integer within the range [3..100,000];
// each element of array A is an integer within the range [−10,000..10,000].
//
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <algorithm>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
// A variant of the classic maximum subarray problem. We should travel the
// array twice. For the first travel, we compute and record the maximum
// sub-array sum, which "ends" at each position. At the second reverse travel,
// we compute and record the maximum sub-array sum, which "starts" at each
// position. Finally, we combine two sub-arrays into one double slice,
// and find out the maximum sum.
//
// The maximum subarray problem was proposed as a simplified model for
// maximum likelihood estimation of patterns in digitized images.
// Maximum subarray algorithms are used for data analysis in many fields,
// such as genomic sequence analysis, computer vision, and data mining.
// https://en.wikipedia.org/wiki/Maximum_subarray_problem
// http://cs.slu.edu/~goldwamh/courses/slu/csci314/2012_Fall/lectures/maxsubarray/
// https://web.archive.org/web/20120108213649/http://www.cs.bell-labs.com/cm/cs/pearls/s08.pdf
int max_double_slice_sum(const vector<int> &A)
{
    size_t i = 0;
    int max_here = 0;
    vector<int> max_ending_here(A.size());
    vector<int> max_beginning_here(A.size());

    // Get the sum of maximum subarray, which ends this position
    // In the definition of double slice, there is one gap cell between two segments.
    for(i = 1; i < A.size() - 2; ++i)
    {
        max_here = max(0, max_here + A[i]);
        max_ending_here[i] = max_here;
    }
    // Get the sum of maximum subarray, which begins at this position
    // In the definition of double slice, there is one gap cell between two segments.
    max_here = 0;
    for (i = A.size() - 2; i > 1; --i)
    {
        max_here = max(0, max_here + A[i]);
        max_beginning_here[i] = max_here;
    }
    // Connect two subarray for a double_slice. If the first subarray
    // ends at position i, the second subarray starts at position i+2.
    // Then we compare each double slice to get the one with the
    // greatest sum.
    max_here = 0; // maximum of double slice
    for(i = 0; i < A.size() - 2; ++i)
        max_here = max(max_here, max_ending_here[i] + max_beginning_here[i + 2]);
    return max_here;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Maximum Sum Double Slice", "[codility]")
{
    REQUIRE(max_double_slice_sum({3, 2, 6, -1, 4, 5, -1, 2}) == 17);
}