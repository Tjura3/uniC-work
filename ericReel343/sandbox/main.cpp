#include <iostream>
#include <string>
using namespace std;
class Node{
    public:
    string value;
    Node* left;
    Node* right;
    Node(string val): value(val), left(nullptr), right(nullptr) {}
};

void printHeightTree(Node* root, int height = 0){
    if(root == nullptr){
        return;
    }
    
    printHeightTree(root->left, height+1);
    cout << "[Node = " << root->value << "|Height = "<< height << "]" << endl;
    printHeightTree(root->right, height+1);
}

int main(){
    Node* root = new Node("A");
    Node* leftc = new Node("B");
    Node* rightc = new Node("C");
    Node* leftg = new Node("D");

    root -> left = leftc;
    root -> right = rightc;
    leftc -> left = leftg;

    printHeightTree(root);
    delete root;
    delete leftc;
    delete rightc;
    delete leftg;
    return 0;
}