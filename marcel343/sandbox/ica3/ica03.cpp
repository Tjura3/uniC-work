// CSS 343 · ICA 03 — Tree Recursion
// ---------------------------------------------------------------------------
// Implement each function marked TODO. Do NOT edit buildExample(), main(), or
// the provided helpers (insert / destroy / buildExpr). Figure out the
// recursion yourself — that's the point of the exercise.
//
// Build & run on the CSS Linux lab:
//     g++ -std=c++17 ica03.cpp -o ica03 && ./ica03
//
// Tip: hand-draw the tree that buildExample() builds, then check your program's
// numbers against your drawing.
// ---------------------------------------------------------------------------
#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int   key;
    Node* left;
    Node* right;
};

// ---- provided: BST insert (used only to build the test tree) --------------
void insert(Node*& root, int key) {
    if (root == nullptr)      root = new Node{key, nullptr, nullptr};
    else if (key < root->key) insert(root->left,  key);
    else if (key > root->key) insert(root->right, key);
    // equal key: ignored (no duplicates)
}

// ---- provided: the tree you will test against -----------------------------
Node* buildExample() {
    Node* root = nullptr;
    for (int k : {50, 30, 70, 20, 40, 60, 80, 10, 45}) insert(root, k);
    return root;
}

// ---- provided: free the whole tree ----------------------------------------
void destroy(Node* t) {
    if (!t) return;
    destroy(t->left);
    destroy(t->right);
    delete t;
}

// ===========================================================================
//  YOUR WORK — replace each stub.
// ===========================================================================

// TODO 1 — height of the tree rooted at t.
//   An empty tree has height -1; a single node has height 0.
int height(Node* t) {
    if(t == nullptr) return -1;
    //apparently if(t) treats pointers as booleans wether they point to something or not.
    return max(height(t->left) + 1, height(t->right) + 1); //if both heights return -1, the +1 turns it to 0. 
}

// TODO 2 — number of LEAVES (nodes with no children) in the tree.
int countLeaves(Node* t) {
    if(!t) return 0; //nullptr
    if(countLeaves(t->left) + countLeaves(t->right) == 0) return 1; //fine to return 1 because in theory two null pointers return 0.
    //I feel like I can make the above more efficient, but if the root is null, it needs to return 0.
    //if not returning 1, there is a node that needs to be accounted for.
    return countLeaves(t->left) + countLeaves(t->right);
}

// TODO 3 — number of nodes that have EXACTLY ONE child.
int countOneChild(Node* t) {
    //if(t != nullptr && t->left == nullptr && t->right == nullptr) //nevermind, its asking the AMOUNT of nodes that have exactly 1 child,
    //not if the tree has only 1 node in it.

    if(t == nullptr) return 0;
    if((t->left != nullptr && t->right == nullptr) || (t->left == nullptr && t->right != nullptr))
        return countOneChild(t->left) + countOneChild(t->right) + 1;

    else return countOneChild(t->left) + countOneChild(t->right);

    //if((t->left && !t->right) || (!t->left && t->right)) //is this the same as the expression above?
}

// TODO 4 — does the tree contain `key`?
//   Use the BST ordering so you follow only ONE root-to-leaf path.
bool contains(Node* t, int key) {
    if(!t) return false;
    if(t->key == key) return true;
    if(key < t->key) return contains(t->left, key);
    else return contains(t->right, key);
    //Should work like this, if it hits a nullpointer, it returns false.
    //if its not a null pointer, it compares.
    //if its not the right key, it will navigate till it finds the location the key should be.
    //therefore, if it navigates to a place where the key should be but isn't, it has to return false since what should be there isn't.
}

// STRETCH (optional) — return true iff t is a valid BST: for EVERY node, its
//   key is greater than every key in its left subtree and less than every key
//   in its right subtree.
bool isValidBSThelper(Node* t, int min, int max){
    if(!t) return true;
    if(t->key > max || t->key < min){
        return false;
    }
    return isValidBSThelper(t->left, min, t->key-1) && isValidBSThelper(t->right, t->key+1, max);
    //the idea here is since we arent doing duplicates, then anything on T's left must be smaller, same in reverse for the right.
    //need to do a valid check on a false tree to make sure it works.
}

bool isValidBST(Node* t) {
    return isValidBSThelper(t, -2147483648, 2147483647);
}




