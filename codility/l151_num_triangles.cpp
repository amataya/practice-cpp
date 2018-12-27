// Same as
// Count the number of triangles that can be built from a given set of edges.
//
// An array A consisting of N integers is given. A triplet (P, Q, R) is
// triangular if it is possible to build a triangle with sides of lengths
// A[P], A[Q] and A[R]. In other words, triplet (P, Q, R) is triangular
// if 0 ≤ P < Q < R < N and:
//
// A[P] + A[Q] > A[R],
// A[Q] + A[R] > A[P],
// A[R] + A[P] > A[Q].
//
// For example, consider array A such that:
// A[0] = 10    A[1] = 2    A[2] = 5
// A[3] = 1     A[4] = 8    A[5] = 12
//
// There are four triangular triplets that can be constructed from elements of
// this array, namely (0, 2, 4), (0, 2, 5), (0, 4, 5), and (2, 4, 5).
//
// Write a function:
//
// int solution(vector<int> &A);
//
// that, given an array A consisting of N integers, returns the number of
// triangular triplets in this array.
//
// For example, given array A such that:
// A[0] = 10    A[1] = 2    A[2] = 5
// A[3] = 1     A[4] = 8    A[5] = 12
//
// the function should return 4, as explained above.
//
// Write an efficient algorithm for the following assumptions:
//
// N is an integer within the range [0..1,000];
// each element of array A is an integer within the range [1..1,000,000,000].
//
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <algorithm>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
// p is the first segment, q is the the second segment for the triangles.
// All the elements between q (exclusive) and r (exclusive) could be the
// third item for the triangles.
// Apply the caterpillar method. We know that in a sorted array every position
// Line 67 is basically answering the question: Given P and R, what values V
// larger than P and smaller than R will fit the equation P+Q > R. The answer is
// rather simple. If V=Q fits the criteria, all following values V are larger
// and will therefore fit the criteria. Hence the sorting and subtraction.
int num_triangles(vector<int> A)
{
    if (A.empty())
        return 0;

    sort(A.begin(), A.end());
    int p, q, r, count = 0;
    for(p = 0; p < A.size() - 2; ++p)
    {
        q = p + 1;
        r = p + 2;
        while (r < A.size())
        {
            if (A[p] + A[q] > A[r])
            {
                count += r - q;
                ++r;
            }
            else if (q < r - 1)
                ++q;
            else
            {
                ++q;
                ++r;
            }
        }
    }
    return count;
}

////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Num Triangles", "[codility]")
{
    REQUIRE(num_triangles({10, 1, 5, 1, 8, 12}) == 4);
    REQUIRE(num_triangles({5, 3, 3}) == 0);
}