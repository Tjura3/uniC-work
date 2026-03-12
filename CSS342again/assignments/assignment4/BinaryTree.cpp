#include "BinaryTree.h"
#include <cmath>
#include <iostream>
#include <stack>
#include <queue>

using namespace std;
BinaryTree::BinaryTree(Node* root){
    root_ = root;
}
// Destructor: must free all allocated nodes.
BinaryTree::~BinaryTree(){
    destroy(root_);
}

int BinaryTree::height() const{
    return height(root_);
}
int BinaryTree::countNodes() const{
    return countNodes(root_);
}
int BinaryTree::countLeaves() const{
    return countLeaves(root_);
}
int BinaryTree::sum() const{
    return sum(root_);
}

void BinaryTree::preOrder() const{   // Root, Left, Right
    preOrder(root_);
    cout << endl;
}
void BinaryTree::inOrder() const{    // Left, Root, Right
    inOrder(root_);
    cout << endl;
}
void BinaryTree::postOrder() const{  // Left, Right, Root
    postOrder(root_);
    cout << endl;
}
void BinaryTree::preOrderIterative() const{ //preorder traversal using a stack and iteration
    if(root_ == nullptr) return;
    stack<Node*> nstack; 
    nstack.push(root_);
    while(!nstack.empty()){
        Node* curr = nstack.top();
        nstack.pop();
        cout << curr->value << " ";
        
        if(curr->right != nullptr){
            nstack.push(curr->right);
        }
        if(curr->left != nullptr){
            nstack.push(curr->left);
        }
    }
    cout << endl;
}

void BinaryTree::mirror(){
    mirror(root_);
}
/* //If you are wondering what this is, I pulled this online from geeks for geeks to aid in testing, it just visualised the tree
//also this creates a bunch of leaks and I was only using it temporarily so I'm just not gonna bother fixing it because it's not even in the h file that will be used so it will break anyways.
void BinaryTree::levelOrder(){
    levelOrder(root_);
    cout << endl;
}
void BinaryTree::levelOrder(Node* root) {
    queue<pair<Node*, int>> queue;
    queue.push({root, 0});

    int lastLevel = 0;
    int heighta = height();
    
    while (!queue.empty()) {
        auto top = queue.front();
        queue.pop();

        Node* node = top.first;
        int lvl = top.second;

        if (lvl > lastLevel) {
            cout << "\n";
            lastLevel = lvl;
        }

        // all levels are printed
        if (lvl > heighta) break;

        // printing null node
        cout << (node->value == -1 ? "N" : to_string(node->value)) << " ";

        // null node has no children
        if (node->value == -1) continue;

        if (node->left == nullptr) queue.push({new Node(-1), lvl + 1});
        else queue.push({node->left, lvl + 1});

        if (node->right == nullptr) queue.push({new Node(-1), lvl + 1});
        else queue.push({node->right, lvl + 1});
    }
}
*/


int BinaryTree::height(Node* node) const{
    //this is ok... right?
    if(node == nullptr) return 0;
    return 1 + max(height(node->left), height(node->right));
}
int BinaryTree::countNodes(Node* node) const{
    if(node == nullptr) return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}
int BinaryTree::countLeaves(Node* node) const{
    if(node == nullptr) return 1;
    return countLeaves(node->left) + countLeaves(node->right);
}
int BinaryTree::sum(Node* node) const{
    if(node == nullptr) return 0;
    return node->value + sum(node->left) + sum(node->right);
}

void BinaryTree::preOrder(Node* node) const{
    if(node == nullptr) return;
    cout << node->value << " ";
    preOrder(node->left);
    preOrder(node->right);
    
}
void BinaryTree::inOrder(Node* node) const{
    if(node == nullptr) return;
    inOrder(node->left);
    cout << node->value << " ";
    inOrder(node->right);
}
void BinaryTree::postOrder(Node* node) const{
    if(node == nullptr) return;
    postOrder(node->left);
    postOrder(node->right);
    cout << node->value << " ";
}

void BinaryTree::mirror(Node* node){
    if (node == nullptr) {
        return;
    }
    //left first, then right,
    mirror(node->left);
    mirror(node->right);

    //Standard library one should work, this just swaps two values.
    //this works in my brain since pointers are just a memory address stored in an address.
    swap(node->left, node->right);
}
void BinaryTree::destroy(Node* node){
    if(node == nullptr) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}