// ===========================================================================
//  EXTRA CREDIT — expression trees
// ===========================================================================
// An expression tree stores an OPERAND in each leaf and a binary OPERATOR
// ('+','-','*','/') in each internal node. `val` is meaningful only in leaves;
// `op` is meaningful only in internal nodes.
struct ExprNode {
    char      op;                  // '+','-','*','/'  (internal nodes)
    int       val;                 // operand value     (leaves)
    ExprNode* left;
    ExprNode* right;
};
ExprNode* leaf(int v)                              { return new ExprNode{0, v, nullptr, nullptr}; }
ExprNode* opNode(char o, ExprNode* a, ExprNode* b) { return new ExprNode{o, 0, a, b}; }

void destroyExpr(ExprNode* t) { if (!t) return; destroyExpr(t->left); destroyExpr(t->right); delete t; }

// provided: several expression trees of increasing complexity, each labeled
struct Expr { const char* name; ExprNode* root; };
vector<Expr> buildExprs() {
    return {
        { "(2 + 3) * 4",
              opNode('*', opNode('+', leaf(2), leaf(3)), leaf(4)) },
        { "20 / (2 + 3)",
              opNode('/', leaf(20), opNode('+', leaf(2), leaf(3))) },
        { "(8 - 3) * (2 + 6)",
              opNode('*', opNode('-', leaf(8), leaf(3)), opNode('+', leaf(2), leaf(6))) },
        { "5 * ((3 * 4) + (6 / 2) - (8 + 2))",
              opNode('*', leaf(5),
                  opNode('-',
                      opNode('+', opNode('*', leaf(3), leaf(4)), opNode('/', leaf(6), leaf(2))),
                      opNode('+', leaf(8), leaf(2)))) },
        { "((10 - 2) * (3 + 1)) / (6 - 2)",
              opNode('/',
                  opNode('*', opNode('-', leaf(10), leaf(2)), opNode('+', leaf(3), leaf(1))),
                  opNode('-', leaf(6), leaf(2))) },
    };
}

// TODO EC — evaluate the expression tree rooted at t.
//   A leaf evaluates to its `val`; an internal node applies its `op` to the
//   values its two subtrees evaluate to.
int evalExprTree(ExprNode* t) {
    
    if(!t) return 0;
    int lval = evalExprTree(t->left);
    int rval = evalExprTree(t->right)
    ;
    //if(t->op == '0') return t->val; //interesting, if the char isn't cast as an int, it doesnt work. why?
    if((int)t->op == 0) return t->val;
    if(t->op == '+'){
        return lval + rval;
    }
    if(t->op == '-'){
        return lval - rval;
    }
    if(t->op == '*'){
        return lval * rval;
    }
    if(t->op == '/'){
        return lval / rval;
    }
    //shouldnt get here in theory but just in case.
    return 0;
}

// ===========================================================================
//  main — prints your results. Do not edit.
// ===========================================================================
#ifndef ICA03_GRADER          // (the autograder defines this and supplies its own main)
int main() {
    Node* root = buildExample();
    cout << "height        = " << height(root)                            << "\n";
    cout << "countLeaves   = " << countLeaves(root)                       << "\n";
    cout << "countOneChild = " << countOneChild(root)                     << "\n";
    cout << "contains(45)  = " << (contains(root, 45) ? "true" : "false") << "\n";
    cout << "contains(35)  = " << (contains(root, 35) ? "true" : "false") << "\n";
    cout << "isValidBST    = " << (isValidBST(root)  ? "true" : "false")  << "\n";

    cout << "\nextra credit — evalExprTree:\n";
    for (Expr& e : buildExprs()) {
        cout << "  " << evalExprTree(e.root) << "\t=  " << e.name << "\n";
        destroyExpr(e.root);
    }

    destroy(root);
    
    //is valid testing section
    {
        // Node* wrongroot;
        // Node* l;
        // Node* r;
        // Node* rl;
        // Node* rr;
        //had issues when I tried this, something about initializing pointers.
        
        Node* rl = new Node{19, nullptr, nullptr};
        Node* rr = new Node{40, nullptr, nullptr};
        Node* l = new Node{10, nullptr, nullptr};
        Node* r = new Node{30, rl, rr};
        Node* wrongroot = new Node{20, l, r};
        // tree looks like this (ommiting the slashes to make it more readable(?))
        //          20
        //     10        30
        //            19    40
        cout << "\nfalse bst     = " << (isValidBST(wrongroot)  ? "true" : "false")  << "\n";
        destroy(wrongroot);
    }


    
    

    return 0;
}
#endif
