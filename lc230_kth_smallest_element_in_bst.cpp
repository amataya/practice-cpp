// Given a binary search tree, write a function kthSmallest to find the kth
// smallest element in it.
//
// Note: You may assume k is always valid, 1 ≤ k ≤ BST's total elements.
//
// Example 1:
// Input: root = [3,1,4,null,2], k = 1
//    3
//   / \
//  1   4
//   \
//    2
// Output: 1
//
// Example 2:
// Input: root = [5,3,6,2,4,null,null,1], k = 3
//        5
//       / \
//      3   6
//     / \
//    2   4
//   /
//  1
// Output: 3
//
// Follow up:
// What if the BST is modified (insert/delete operations) often and you need to
// find the kth smallest frequently? How would you optimize the
// kthSmallest routine?
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "binary_tree.h"

using namespace std;
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Kth Smallest Element in a BST", "[leetcode]")
{
    BTNode *root1 = new BTNode(3);
    root1->left = new BTNode(1);
    root1->right = new BTNode(4);
    root1->left->right = new BTNode(2);

    BTNode *root2 = new BTNode(5);
    root2->left = new BTNode(3);
    root2->right = new BTNode(6);
    root2->left->left = new BTNode(2);
    root2->left->left->left = new BTNode(1);
    root2->left->right = new BTNode(4);

    REQUIRE(kth_smallest_element(root1, 1) == 1);
    REQUIRE(kth_smallest_element(root2, 3) == 3);

    destroy_binary_tree(root1);
    destroy_binary_tree(root2);
}