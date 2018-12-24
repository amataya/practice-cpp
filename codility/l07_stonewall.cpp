// Cover "Manhattan skyline" using the minimum number of rectangles.
//
// You are going to build a stone wall. The wall should be straight and N meters
// long, and its thickness should be constant; however, it should have different
// heights in different places. The height of the wall is specified by an array
// H of N positive integers. H[I] is the height of the wall from I to I+1 meters
// to the right of its left end. In particular, H[0] is the height of the wall's
// left end and H[N−1] is the height of the wall's right end.
//
// The wall should be built of cuboid stone blocks (that is, all sides of such
// blocks are rectangular). Your task is to compute the minimum number of blocks
// needed to build the wall.
//
// Write a function:
//
// int solution(vector<int> &H);
//
// that, given an array H of N positive integers specifying the height of the
// wall, returns the minimum number of blocks needed to build it.
//
// For example, given array H containing N = 9 integers:
// H[0] = 8    H[1] = 8    H[2] = 5
// H[3] = 7    H[4] = 9    H[5] = 8
// H[6] = 7    H[7] = 4    H[8] = 8
//
// the function should return 7. The figure shows one possible arrangement of
// seven blocks.
//
// Write an efficient algorithm for the following assumptions:
//
// N is an integer within the range [1..100,000];
// each element of array H is an integer within the range [1..1,000,000,000].
//
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <stack>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
// This only makes sense when you draw on a piece of paper.
// Use a stack to track levels as long as the height increases. When the height
// decreases, take levels out, but increment a counter for the building blocks.
// Keep taking levels out until the height of the level on the stack is lower
// than the current values. In the end, when all the values are finished,
// add one construction block for each level in the stack.
// If the height of current block is:
// - lesser than the previous ones, the previous ones have to end before current
// - greater than the previous one, a new block is needed for current position
// - equal then they should be combined into one block
// Finally add remaining blocks.
int min_blocks(const vector<int> H)
{
    int count = 0;
    stack<int> heights;
    for (const auto& height: H)
    {
        for(; !heights.empty() && height < heights.top(); ++count)
            heights.pop();

        if (heights.empty() || height > heights.top())
            heights.push(height);
    }
    count += heights.size();
    return count;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Stonewall", "[codility]")
{
    REQUIRE(min_blocks({8, 8, 5, 7, 9, 8, 7, 4, 8}) == 7);
}