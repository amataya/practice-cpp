////////////////////////////////////////////////////////////////////////////////
// Given an array nums of n integers, are there elements a, b, c in
// nums such that a + b + c = 0? Find all unique triplets in the array
// which gives the sum of zero.
// Note: The solution set must not contain duplicate triplets.
// Example:
// Given array nums = [-1, 0, 1, 2, -1, -4],
// A solution set is:
// [
//   [-1, 0, 1],
//   [-1, -1, 2]
// ]
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
vector<vector<int>> threeSum(vector<int> nums)
{
    vector<vector<int>> result;

    if (nums.size() < 3)
        return result;

    sort(nums.begin(), nums.end());
    int i = 0, j = 0, k = 0;
    int a = 0, b = 0, c = 0;
    for (; i < nums.size() - 2; ++i)
    {
        a = nums[i];
        if (i > 0 && a == nums[i - 1])
            continue;
        for (j = i + 1, k = nums.size() - 1; j < k;)
        {
            b = nums[j];
            c = nums[k];
            if (a + b + c == 0)
            {
                result.push_back({a, b, c});
                // clever trick - we were already updating indexes before
                // entering these loops; now that happens within the loops
                while (j < k && b == nums[++j]);
                while (j < k && c == nums[--k]);
            }
            else if (a + b + c > 0) // too much positive value
                k--;
            else                    // too much negative value
                j++;
        }
    }
    return result;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("3Sum", "[leetcode]")
{
    REQUIRE(threeSum({-1, 0, 1, 2, -1, -4}) ==
                    vector<vector<int>>{{-1, -1, 2}, {-1, 0, 1}});
}