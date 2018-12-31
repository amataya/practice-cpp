// Given a binary tree, determine if it is a valid binary search tree (BST).
//
// Assume a BST is defined as follows:
// - The left subtree of a node contains only nodes with keys less than the
// node's key.
// - The right subtree of a node contains only nodes with keys greater than the
// node's key.
// - Both the left and right subtrees must also be binary search trees.
//
// Example 1:
// Input:
//     2
//    / \
//   1   3
// Output: true
//
// Example 2:
//     5
//    / \
//   1   4
//      / \
//     3   6
// Output: false
// Explanation: The input is: [5,1,4,null,null,3,6]. The root node's value
//              is 5 but its right child's value is 4.
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "binary_tree.h"

using namespace std;
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Is Valid BST", "[leetcode]")
{
    BTNode *root1 = new BTNode(2);
    root1->left = new BTNode(1);
    root1->right = new BTNode(3);
    REQUIRE(is_valid_bst(root1));
    REQUIRE(is_valid_bst_iterative(root1));
    destroy_binary_tree(root1);

    BTNode *root2 = new BTNode(5);
    root2->left = new BTNode(1);
    root2->right = new BTNode(4);
    root2->right->left = new BTNode(3);
    root2->right->right = new BTNode(6);
    REQUIRE_FALSE(is_valid_bst(root2));
    REQUIRE_FALSE(is_valid_bst_iterative(root2));
    destroy_binary_tree(root2);
}