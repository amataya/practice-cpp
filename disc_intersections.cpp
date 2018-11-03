////////////////////////////////////////////////////////////////////////////////
// Codility - Beta 2010
////////////////////////////////////////////////////////////////////////////////
// Given an array `A` of `N` integers, we draw N discs in a 2D plane such that
// the I-th disc is centered on `(0,I)` and has a radius of `A[I]`. We say that
// the J-thdisc and K-th disc intersect if `J ≠ K` and J-th and K-th discs have
// at least one common point.
// Calculate the number of (unordered) pairs of intersecting discs.
// The function should return −1 if the number of intersecting pairs exceeds
// 10,000,000.
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <utility>
#include <tuple>
#include <algorithm>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
// NOTE: This solution did not passes all tests.
// https://www.martinkysel.com/codility-number-of-disc-intersections-2010-beta-solution/
int disc_intersections(vector<int> A)
{
    if (A.size() < 2)
        return 0;

    const bool BEGINS = true, ENDS = false;
    using Bound = pair<int, bool>;

    vector<Bound> disc_endpoints;
    for (int i = 0; i < A.size(); ++i)
    {
        const Bound start = {i - A[i], BEGINS};
        const Bound end = make_pair(i + A[i], ENDS);
        disc_endpoints.push_back(start);
        disc_endpoints.push_back(end);
    }

    sort(disc_endpoints.begin(), disc_endpoints.end(),
         [](const Bound& a, const Bound& b) { return a.first < b.first; });

    int intersections = 0, active_discs = 0;
    for (const auto [pt, status] : disc_endpoints)
    {
        if (status == BEGINS)
        {
            intersections += active_discs;
            ++active_discs;
        }
        else if (status == ENDS)
            --active_discs;
        if (intersections > 10e6)
            return -1;
    }
    return intersections;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Test Disc Intersections", "[classic]")
{
    REQUIRE(disc_intersections({1, 5, 2, 1, 4, 0})  == 11);
}