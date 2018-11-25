// Given a binary search tree (BST), find the lowest common ancestor (LCA) of
// two given nodes in the BST.
//
// According to the definition of LCA on Wikipedia: “The lowest common ancestor
// is defined between two nodes p and q as the lowest node in T that has both
// p and q as descendants (where we allow a node to be a descendant of itself).”
//
// Given binary search tree:  root = [6,2,8,0,4,7,9,null,null,3,5]
//
//         _______6______
//        /              \
//     ___2__          ___8__
//    /      \        /      \
//    0      _4       7       9
//          /  \
//          3   5
//
// Example 1:
// Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
// Output: 6
// Explanation: The LCA of nodes 2 and 8 is 6.
//
// Example 2:
// Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
// Output: 2
// Explanation: The LCA of nodes 2 and 4 is 2, since a node can be a descendant
// of itself according to the LCA definition.
//
// Note:
//     All of the nodes' values will be unique.
//     p and q are different and both values will exist in the BST.
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "binary_tree.h"

using namespace std;
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Lowest Common Ancestor of a Binary Search Tree", "[leetcode]")
{
    BTNode *root = new BTNode(6);
    root->left = new BTNode(2);
    root->left->left = new BTNode(0);
    root->left->right = new BTNode(4);
    root->left->right->left = new BTNode(3);
    root->left->right->right = new BTNode(5);
    root->right = new BTNode(8);
    root->right->left = new BTNode(7);
    root->right->right = new BTNode(9);

    BTNode *lca1 = lowest_common_ancestor_bst(root, root->left, root->right);
    REQUIRE(lca1 != nullptr);
    REQUIRE(lca1->key == 6);

    BTNode *lca2 = lowest_common_ancestor_bst(root, root->left, root->left->right);
    REQUIRE(lca2 != nullptr);
    REQUIRE(lca2->key == 2);

    BTNode *lca3 = lowest_common_ancestor_bst_iterative(root, root->left, root->right);
    REQUIRE(lca3 != nullptr);
    REQUIRE(lca3->key == 6);

    BTNode *lca4 = lowest_common_ancestor_bst_iterative(root, root->left, root->left->right);
    REQUIRE(lca4 != nullptr);
    REQUIRE(lca4->key == 2);

    destroy_binary_tree(root);
}