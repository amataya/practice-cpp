////////////////////////////////////////////////////////////////////////////////
// Given n non-negative integers a1, a2, ..., an , where each represents a
// point at coordinate (i, ai). n vertical lines are drawn such that the
// two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which
// together with x-axis forms a container, such that the container contains
// the most water.
//
// Note: You may not slant the container and n is at least 2
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
// Start by evaluating the widest container, using the first and the last line.
// All other possible containers are less wide, so to hold more water, they need
// to be higher. Thus, after evaluating that widest container, skip lines at both
// ends that don't support a higher height. Then evaluate that new container we
// arrived at. Repeat until there are no more possible containers left.
int maxArea(vector<int> height)
{
    int water = 0;
    int i = 0, j = height.size() - 1, h = 0;
    while (i < j)
    {
        h = min(height[i], height[j]);
        water = max(water, (j - i) * h);
        while (height[i] <= h && i < j) i++;
        while (height[j] <= h && i < j) j--;
    }
    return water;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Container with most water", "[leetcode]")
{
    REQUIRE(maxArea({1,8,6,2,5,4,8,3,7}) == 49);
}