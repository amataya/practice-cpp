////////////////////////////////////////////////////////////////////////////////
// Given a 2d grid map of '1's (land) and '0's (water), count the number of
// islands. An island is surrounded by water and is formed by connecting adjacent
// lands horizontally or vertically. You may assume all four edges of the grid
// are all surrounded by water.
//
// Example 1:
// Input:
// 11110
// 11010
// 11000
// 00000
// Output: 1
//
// Example 2:
// Input:
// 11000
// 11000
// 00100
// 00011
// Output: 3
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <string>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
void dfs(vector<vector<char>>& grid, int i, int j)
{
    int r = grid.size();
    int c = grid[0].size();
    // Base case to stop recursion
    if (i < 0 || j < 0 || i >= r || j >= c || grid[i][j] == '0')
        return;
    // Visit all adjancent cells around the current cell
    // and mark them as '0'. This simplifies traversal logic later
    grid[i][j] = '0';
    dfs(grid, i+1, j);
    dfs(grid, i-1, j);
    dfs(grid, i, j+1);
    dfs(grid, i, j-1);
}

int numIslands(vector<vector<char>> grid)
{
    int r = grid.size();
    if (r == 0)
        return 0;
    int c = grid[0].size();
    if (c == 0)
        return 0;

    int count = 0, i = 0, j = 0;
    for (; i < r; ++i)
    {
        for(j = 0; j < c; ++j)
        {
            if (grid[i][j] == '1')
            {
                dfs(grid, i, j);
                ++count;
            }
        }
    }
    return count;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Number of Islands", "[leetcode]")
{
    REQUIRE(numIslands({{'1', '1', '1', '1', '0'}, {'1', '1', '0', '1', '0'},
                        {'1', '1', '0', '0', '0'}, {'0', '0', '0', '0', '0'}}) == 1);
    REQUIRE(numIslands({{'1', '1', '0', '0', '0'}, {'1', '1', '0', '0', '0'},
                        {'0', '0', '1', '0', '0'}, {'0', '0', '0', '1', '1'}}) == 3);
}
