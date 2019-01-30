////////////////////////////////////////////////////////////////////////////////
// Given an integer array nums, find the contiguous subarray (containing at
// least one number) which has the largest sum and return its sum.
//
// Example:
// Input: [-2,1,-3,4,-1,2,1,-5,4],
// Output: 6
// Explanation: [4,-1,2,1] has the largest sum = 6.
//
// Follow up: If you have figured out the O(n) solution, try coding another
// solution using the divide and conquer approach, which is more subtle.
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
// Kadane’s Algorithm:
// Initialize:
//     max_so_far = 0
//     max_ending_here = 0
//
// Loop for each element of the array
//   (a) max_ending_here = max_ending_here + a[i]
//   (b) if(max_ending_here < 0)
//             max_ending_here = 0
//   (c) if(max_so_far < max_ending_here)
//             max_so_far = max_ending_here
// return max_so_far
////////////////////////////////////////////////////////////////////////////////
int maxSubArray(const vector<int>& nums)
{
    if (nums.empty())
        return 0;

    int curMax = nums[0], allTimeMax = nums[0];
    for (int i = 1; i < nums.size(); ++i)
    {
        curMax = max(nums[i], curMax + nums[i]);
        allTimeMax = max(curMax, allTimeMax);
    }
    return allTimeMax;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Maximum Subarray Sum", "[leetcode]")
{
    REQUIRE(maxSubArray({-2,1,-3,4,-1,2,1,-5,4}) == 6);
}