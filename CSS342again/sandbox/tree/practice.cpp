#include <iostream>
using namespace std;
//I wonder if the reason why you would want to put something on the heap is so it doesn't fall outside of the scope.
template <typename T>
struct Node{
    T value;
    Node* left;
    Node* right;
    Node(T val) : value(val), left(nullptr), right(nullptr) {}
    // ~Node(){
    //     delete left;
    //     delete right;
    // }
};

struct Treenode
{
    int value;
    Treenode* left;
    Treenode* right;
    Treenode(int val){
        value = val;
        left = nullptr;
        right = nullptr;
    }
};

void printtree(const Treenode* head){
    if(head == nullptr) return;
    printtree(head->left);
    printtree(head->right);
    cout << " " << head->value << " ";
}
void deletetree(Treenode* root){
    if (root == nullptr) return;
    deletetree(root->left);
    deletetree(root->right);
    root->left = nullptr;
    root->right = nullptr;
    delete root;
}
//this is broken so far.
int count(Treenode* root){
    if(root == nullptr) return 0;
    return 1 + count(root->left) + count(root->right);
}
int main(){
    Treenode* root = new Treenode(5);
    
    root->left = new Treenode(3);
    root->left->left = new Treenode(1);
    root->left->right = new Treenode(4);
    root->right = new Treenode(7);
    root->right->right = new Treenode(10);
    root->right->left = new Treenode(6);
    
    printtree(root);
    cout << endl;
    deletetree(root);
    cout << "here" << endl;
    cout << count(root) << endl;

    
    
    return 0;
}