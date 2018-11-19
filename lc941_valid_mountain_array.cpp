////////////////////////////////////////////////////////////////////////////////
// Given an array A of integers, return true if and only if it is a valid
// mountain array.
// Recall that A is a mountain array if and only if:
//     A.length >= 3
//     There exists some i with 0 < i < A.length - 1 such that:
//         A[0] < A[1] < ... A[i-1] < A[i]
//         A[i] > A[i+1] > ... > A[B.length - 1]
//
// Example 1:
// Input: [2,1]
// Output: false
//
// Example 2:
// Input: [3,5,5]
// Output: false
//
// Example 3:
// Input: [0,3,2,1]
// Output: true
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
bool validMountainArray(vector<int> A)
{
    if (A.size() < 3)
        return false;

    int i = 1;
    for (; i < A.size(); ++i)
        if (A[i] < A[i-1])
            break;
    if (i == 1 || i == A.size())
        return false;
    for (int j = A.size() - 1; j > i; --j)
        if (A[j] >= A[j - 1])
            return false;
    return true;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Valid Mountain Array", "[leetcode]")
{
    REQUIRE_FALSE(validMountainArray({2,1}));
    REQUIRE_FALSE(validMountainArray({3,5,5}));
    REQUIRE(validMountainArray({0,3,2,1}));
    REQUIRE(validMountainArray({1,3,2}));
    REQUIRE_FALSE(validMountainArray({9,8,7,6,5,4,3,2,1,0}));
    REQUIRE(validMountainArray({1,2,3,5,7,9,10,12,18,20,21,22,23,24,25,28,29,23}));
}