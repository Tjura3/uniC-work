#include <iostream>
#include <queue>
#include <vector>
#include <cstdlib>
#include "BinaryTree.h"
//DO NOT MODIFY
using namespace std;

// Build tree in level-order from vector
Node* buildLevelOrder(const vector<int>& values) {
    if (values.empty()) return nullptr;

    Node* root = new Node(values[0]);
    queue<Node*> q;
    q.push(root);

    size_t i = 1;
    while (i < values.size()) {
        Node* parent = q.front();
        q.pop();

        parent->left = new Node(values[i++]);
        q.push(parent->left);

        if (i < values.size()) {
            parent->right = new Node(values[i++]);
            q.push(parent->right);
        }
    }

    return root;
}

void printAll(const BinaryTree& tree) {
    cout << "Height: " << tree.height() << endl;
    cout << "CountNodes: " << tree.countNodes() << endl;
    cout << "CountLeaves: " << tree.countLeaves() << endl;
    cout << "Sum: " << tree.sum() << endl;

    cout << "PreOrder: ";
    tree.preOrder();

    cout << "InOrder: ";
    tree.inOrder();

    cout << "PostOrder: ";
    tree.postOrder();

    cout << "PreOrderIterative: ";
    tree.preOrderIterative();
}

int main(int argc, char* argv[]) {

    // ---------------------------------------------------
    // Case 1: Tree built from command-line arguments
    // ---------------------------------------------------
    vector<int> values;
    for (int i = 1; i < argc; ++i) {
        values.push_back(atoi(argv[i]));
    }

    Node* root = buildLevelOrder(values);
    BinaryTree tree(root);

    cout << "=== Command Line Tree ===" << endl;
    printAll(tree);
    //tree.levelOrder();
    

    tree.mirror();
    cout << "=== After Mirror ===" << endl;
    printAll(tree);
    //tree.levelOrder();

    tree.mirror();
    cout << "=== After Mirror Twice ===" << endl;
    printAll(tree);

    cout << endl;

    // ---------------------------------------------------
    // Case 2: Empty tree
    // ---------------------------------------------------
    BinaryTree emptyTree(nullptr);
    cout << "=== Empty Tree ===" << endl;
    printAll(emptyTree);

    cout << endl;

    // ---------------------------------------------------
    // Case 3: Single node
    // ---------------------------------------------------
    Node* single = new Node(42);
    BinaryTree singleTree(single);

    cout << "=== Single Node Tree ===" << endl;
    printAll(singleTree);

    return 0;
}