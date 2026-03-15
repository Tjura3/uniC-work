#ifndef BST_H
#define BST_H

#include <vector>

struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

class BST {
public:
    // Constructor
    // An empty BST must be represented by:
    // root_ == nullptr
    // Do NOT allocate any nodes inside the constructor.
    BST();

    // Destructor
    // Must free all dynamically allocated nodes.
    ~BST();

    // Note: Copy constructor and assignment operator
    // are omitted here for simplicity.
    // You do NOT need to implement copy control for this bonus project.

    bool insert(int key);

    // kth_smallest:
    // k is 1-indexed.
    // Hint: When implementing the recursive helper,
    // you may find it useful to pass k by reference
    // so its value can be updated across recursive calls.
    bool kth_smallest(int k, int& result) const;

    std::vector<int> level_order_print() const;

    bool lca(int a, int b, int& result) const;

    // is_balanced:
    // Return true if the tree is height-balanced:
    // for every node, |height(left) - height(right)| <= 1.
    bool is_balanced() const;

private:
    Node* root_;

    // Recursive helpers
    Node* insert(Node* node, int key, bool& inserted);

    void destroy(Node* node);

    bool kth_smallest(Node* node, int& k, int& result) const;

    bool lca(Node* node, int a, int b, int& result) const;

    // Helper for is_balanced:
    // Returns height if balanced; returns -1 if unbalanced.
    int balanced_height(Node* node) const;
};

#endif