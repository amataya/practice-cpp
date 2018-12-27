//  Compute number of distinct absolute values of sorted array elements.
//
// A non-empty array A consisting of N numbers is given. The array is sorted
// in non-decreasing order. The absolute distinct count of this array is the
// number of distinct absolute values among the elements of the array.
//
// For example, consider array A such that:
// A[0] = -5
// A[1] = -3
// A[2] = -1
// A[3] =  0
// A[4] =  3
// A[5] =  6
//
// The absolute distinct count of this array is 5, because there are 5 distinct
// absolute values among the elements of this array, namely 0, 1, 3, 5 and 6.
//
// Write a function:
//
// int solution(vector<int> &A);
//
// that, given a non-empty array A consisting of N numbers, returns absolute
// distinct count of array A.
//
// For example, given array A such that:
// A[0] = -5
// A[1] = -3
// A[2] = -1
// A[3] =  0
// A[4] =  3
// A[5] =  6
//
// the function should return 5, as explained above.
//
// Write an efficient algorithm for the following assumptions:
//
// N is an integer within the range [1..100,000];
// each element of array A is an integer within the range
// [−2,147,483,648 ... 2,147,483,647];
// array A is sorted in non-decreasing order.
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <climits>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
int num_distinct(const vector<int> &A)
{
    if (A.size() < 2) // N is minimum 1
        return 1;

    long max_value = A[A.size() - 1];
    if (max_value < 0) // If you have an array of all negatives
        max_value *= -1;
    if (A[0] < 0)
        max_value = max(long(A[0]) * -1, max_value);

    vector<bool> checker(max_value);
    int distinct = 0;
    for (long n : A)
    {
        if (n < 0)
            n = abs(n);
        if (!checker[n])
        {
            ++distinct;
            checker[n] = true;
        }
    }
    return distinct;
}
// Can you do it without using additional storage?
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Num Distinct Absolute", "[codility]")
{
    //REQUIRE(num_distinct({-5, -3, 1, 0, 3, 6}) == 5);
    REQUIRE(num_distinct({-2147483648, 0}) == 2);
}