////////////////////////////////////////////////////////////////////////////////
// Given a binary tree, find its maximum depth.
// The maximum depth is the number of nodes along the longest path from the root
// node down to the farthest leaf node.
// Note: A leaf is a node with no children.
// Example: Given binary tree [3,9,20,null,null,15,7],
//     3
//    / \
//   9  20
//     /  \
//    15   7
// return its depth = 3.
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "binary_tree.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// Example: Given binary tree [3,9,20,null,null,15,7],
//     3
//    / \
//   9  20
//     /  \
//    15   7
// It's max depth = 3.
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Maximum Depth Binary Tree", "[leetcode]")
{
    // Serialized form is not according to the below logic. Find out why?
    // LEFT = (ROOT_INDEX * 2) + 1;
    // RIGHT = (ROOT_INDEX * 2) + 2;
    list<int> btree{3, 9, MARKER, MARKER, 20,
                    15, MARKER, MARKER, 7, MARKER, MARKER};
    BTNode *bt = deserialize_binary_tree(btree);
    REQUIRE(maxDepth(bt) == 3);
    destroy_binary_tree(bt);
}