//I did end up adding code to main to add tests for erase, 
//and I added printHorizontal to help me visualize during testing, 
//making sure things were working as intended.

// CSS 343 · ICA 04 — AVL trees.  Fill in the TODOs, then run the application.
//
//   build:        g++ -std=c++17 -g -o ica04 ica04.cpp
//   run:          ./ica04
//   leak-check:   valgrind --leak-check=full ./ica04     (ICA 04 IS LEAK-GRADED)
//
// The Node struct, the helpers, and main() (a unit-test battery + the
// worst-case application) are GIVEN — do not edit them. You implement bf, fix,
// the two rotations, rebalance, insert, isAVL, and contains. Run early and
// often: the tests report [PASS]/[FAIL] one by one as you fill in the TODOs.

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
using namespace std;

struct Node {
    int   key;
    Node* left   = nullptr;
    Node* right  = nullptr;
    int   height = 0;                 // leaf = 0, empty subtree = -1
    Node(int k) : key(k) {}
};

// ---- GIVEN ---------------------------------------------------------------
int height(Node* t) { return t ? t->height : -1; }   // null-safe height

void inorder(Node* t, vector<int>& out) {            // collect keys in order
    if (!t) return;
    inorder(t->left, out);
    out.push_back(t->key);
    inorder(t->right, out);
}

int sizeOf(Node* t) { return t ? 1 + sizeOf(t->left) + sizeOf(t->right) : 0; }

void destroy(Node* t) {                              // free the whole tree
    if (!t) return;
    destroy(t->left);
    destroy(t->right);
    delete t;
}

// ---- TODO 1 — balance factor and height maintenance ----------------------
int bf(Node* t) {
    // TODO: return height(left) - height(right); return 0 for a null node.
    if(!t) return 0;
    return height(t->left) - height(t->right);
    return 0;
}
void fix(Node* t) {
    // TODO: set t->height = 1 + max(height(t->left), height(t->right)).
    //height is primarily managed through fix.
    if(!t) return;
    t->height = 1 + max(height(t->left), height(t->right));
}

// ---- TODO 2 — rotations (each O(1); remember to fix() heights) ------------
Node* rotateRight(Node* y) {
    // TODO: x = y->left; move x->right under y; hang y under x; fix y then x;
    //       return x (the new subtree root).
    Node* x = y->left;
    Node* temp = x->right;
    x->right = y;
    y->left = temp;
    fix(y);
    fix(x);
    return x;
}
Node* rotateLeft(Node* x) {
    // TODO: the mirror image of rotateRight.
    Node* y = x->right;
    Node* temp = y->left;
    y->left = x;
    x->right = temp;
    fix(x);
    fix(y);
    return y;
}

// ---- TODO 3 — rebalance: the four cases (LL / RR / LR / RL) ---------------
Node* rebalance(Node* t) {
    // TODO: fix(t) first, then:
    //   if bf(t) >  1: if bf(t->left)  < 0  t->left  = rotateLeft(t->left);   return rotateRight(t);
    //   if bf(t) < -1: if bf(t->right) > 0  t->right = rotateRight(t->right); return rotateLeft(t);
    //   otherwise return t.
    fix(t);
    if(bf(t) > 1){
        if(bf(t->left) < 0) { //LR rotation if true, other
            t->left = rotateLeft(t->left);
        }
        return rotateRight(t);
    }
    if(bf(t) < -1){
        if(bf(t->right) > 0){ //RL rotation, RR if not.
            t->right = rotateRight(t->right);
        }
        return rotateLeft(t);
    }
    //remember the above works because the scond balance factor tests which side the imbalance is on.
    return t;
}

// ---- TODO 4 — insert: BST insert, then rebalance on the way up ------------
Node* insert(Node* t, int k) {
    // TODO: if empty, return new Node(k). Recurse left/right by comparison
    //       (ignore duplicates). Then return rebalance(t).
    //Why is t here? is it root?
    
    if(t == nullptr) return new Node(k);
    
    if(k < t->key){
        t->left = insert(t->left, k);
    }else if(k > t->key){
        t->right = insert(t->right, k);
    }else return t;

    return rebalance(t);
    
}

// ---- TODO 5 — checks (stretch: also write erase with rebalancing) --------
bool isAVL(Node* t) {
    // TODO: true if |bf(t)| <= 1 AND both subtrees are AVL (recursively).
    return t == nullptr || (abs(bf(t)) <= 1 && isAVL(t->left) && isAVL(t->right));
    return true;
}
bool contains(Node* t, int k) {
    // TODO: standard BST search.
    if(t == nullptr) return false;
    if(t->key == k) return true;
    if(k < t->key) return contains(t->left, k);
    if(k > t->key) return contains(t->right, k);
    return false;
}

//Erase extra credit
Node* erase(Node* t, int k) {
    if(t == nullptr) return nullptr;

    if(k < t->key){
        t->left = erase(t->left, k);
    }else if(k > t->key){
        t->right = erase(t->right, k);
    }else{
        //found
        if(t->left == nullptr && t->right == nullptr){
            delete t;
            return nullptr;
        }else if(t->left == nullptr){
            Node* temp = t->right;
            delete t;
            return temp;
        }else if(t->right == nullptr){
            Node* temp = t->left;
            delete t;
            return temp;
        }else{
            //go to the right and keep going left.
            //basically like deleting the root of an avl tree and finding successor.
            Node* temp = t->right;
            while(temp->left != nullptr){
                temp = temp->left;
            }
            t->key = temp->key; //just move the key up.
            t->right = erase(t->right, temp->key); 
        }
    }
    return rebalance(t);
}

