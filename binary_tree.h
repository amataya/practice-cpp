#ifndef PRACTICE_BINARY_TREE_H
#define PRACTICE_BINARY_TREE_H

#include <list>
#include <vector>
#include <climits>
////////////////////////////////////////////////////////////////////////////////
struct BTNode
{
    BTNode *left = nullptr;
    BTNode *right = nullptr;
    int key;
    BTNode(int k) : key(k) {}
};

#define MARKER INT_MIN
////////////////////////////////////////////////////////////////////////////////

void destroy_binary_tree(BTNode*& root);

void serialize_binary_tree(BTNode *root, std::list<int>& repr);

BTNode* deserialize_binary_tree(std::list<int>& repr);

////////////////////////////////////////////////////////////////////////////////

void preorder(BTNode *root, std::vector<int>& traversal);

void inorder(BTNode *root, std::vector<int>& traversal);

void postorder(BTNode *root, std::vector<int>& traversal);

////////////////////////////////////////////////////////////////////////////////

int maxDepth(BTNode* root);

int minDepth(BTNode* root);

int min_depth_iterative(BTNode* root);

////////////////////////////////////////////////////////////////////////////////

BTNode* deepest_left_leaf_node(BTNode* root);

////////////////////////////////////////////////////////////////////////////////



#endif //PRACTICE_BINARY_TREE_H
