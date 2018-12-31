////////////////////////////////////////////////////////////////////////////////
// Given n non-negative integers representing an elevation map where the width
// of each bar is 1, compute how much water it is able to trap after raining.
// Example:
// Input: [0,1,0,2,1,0,1,3,2,1,2,1]
// Output: 6
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
// We store the maximum heights upto a point using 2 iterations of O(n) each.
// We finally update result using the stored values in O(n).
int trap(vector<int> height)
{
    if (height.size() < 2)
        return 0;

    const int n = height.size();
    vector<int> left(n), right(n);
    int i;

    left[0] = height[0];
    for (i = 1; i < n; ++i)
        left[i] = max(left[i - 1], height[i]);

    right[n - 1] = height[n - 1];
    for (i = n - 2; i >= 0; --i)
        right[i] = max(right[i + 1], height[i]);

    int water = 0;
    for (i = 0; i < n; ++i)
        water += min(left[i], right[i]) - height[i];

    return water;
}

// Instead of calculating area by height*width, we can think it in a cumulative
// way. In other words, sum water amount of each bin(width=1).
// Search from left to right and maintain find the max height of left and right
// separately, which is like a one-side wall of partial container.
// Fix the higher one and flow water from the lower part. For example,
// if current height of left is lower, we fill water in the left bin.
// Until left meets right, we filled the whole container.
int trap2(vector<int> height)
{
    if (height.size() < 2)
        return 0;

    int l = 0, r = height.size() - 1, level = 0, water = 0, lower = 0;
    while (l < r)
    {
        lower = height[l] < height[r] ? l++ : r--;
        level = max(level, height[lower]);
        water += level - height[lower];
    }
    return water;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Trapping Rain Water", "[leetcode]")
{
    REQUIRE(trap({0,1,0,2,1,0,1,3,2,1,2,1}) == 6);
    REQUIRE(trap2({0,1,0,2,1,0,1,3,2,1,2,1}) == 6);
}