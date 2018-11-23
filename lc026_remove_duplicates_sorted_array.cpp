// Given a sorted array nums, remove the duplicates in-place such that each
// element appear only once and return the new length.
// Do not allocate extra space for another array, you must do this by modifying
// the input array in-place with O(1) extra memory.
//
// Example 1:
// Given nums = [1,1,2],
// Your function should return length = 2, with the first two elements of nums
// being 1 and 2 respectively.
//
// Example 2:
// Given nums = [0,0,1,1,1,2,2,3,3,4],
// Your function should return length = 5, with the first five elements of nums
// being modified to 0, 1, 2, 3, and 4 respectively.
//
// It doesn't matter what values are set beyond the returned length.
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <algorithm>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
int removeDuplicates(vector<int>& nums)
{
    // This optimization speeds up execution
    if (nums.size() < 2)
        return nums.size();

    int count = 0;
    for(int i = 1; i < nums.size(); ++i)
        if (nums[i] == nums[i - 1])
            ++count;
        else
            nums[i - count] = nums[i];
    return nums.size() - count;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Remove Duplicates from Sorted Array", "[leetcode]")
{
    vector<int> nums1 = {1, 1, 2};
    REQUIRE(removeDuplicates(nums1) == 2);

    vector<int> nums2 = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
    REQUIRE(removeDuplicates(nums2) == 5);

    vector<int> nums3 = {1, 1};
    REQUIRE(removeDuplicates(nums3) == 1);

    vector<int> nums4 = {2};
    REQUIRE(removeDuplicates(nums4) == 1);

    vector<int> nums5 = {};
    REQUIRE(removeDuplicates(nums5) == 0);
}