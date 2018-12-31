// Given a binary tree, find its minimum depth. The minimum depth is the number
// of nodes along the shortest path from the root node down to the nearest
// leaf node.
// Note: A leaf is a node with no children.
//
// Example:
// Given binary tree [3,9,20,null,null,15,7],
//     3
//    / \
//   9  20
//     /  \
//    15   7
// return its minimum depth = 2.
////////////////////////////////////////////////////////////////////////////////

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "binary_tree.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Minimum Depth Binary Tree", "[leetcode]")
{
    // Serialized form is not according to the below logic. Find out why?
    // LEFT = (ROOT_INDEX * 2) + 1;
    // RIGHT = (ROOT_INDEX * 2) + 2;
    list<int> btree{3, 9, MARKER, MARKER, 20,
                    15, MARKER, MARKER, 7, MARKER, MARKER};
    BTNode *bt = deserialize_binary_tree(btree);
    REQUIRE(minDepth(bt) == 2);
    REQUIRE(min_depth_iterative(bt) == 2);
    destroy_binary_tree(bt);
}
