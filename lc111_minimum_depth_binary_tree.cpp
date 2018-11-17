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

#include <queue>
#include <utility>

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
int minDepth(TreeNode* root)
{
    if (root == nullptr)
        return 0;
    if (root->left == nullptr && root->right == nullptr)
        return 1;
    if (root->left == nullptr)
        return minDepth(root->right) + 1;
    if (root->right == nullptr)
        return minDepth(root->left) + 1;
    return min(minDepth(root->left), minDepth(root->right)) + 1;
}

int minDepth2(TreeNode* root)
{
    if (!root)
        return 0;
    queue<pair<TreeNode*, int>> q;
    int i = 0;
    q.push({root, 1});
    while (!q.empty())
    {
        auto cur = q.front(); q.pop();
        if (!cur.first->left && !cur.first->right)
            return cur.second;
        if (cur.first->left)
            q.push({cur.first->left, cur.second + 1});
        if (cur.first->right)
            q.push({cur.first->right, cur.second + 1});
    }
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Minimum Depth Binary Tree", "[leetcode]")
{
    TreeNode bt(3);
    bt.left = new TreeNode(9);
    bt.right = new TreeNode(20);
    bt.right->left = new TreeNode(15);
    bt.right->right = new TreeNode(7);
    REQUIRE(minDepth(&bt) == 2);
    REQUIRE(minDepth2(&bt) == 2);
}
