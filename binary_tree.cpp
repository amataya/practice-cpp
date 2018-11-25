////////////////////////////////////////////////////////////////////////////////

#include "binary_tree.h"

#include <queue>
#include <utility>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
BTNode* deserialize_binary_tree(list<int>& repr)
{
    if (repr.size() == 0)
        return nullptr;

    if (repr.front() == MARKER)
    {
        repr.pop_front();
        return nullptr;
    }
    BTNode *root = new BTNode(repr.front());
    repr.pop_front();
    root->left = deserialize_binary_tree(repr);
    root->right = deserialize_binary_tree(repr);
    return root;
}

// https://www.geeksforgeeks.org/construct-binary-tree-string-bracket-representation/

void serialize_binary_tree(BTNode *root, list<int>& repr)
{
    if (! root)
    {
        repr.push_back(MARKER);
        return;
    }
    repr.push_back(root->key);
    serialize_binary_tree(root->left, repr);
    serialize_binary_tree(root->right, repr);
}

void destroy_binary_tree(BTNode *&root)
{
    if (root == nullptr)
        return;
    destroy_binary_tree(root->left);
    destroy_binary_tree(root->right);
    delete root;
    root = nullptr;
}

void destroy_binary_tree_iterative(BTNode *&root)
{
    if (! root)
        return;
    list<BTNode*> queue;
    queue.push_back(root);
    BTNode *n = nullptr;
    while (!queue.empty())
    {
        n = queue.front();
        queue.pop_front();
        if (n->left)
            queue.push_back(n->left);
        if (n->right)
            queue.push_back(n->right);
        delete n; // Important: Delete node only after enqueueing its children
    }
    root = nullptr;
}

////////////////////////////////////////////////////////////////////////////////

void preorder(BTNode *root, vector<int>& traversal)
{
    if (root)
    {
        traversal.push_back(root->key);
        preorder(root->left, traversal);
        preorder(root->right, traversal);
    }
}

void postorder(BTNode *root, vector<int>& traversal)
{
    if (root)
    {
        postorder(root->left, traversal);
        postorder(root->right, traversal);
        traversal.push_back(root->key);
    }
}

void inorder(BTNode *root, vector<int>& traversal)
{
    if (root)
    {
        inorder(root->left, traversal);
        traversal.push_back(root->key);
        inorder(root->right, traversal);
    }
}
////////////////////////////////////////////////////////////////////////////////
// Given a binary tree, find its maximum depth.
// The maximum depth is the number of nodes along the longest path from the root
// node down to the farthest leaf node.
// Note: A leaf is a node with no children.
////////////////////////////////////////////////////////////////////////////////
int maxDepth(BTNode *root)
{
    if (!root)
        return 0;

    const int dl = maxDepth(root->left) + 1;
    const int dr = maxDepth(root->right) + 1;
    return max(dl, dr);
}

int minDepth(BTNode* root)
{
    if (! root)
        return 0;
    if (! root->left && ! root->right)
        return 1;
    if (!root->left)
        return minDepth(root->right) + 1;
    if (! root->right)
        return minDepth(root->left) + 1;
    return min(minDepth(root->left), minDepth(root->right)) + 1;
}

int min_depth_iterative(BTNode *root)
{
    if (!root)
        return 0;
    queue<pair<BTNode*, int>> q;
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
// Given a Binary Tree, find the deepest leaf node that is left child of its
// parent. For example, consider the following tree.
////////////////////////////////////////////////////////////////////////////////
void deepest_leaf_node_util(BTNode* node,
                            int level, int& maxLevel,
                            bool isLeft, BTNode **result)
{
    if (!node)
        return;

    // Update result if this node is left node and its level is more than max
    if (isLeft && !node->left && !node->right && level > maxLevel)
    {
        *result = node;
        maxLevel = level;
    }

    deepest_leaf_node_util(node->left, level + 1, maxLevel, true, result);
    deepest_leaf_node_util(node->right, level + 1, maxLevel, false, result);
}

BTNode* deepest_left_leaf_node(BTNode* root)
{
    BTNode *result = nullptr;
    int maxLevel = 0;
    deepest_leaf_node_util(root, 0, maxLevel, false, &result);
    return result;
}

// https://www.geeksforgeeks.org/deepest-left-leaf-node-in-a-binary-tree/