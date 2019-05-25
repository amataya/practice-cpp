// Given a collection of intervals, merge all overlapping intervals.
//
// Example 1:
// Input: [[1,3],[2,6],[8,10],[15,18]]
// Output: [[1,6],[8,10],[15,18]]
// Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into [1,6].
//
// Example 2:
// Input: [[1,4],[4,5]]
// Output: [[1,5]]
// Explanation: Intervals [1,4] and [4,5] are considered overlapping.
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <algorithm>
#include <vector>
#include <stack>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
// A simple approach is to start from the first interval and compare it with all
// other intervals for overlapping, if it overlaps with any other interval, then
// remove the other interval from list and merge the other into the first
// interval. Repeat the same steps for remaining intervals after first.
// This approach cannot be implemented in better than O(n^2) time.
//
// An efficient approach is to first sort the intervals according to starting
// time
// 1. Sort the intervals based on increasing order of starting time
// 2. Push the first interval on to the stack
// 3. For each interval:
//    a.  If the current interval does not overlap with the stack top, push it
//    b.  If their is an overlap and ending of the current interval is more than
//        that of stack top, then update the stack top with the ending time of
//        current interval.
// 4. At the end, the stack contains the merged intervals.
vector<vector<int>> merge_intervals(vector<vector<int>> intervals)
{
    if (intervals.size() < 2)
        return intervals;

    static auto cmp =  [](const vector<int>& v1, const vector<int>& v2) {
        return (v1[0] < v2[0]);
    };

    sort(intervals.begin(), intervals.end(), cmp);

    vector<vector<int>> result;
    result.push_back(intervals[0]);
    for (int i = 1; i < intervals.size(); ++i)
    {
        if (result.back()[1] < intervals[i][0])
            result.push_back(move(intervals[i]));
        else
            result.back()[1] = max(result.back()[1], intervals[i][1]);

    }
    return result;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("LC0056-Merge-Intervals-1", "[leetcode]")
{
    auto result = merge_intervals({{1,3},{2,6},{8,10},{15,18}});
    REQUIRE(result == vector<vector<int>>{{1,6},{8,10},{15,18}});
}

TEST_CASE("LC0056-Merge-Intervals-2", "[leetcode]")
{
    auto result = merge_intervals({{1,4},{4,5}});
    REQUIRE(result == vector<vector<int>>{{1,5}});
}

TEST_CASE("LC0056-Merge-Intervals-3", "[leetcode]")
{
    auto result = merge_intervals({});
    REQUIRE(result.empty());
}
