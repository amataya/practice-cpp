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

void destroy_binary_tree(BTNode *root);

void serialize_binary_tree(BTNode *root, std::list<int>& repr);

BTNode* deserialize_binary_tree(std::list<int>& repr);

////////////////////////////////////////////////////////////////////////////////

void preorder(BTNode *root, std::vector<int>& traversal);

void inorder(BTNode *root, std::vector<int>& traversal);

void postorder(BTNode *root, std::vector<int>& traversal);

std::vector<int> inorder_iterative(BTNode *node);

////////////////////////////////////////////////////////////////////////////////

int maxDepth(BTNode* root);

int minDepth(BTNode* root);

int min_depth_iterative(BTNode* root);

////////////////////////////////////////////////////////////////////////////////

bool is_valid_bst(BTNode *root);

bool is_valid_bst_iterative(BTNode *node);

BTNode* deepest_left_leaf_node(BTNode* root);

BTNode* lowest_common_ancestor(BTNode *root, BTNode *p, BTNode *q);

BTNode* lowest_common_ancestor_bst(BTNode *root, BTNode *p, BTNode *q);

BTNode* lowest_common_ancestor_bst_iterative(BTNode *root, BTNode *p, BTNode *q);

int kth_smallest_element(BTNode *root, int k);

////////////////////////////////////////////////////////////////////////////////



#endif //PRACTICE_BINARY_TREE_H
