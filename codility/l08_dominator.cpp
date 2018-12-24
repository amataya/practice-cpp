//  Find an index of an array such that its value occurs at more than half of
//  indices in the array.
//
// An array A consisting of N integers is given. The dominator of array A is
// the value that occurs in more than half of the elements of A.
//
// For example, consider array A such that
// A[0] = 3    A[1] = 4    A[2] =  3
// A[3] = 2    A[4] = 3    A[5] = -1
// A[6] = 3    A[7] = 3
//
// The dominator of A is 3 because it occurs in 5 out of 8 elements of A
// (namely in those with indices 0, 2, 4, 6 and 7) and 5 is more than
// a half of 8.
//
// Write a function
//
// int solution(vector<int> &A);
//
// that, given an array A consisting of N integers, returns index of any
// element of array A in which the dominator of A occurs. The function should
// return −1 if array A does not have a dominator.
//
// For example, given array A such that
// A[0] = 3    A[1] = 4    A[2] =  3
// A[3] = 2    A[4] = 3    A[5] = -1
// A[6] = 3    A[7] = 3
//
// the function may return 0, 2, 4, 6 or 7, as explained above.
//
// Write an efficient algorithm for the following assumptions:
//
// N is an integer within the range [0..100,000];
// each element of array A is an integer within the range
// [−2,147,483,648..2,147,483,647].
//
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <algorithm>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
// This is an implementation of Boyer-Moore Majority Voting Algorithm
int dominator(const vector<int> &A)
{
    int candidate = 0, cindex = -1, i = 0;;
    long times = 0;
    for (i = 0; i < A.size(); ++i)
    {
        if  (times == 0)
        {
            candidate = A[i];
            cindex = i;
            ++times;
        }
        else
            times += (A[i] == candidate) ? 1 : -1;
    }
    if (times > 0)
    {
        times = count(A.begin(), A.end(), candidate);
        if (times > A.size() / 2)
            return cindex;
    }
    return -1;
}

////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Dominator", "[codility]")
{
    REQUIRE(dominator({3, 4, 3, 2, 3, -1, 3, 3}) == 6);
}