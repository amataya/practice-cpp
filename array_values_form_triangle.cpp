//
// Given an array of integers, we need to find out whether it is possible to
// construct at least one non-degenerate triangle using array values as its sides.
// In other words, we need to find out 3 such array indices which can become
// sides of a non-degenerate triangle.
//
// For a non-degenerate triangle, its sides should follow these constraints,
// A + B > C    and
// B + C > A    and
// C + A > B
// where A, B and C are length of sides of the triangle.
// Input : [4, 1, 2]
// Output : No triangle is possible from given array values
//
// Input : [5, 4, 3, 1, 2]
// Output : Yes, sides of possible triangle are 2 3 4
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <algorithm>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
// A Simple Solution is to generate all triplets and for every triplet check if
// it forms a triangle or not by checking above three conditions.
// An Efficient Solution is use sorting. First, we sort the array then we loop
// once and we will check three consecutive elements of this array if any triplet
// satisfies arr[i] + arr[i+1] > arr[i+2], then we will output that triplet as
// our final result.
// Why checking only 3 consecutive elements will work instead of trying all
// possible triplets of sorted array?
// Let we are at index i and 3 line segments are
// arr[i], arr[i + 1] and arr[i + 2] with relation
// arr[i] < arr[i+1] < arr[i+2], If they can't form a non-degenerate triangle,
// the other line segments cannot form a non-degenerate triangle also because their
// sum will be even less. So we don't need to try all the combinations,
// we will try just 3 consecutive indices of array in sorted form.
// You also don't have to check all 3 conditions - if 1 is true, others will be true.
// The total complexity of below solution is O(n log n)
bool is_triangle_possible(vector<int> sides)
{
    if (sides.size() < 3)
        return false;

    sort(sides.begin(), sides.end());
    for (int i = 0; i < sides.size() - 2; ++i)
        if (sides[i] + sides[i+1] > sides[i+2])
            return true;
    return false;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Array values form triangle", "[jpmorgan]")
{
    REQUIRE(is_triangle_possible({5, 4, 3, 1, 2}));
    REQUIRE_FALSE(is_triangle_possible({4, 1, 2}));
}
