// Given a binary tree, find the lowest common ancestor (LCA) of two given
// nodes in the tree.
//
// According to the definition of LCA on Wikipedia: “The lowest common ancestor
// is defined between two nodes p and q as the lowest node in T that has both
// p and q as descendants (where we allow a node to be a descendant of itself).”
//
// Given the following binary tree:  root = [3,5,1,6,2,0,8,null,null,7,4]
//         _______3______
//        /              \
//     ___5__          ___1__
//    /      \        /      \
//    6      _2       0       8
//          /  \
//          7   4
//
// Example 1:
// Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
// Output: 3
// Explanation: The LCA of nodes 5 and 1 is 3.
//
// Example 2:
// Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
// Output: 5
// Explanation: The LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself
//              according to the LCA definition.
//
// Note:
// - All of the nodes' values will be unique.
// - p and q are different and both values will exist in the binary tree.
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "binary_tree.h"

using namespace std;
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Lowest Common Ancestor of a Binary Tree", "[leetcode]")
{
    BTNode *root = new BTNode(3);
    root->left = new BTNode(5);
    root->left->left = new BTNode(6);
    root->left->right = new BTNode(2);
    root->left->right->left = new BTNode(7);
    root->left->right->right = new BTNode(4);
    root->right = new BTNode(1);
    root->right->left = new BTNode(0);
    root->right->right = new BTNode(8);

    BTNode *lca1 = lowest_common_ancestor(root, root->left, root->right);
    REQUIRE(lca1 != nullptr);
    REQUIRE(lca1->key == 3);

    BTNode *lca2 = lowest_common_ancestor(root, root->left, root->left->right->right);
    REQUIRE(lca2 != nullptr);
    REQUIRE(lca2->key == 5);

    destroy_binary_tree(root);
}