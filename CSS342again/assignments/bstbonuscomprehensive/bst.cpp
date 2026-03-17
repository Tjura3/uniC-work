#include "bst.h"
#include <vector>
#include <queue>
#include <cmath>
#include <iostream>
using namespace std;
BST::BST(){
    root_ = nullptr;
}
BST::~BST(){
    destroy(root_);
}
bool BST::insert(int key){
    bool inserted = false;
    //setting it this way, allows for root to set itself. (also follows the spec)
    root_ = insert(root_, key, inserted);
    return inserted;
}
bool BST::kth_smallest(int k, int& result) const{
    if(k <= 0) return false;
    return kth_smallest(root_, k, result);
}
std::vector<int> BST::level_order_print() const{
    vector<int> result;
    if(root_ == nullptr) return result;
    //queue time
    queue<Node*> q;
    q.push(root_);

    while(!q.empty()){
        Node* curr = q.front();
        result.push_back(curr->key);
        q.pop();
        //pointers allocated are true
        if(curr->left) q.push(curr->left);
        if(curr->right) q.push(curr->right);
    }
    return result;
}
bool BST::lca(int a, int b, int& result) const{
    //initial check to make sure they are in the tree.
    Node* tempa = root_;
    while(tempa != nullptr && tempa->key != a){
        if(a < tempa->key){
            tempa = tempa->left;
        }else{
            tempa = tempa->right;
        }
    }
    if(tempa == nullptr) return false;
    //basically the same but left side
    Node* tempb = root_;
    while(tempb != nullptr && tempb->key != b){
        if(b < tempb->key){
            tempb = tempb->left;
        }else{
            tempb = tempb->right;
        }
    }
    if(tempb == nullptr) return false;
    //at this point the two numbers are in the bst so run it
    return lca(root_, a, b, result);
}
bool BST::is_balanced() const{
    return balanced_height(root_) != -1;
}

/**
 * Private methods
 */

// Recursive helpers
Node* BST::insert(Node* node, int key, bool& inserted){
    if (node == nullptr) {
        inserted = true;
        return new Node(key);
    }
    if (key < node->key) {
        node->left = insert(node->left, key, inserted);
    } else if (key > node->key) {
        node->right = insert(node->right, key, inserted);
    } else {
        inserted = false;
    }
    return node;
}

void BST::destroy(Node* node){
    if (node == nullptr) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}
//in order, find kth smallest
//basically keep going left until you find the smallest node you can find, then return the result
//in order is used to check the lowest nodes on the left first.
bool BST::kth_smallest(Node* node, int& k, int& result) const{
    if(node == nullptr) return false;
    //left search
    if(kth_smallest(node->left, k, result)) return true;
    //middle check
    k--;
    if(k == 0){
        result = node->key;
        return true;
    }
    //if left hits null, it checks the smallest of the right, or right check.
    return kth_smallest(node->right, k, result);
}

bool BST::lca(Node* node, int a, int b, int& result) const{
    if(a < node->key && b < node->key){
        return lca(node->left, a, b, result);
    }else if(a > node->key && b > node->key){
        return lca(node->right, a, b, result);
    }else{
        result = node->key;
        return true;
    }

}

// Helper for is_balanced:
// Returns height if balanced; returns -1 if unbalanced.
int BST::balanced_height(Node* node) const{
    if(node == nullptr) return 0;
    int lh = balanced_height(node->left);
    if(lh == -1) return -1;

    int rh = balanced_height(node->right);
    if(rh == -1) return -1;

    if(abs(lh - rh) > 1) return -1;

    return 1 + max(lh, rh);
}