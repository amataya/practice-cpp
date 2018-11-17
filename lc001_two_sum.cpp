////////////////////////////////////////////////////////////////////////////////
// Given an array of integers, return indices of the two numbers such that they
// add up to a specific target. You may assume that each input would have exactly
// one solution, and you may not use the same element twice.
// Example:
// Given nums = [2, 7, 11, 15], target = 9,
// Because nums[0] + nums[1] = 2 + 7 = 9,
// return [0, 1].
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <unordered_map>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
vector<int> twoSum(vector<int> nums, int target)
{
    unordered_map<int, int> numIndexMap;
    int i = 0;
    for (; i < nums.size(); ++i)
        numIndexMap[nums[i]] = i;
    int other = 0;
    for(i = 0; i < nums.size(); ++i)
    {
        other = target - nums[i];
        if (numIndexMap.find(other) != numIndexMap.end() &&
            numIndexMap[other] != i)
            return {i, numIndexMap[other]};
    }
    return {};
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Two Sum", "[leetcode]")
{
    REQUIRE(twoSum({2, 7, 11, 15}, 9) == vector<int>{0,1});
}