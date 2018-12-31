////////////////////////////////////////////////////////////////////////////////
// There are two sorted arrays nums1 and nums2 of size m and n respectively.
// Find the median of the two sorted arrays. The overall run time complexity
// should be O(log (m+n)).
// You may assume nums1 and nums2 cannot be both empty.
// Example 1:
// nums1 = [1, 3]
// nums2 = [2]
// The median is 2.0
//
// Example 2:
// nums1 = [1, 2]
// nums2 = [3, 4]
// The median is (2 + 3)/2 = 2.5
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
double findMedianUtil(vector<int>& A, vector<int>& B, int k,
                      int aStart, int aEnd, int bStart, int bEnd)
{
    int aLen = aEnd - aStart + 1;
    int bLen = bEnd - bStart + 1;

    // Handle special cases
    if (aLen == 0)
        return B[bStart + k];
    if (bLen == 0)
        return A[aStart + k];
    if (k == 0)
        return A[aStart] < B[bStart] ? A[aStart] : B[bStart];

    int aMid = aLen * k / (aLen + bLen); // a's middle count
    int bMid = k - aMid - 1; // b's middle count

    // make aMid and bMid to be array index
    aMid = aMid + aStart;
    bMid = bMid + bStart;

    if (A[aMid] > B[bMid])
    {
        k = k - (bMid - bStart + 1);
        aEnd = aMid;
        bStart = bMid + 1;
    }
    else
    {
        k = k - (aMid - aStart + 1);
        bEnd = bMid;
        aStart = aMid + 1;
    }

    return findMedianUtil(A, B, k, aStart, aEnd, bStart, bEnd);
}

double findMedianSortedArrays(vector<int> nums1, vector<int> nums2)
{
    int m = nums1.size();
    int n = nums2.size();
    int t = (m + n) / 2;
    if ((m + n) % 2 != 0) // odd
        return findMedianUtil(nums1,  nums2, t, 0, m - 1, 0, n - 1);
    else // even
    {
        return (findMedianUtil(nums1, nums2, t,     0, m - 1, 0, n - 1) +
                findMedianUtil(nums1, nums2, t - 1, 0, m - 1, 0, n - 1)) * 0.5;
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Median of two sorted arrays", "[leetcode]")
{
    REQUIRE(findMedianSortedArrays({1, 3}, {2}) == 2.0);
    REQUIRE(findMedianSortedArrays({1, 2}, {3, 4}) == 2.5);
}