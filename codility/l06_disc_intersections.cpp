////////////////////////////////////////////////////////////////////////////////
// Codility - Beta 2010
////////////////////////////////////////////////////////////////////////////////
// We draw N discs in a 2D plane. The discs are numbered from 0 to N − 1.
// An array A of N non-negative integers, specifying the radiuses of the discs,
// is given. The J-th disc is drawn with its center at (J, 0) and radius A[J].
// We say that the J-th disc and K-th disc intersect if J ≠ K and the J-th and
// K-th discs have at least one common point (assuming that the discs
// contain their borders).
//
// Write a function:
//
// int solution(vector<int> &A);
//
// that, given an array A describing N discs as explained above, returns the
// number of (unordered) pairs of intersecting discs. The function should
// return −1 if the number of intersecting pairs exceeds 10,000,000.
//
// For example, given N = 6 and A as follows:
// A[0] = 1
// A[1] = 5
// A[2] = 2
// A[3] = 1
// A[4] = 4
// A[5] = 0
//
// There are 11 (unordered) pairs of discs that intersect, namely:
// discs 1 and 4 intersect, and both intersect with all the other discs;
// disc 2 also intersects with discs 0 and 3.
//
// Write an efficient algorithm for the following assumptions:
// - N is an integer within the range [0..100,000];
// - each element of array A is an integer within the range [0..2,147,483,647].
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <utility>
#include <algorithm>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
// We want to find the number of intersections of the intervals [i-A[i], i+A[i]].
//
// Maintain a sorted array (call it X) containing the i-A[i]
// (also have some extra space which has the value i+A[i] in there).
//
// Now walk the array X, starting at the leftmost interval (i.e smallest i-A[i]).
//
// For the current interval, do a binary search to see where the right end point
// of the interval (i.e. i+A[i]) will go (called the rank).
// Now you know that it intersects all the elements to the left.
//
// Increment a counter with the rank and subtract current position
// (assuming one indexed) as we don't want to double count intervals and
// self intersections.
// https://stackoverflow.com/a/4801275/10353406
////////////////////////////////////////////////////////////////////////////////
int disc_intersections(const vector<int> A)
{
    if (A.size() < 2)
        return 0;

    const int UPPER_LIMIT = 10000000;
    const size_t num_discs = A.size();
    using Bound = pair<long, long>;
    vector<Bound> bounds(num_discs);
    // The J-th disc is drawn with its center at (J, 0) and radius A[J]
    long center = 0, radius = 0;
    for (size_t j = 0; j < num_discs; ++j)
    {
        center = j;
        radius = A[j];
        bounds[j] = make_pair<long, long>(center - radius, center + radius);
    }

    auto comp1 = [](const Bound& a, const Bound& b) {
        return a.first < b.first;
    };

    sort(bounds.begin(), bounds.end(), comp1);

    auto comp2 = [](long right, const Bound& a) {
        return a.first > right;
    };

    long rank = 0, current_pos = 0 ;
    int num_intersections = 0;
    for(auto it = bounds.cbegin(); it != bounds.cend(); ++it)
    {
        rank = upper_bound(bounds.begin(), bounds.end(), it->second, comp2) - bounds.begin();
        current_pos = it - bounds.begin() + 1;
        num_intersections += rank - current_pos;
        if (num_intersections > UPPER_LIMIT)
            return -1;
    }
    return num_intersections;
}

////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Test Disc Intersections", "[codility]")
{
    REQUIRE(disc_intersections({1, 5, 2, 1, 4, 0})  == 11);
}

