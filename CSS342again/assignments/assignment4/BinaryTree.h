#ifndef BINARYTREE_H
#define BINARYTREE_H
//DO NOT MODIFY
struct Node {
    int value;
    Node* left;
    Node* right;

    Node(int v) : value(v), left(nullptr), right(nullptr) {}
};

class BinaryTree {
public:
    // Constructor: stores the provided root pointer.
    // The tree is built in main.cpp and passed into this constructor.
    BinaryTree(Node* root);

    // Destructor: must free all allocated nodes.
    ~BinaryTree();

    int height() const;
    int countNodes() const;
    int countLeaves() const;
    int sum() const;

    void preOrder() const;   // Root, Left, Right
    void inOrder() const;    // Left, Root, Right
    void postOrder() const;  // Left, Right, Root
    void preOrderIterative() const; //preorder traversal using a stack and iteration

    void mirror();
    //
    //void levelOrder();
private:
    Node* root_;

    // Private recursive helpers
    int height(Node* node) const;
    int countNodes(Node* node) const;
    int countLeaves(Node* node) const;
    int sum(Node* node) const;

    void preOrder(Node* node) const;
    void inOrder(Node* node) const;
    void postOrder(Node* node) const;

    void mirror(Node* node);
    void destroy(Node* node);
    //
    //void levelOrder(Node* root);
};

#endif