//prints in reverse pre-order, used stack overflow to help me make this.
//prints (height, balance factor)
void printHorizontal(Node* t, int depth = 0) {
    if (!t) return;
    printHorizontal(t->right, depth + 1);
    for (int i = 0; i < depth; ++i) {
        cout << "    ";
    }
    cout << "> " << t->key << " (h:" << t->height << ", b:" << bf(t) << ")\n";
    printHorizontal(t->left, depth + 1);
}


// ==========================================================================
// UNIT TESTS + APPLICATION (given — do not edit).
// ==========================================================================
#ifndef ICA04_GRADER
static int passCnt = 0, failCnt = 0;
static void check(bool ok, const string& what) {
    (ok ? passCnt : failCnt)++;
    cout << (ok ? "  [PASS] " : "  [FAIL] ") << what << '\n';
}
static Node* build(const vector<int>& ks) { Node* r = nullptr; for (int k : ks) r = insert(r, k); return r; }
static bool sortedInorder(Node* t) { vector<int> v; inorder(t, v); return is_sorted(v.begin(), v.end()); }



int main() {
    // -- T1: basics --------------------------------------------------------
    cout << "T1 · basics\n";
    check(height(nullptr) == -1, "height(empty) == -1");
    Node* one = build({42});
    check(one != nullptr && sizeOf(one) == 1 && height(one) == 0, "single insert: 1 node, height 0");
    check(contains(one, 42) && !contains(one, 7), "contains: hit and miss on 1 node");
    cout << contains(one, 42) << endl;
    destroy(one);

    // -- T2..T5: one test per rotation case --------------------------------
    // each inserts 3 keys that force exactly one case; a correct AVL ends
    // with the MIDDLE key at the root and height 1.
    struct Case { const char* name; vector<int> ks; };
    vector<Case> cases = {
        {"T2 · RR (rotateLeft)",        {1, 2, 3}},
        {"T3 · LL (rotateRight)",       {3, 2, 1}},
        {"T4 · LR (double: left-right)", {3, 1, 2}},
        {"T5 · RL (double: right-left)", {1, 3, 2}},
    };
    for (auto& c : cases) {
        cout << c.name << '\n';
        Node* t = build(c.ks);
        check(t != nullptr && t->key == 2, "root is the middle key (2)");
        check(t && t->left && t->left->key == 1 && t->right && t->right->key == 3, "children are 1 and 3");
        check(height(t) == 1, "height is 1 (not a path)");
        destroy(t);
    }

    // -- T6: duplicates are ignored -----------------------------------------
    cout << "T6 · duplicates\n";
    Node* d = build({5, 5, 5, 5});
    check(sizeOf(d) == 1, "inserting 5 four times keeps 1 node");
    destroy(d);

    // -- T7: a shuffled batch stays a valid, sorted, balanced BST -----------
    cout << "T7 · shuffled input\n";
    Node* s = build({9, 3, 14, 1, 6, 12, 16, 2, 5, 8, 10, 13, 15, 4, 7, 11});
    check(sizeOf(s) == 16, "all 16 keys inserted");
    check(sortedInorder(s), "in-order is sorted (still a BST)");
    check(isAVL(s), "isAVL holds everywhere");
    check(height(s) <= 5, "height <= 5 for 16 keys");
    destroy(s);

    // -- T8: THE APPLICATION — worst-case input, sorted stream --------------
    // a ticket registry hands out strictly increasing ids; sorted input is the
    // worst case for a plain BST (a path of height N-1). The AVL must stay
    // logarithmic.
    cout << "T8 · worst case: sorted 1..1023\n";
    const int N = 1023;                          // 2^10 - 1 ids
    Node* root = nullptr;
    for (int k = 1; k <= N; ++k) root = insert(root, k);
    int bound = (int)ceil(1.44 * log2((double)N));         // ~14
    cout << "     AVL height = " << height(root) << "   (a plain BST would be " << N - 1 << ")\n";
    check(sizeOf(root) == N, "all 1023 keys inserted");
    check(height(root) <= bound, "height <= 1.44*log2(N) = " + to_string(bound));
    check(isAVL(root), "isAVL holds everywhere");
    check(sortedInorder(root), "in-order is sorted");
    check(contains(root, 512) && !contains(root, 9999), "contains: hit 512, miss 9999");
    destroy(root);

    // -- T9: the mirror worst case, reverse-sorted --------------------------
    cout << "T9 · worst case: reverse-sorted 1023..1\n";
    Node* rev = nullptr;
    for (int k = N; k >= 1; --k) rev = insert(rev, k);
    check(sizeOf(rev) == N && height(rev) <= bound && isAVL(rev), "same guarantees on the mirror input");
    destroy(rev);


    //T10 erase test
    cout << "\n\nT10 erase test\n";
    cout << "Tree before any issues, will print after erasing 2 and 8.\n";
    Node* e = build({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15});
    printHorizontal(e);
    
    e = erase(e, 1);
    check(sizeOf(e) == 14 && !contains(e, 1), "Remove 1 leaf node");
    check(isAVL(e), "Tree still AVL");
    
    e = erase(e, 2);
    check(sizeOf(e) == 13 && !contains(e, 2), "Removing 2, check if 3 takes its place.");
    check(isAVL(e), "Tree still AVL");
    printHorizontal(e);
    
    
    //9 should take 8's place.
    cout << "Check below regarding this test, if 9 takes 8's place.\n";
    e = erase(e, 8);
    check(sizeOf(e) == 12 && !contains(e, 8), "Remove 8 (root)");
    printHorizontal(e);
    check(isAVL(e), "Tree Still AVL after delete w/ root");
    printHorizontal(e);
    
    
    destroy(e);

    cout << passCnt << " passed, " << failCnt << " failed"
         << (failCnt ? "" : "  —  now run it under valgrind (must be clean)") << '\n';
    return failCnt ? 1 : 0;


}
#endif
