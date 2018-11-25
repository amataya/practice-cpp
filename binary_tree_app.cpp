// Executable to test binary tree algorithms
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "binary_tree.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////
//        20
//      /   \
//     8     22
//   /  \
//  4    12
//     /   \
//    10   14
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Binary Tree Essentials", "[classic]")
{
    list<int> deserialized{20, 8, 4, MARKER, MARKER,
                           12, 10, MARKER, MARKER,
                           14, MARKER, MARKER,
                           22, MARKER, MARKER};
    BTNode *root =  deserialize_binary_tree(deserialized);
    vector<int> traversal;
    inorder(root, traversal);
    REQUIRE(traversal == vector<int>{4, 8, 10, 12, 14, 20, 22});

    traversal.clear();
    preorder(root, traversal);
    REQUIRE(traversal == vector<int>{20, 8, 4, 12, 10, 14, 22});

    traversal.clear();
    postorder(root, traversal);
    REQUIRE(traversal == vector<int>{4, 10, 14, 12, 8, 22, 20});

    list<int> serialized{};
    serialize_binary_tree(root, serialized);
    REQUIRE(serialized == list<int>{20, 8, 4, MARKER, MARKER,
                                    12, 10, MARKER, MARKER,
                                    14, MARKER, MARKER,
                                    22, MARKER, MARKER});

    destroy_binary_tree(root);
    REQUIRE(root == nullptr);
}

////////////////////////////////////////////////////////////////////////////////
// The deepest left leaf node is the node with value 9.
//        1
//      /   \
//     2     3
//   /      /  \
//  4      5    6
//         \     \
//          7     8
//         /       \
//        9         10
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Deepest Left Leaf Node", "[bloomberg]")
{
    BTNode *root = new BTNode(1);
    root->left = new BTNode(2);
    root->left->left = new BTNode(4);
    root->right = new BTNode(3);
    root->right->left = new BTNode(5);
    root->right->left->right = new BTNode(7);
    root->right->left->right->left = new BTNode(9);
    root->right->right = new BTNode(6);
    root->right->right->right = new BTNode(8);
    root->right->right->right->right = new BTNode(10);

    BTNode *leaf = deepest_left_leaf_node(root);
    REQUIRE(leaf != nullptr);
    REQUIRE(leaf->key == 9);

    leaf = nullptr;
    destroy_binary_tree(root);
}