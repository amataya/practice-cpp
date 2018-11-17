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

using namespace std;
////////////////////////////////////////////////////////////////////////////////
struct TreeNode
{
    int val;
    TreeNode *left = nullptr;
    TreeNode *right = nullptr;
    TreeNode(int x) : val(x) {}
};
////////////////////////////////////////////////////////////////////////////////
int maxDepth(TreeNode* root)
{
    if (!root)
        return 0;
    return max(maxDepth(root->left) + 1, maxDepth(root->right) + 1);
}

////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Maximum Depth Binary Tree", "[leetcode]")
{
    TreeNode bt(3);
    bt.left = new TreeNode(9);
    bt.right = new TreeNode(20);
    bt.right->left = new TreeNode(15);
    bt.right->right = new TreeNode(7);
    REQUIRE(maxDepth(&bt) == 3);
}