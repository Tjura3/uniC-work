// CSS 343 · PA2 — BinTree implementation SKELETON.
// Every method is a TODO except displayTree (given, for debugging). The
// skeleton compiles and links as-is; fill the TODOs and re-diff against
// expected-output.txt as you go.
//
// Porting note (encouraged): your ICA 04 bf/fix/rotate/rebalance code IS the
// AVL fix-up — adapt it to this Node type and count rotations as you go.
// The REDBLACK fix-up is the three-if left-leaning insert from the §3.3
// reading (rotate-left · rotate-right · flip-colors), with the root kept black.
//
// MERGE — design your own algorithm. Candidate directions (pick, combine, or
// invent): a loop over the other tree's keys calling insert; flatten both to
// sorted arrays, union-merge, rebuild; the same but STREAMING with two
// iterator stacks (never materialize the arrays); rebuild in place by
// rotating the trees into vines; or look up split/join merging. Predict your
// algorithm's time and space BEFORE you measure — the report reconciles the
// two, and the leaderboard ranks both.
//
// Useful fact if you rebuild balanced in REDBLACK mode: a perfectly balanced
// tree is a valid left-leaning red-black tree if the DEEPEST-level nodes are
// RED and all others BLACK (build with the upper median so the partial level
// leans left). If you merge by re-inserting, no color rule is needed.
#include "bintree.h"

// ---- GIVEN — displayTree (debugging aid; do not change) ---------------------
void BinTree::displayTree() const { displayRec(root, "Root:", 0); }
void BinTree::displayRec(Node* t, const string& tag, int depth) {
    if (!t) return;
    cout << string(4 * depth, ' ') << tag << ' ' << t->key << '\n';
    displayRec(t->left,  "L---", depth + 1);
    displayRec(t->right, "R---", depth + 1);
}

// ---- TODO 1 — construction, destruction, deep copy --------------------------
BinTree::BinTree(Mode m) : root(nullptr), mode_(m) {}

BinTree::BinTree(const BinTree& other) : root(nullptr), mode_(other.mode_) {
    // TODO: deep-copy other's tree (copy height/red fields too) + the counters
    rot_ = other.rot_;
    flips_ = other.flips_;
    auxBytes_ = other.auxBytes_;
    root = copyOther(other.root);
}

BinTree::Node* BinTree::copyOther(const Node* curr){
    if(!curr){
        return nullptr;
    }
    BinTree::Node* newNode = new BinTree::Node();
    newNode->key = curr->key;
    newNode->height = curr->height;
    newNode->red = curr->red;
    newNode->left = copyOther(curr->left);
    newNode->right = copyOther(curr->right);
    return newNode;
}



BinTree::~BinTree() {
    // TODO: delete every node (post-order)
    destroy(root);
}
void BinTree::destroy(Node* curr){
    if(!curr) return;
    destroy(curr->left);
    destroy(curr->right);
    delete curr;
}


BinTree& BinTree::operator=(const BinTree& other) {
    // TODO: guard self-assignment; free the current tree; deep-copy other's
    //       tree, mode, and counters
    if(this == &other) return *this;
    destroy(root);
    mode_ = other.mode_;
    rot_ = other.rot_;
    flips_ = other.flips_;
    auxBytes_ = other.auxBytes_;
    root = copyOther(other.root);
    return *this;
}

// ---- TODO 2 — comparison ------------------------------------------------------
bool BinTree::operator==(const BinTree& other) const {
    // TODO: same keys AND same structure, in lockstep (ignore mode/colors/heights)
    if(this == &other) return true;    
    return snkEqual(root, other.root);
}
bool BinTree::snkEqual(const Node* a, const Node* b) const{ //structure and key equal
    if((a == nullptr) && (b == nullptr)) return true; //nullptr
    if((a == nullptr) || (b == nullptr)) return false; //one nullptr other not
    if(a->key != b->key) return false;
    return snkEqual(a->left, b->left) && snkEqual(a->right, b->right);
}
bool BinTree::operator!=(const BinTree& other) const { return !(*this == other); }

// ---- TODO 3 — queries -----------------------------------------------------------
Mode BinTree::mode() const { return mode_; }
long BinTree::rotations() const { return rot_; }
long BinTree::colorFlips() const { return flips_; }
long BinTree::mergeAuxBytes() const { return auxBytes_; }

bool BinTree::isEmpty() const {
    return root == nullptr;
}
int BinTree::size() const {
    //return 0;      // TODO
    return nodeCount(root);
}
int BinTree::nodeCount(const Node* curr) const{
    if(!curr) return 0;
    return 1 + nodeCount(curr->left) + nodeCount(curr->right);
}
int BinTree::treeHeight() const {
    // TODO: #nodes on the longest root-to-leaf path (empty = 0)
    return tHeight(root);
}
int BinTree::tHeight(const Node* curr) const{
    if(!curr) return 0;
    return 1 + max(tHeight(curr->left), tHeight(curr->right));
}
bool BinTree::contains(int key) const {
    //(void)key;
    //return false;  // TODO: iterative BST search
    //iterations = loops not recursion.
    Node* curr = root;
    while(curr != nullptr){
        if(key == curr->key) return true;
        else if(key < curr->key) curr = curr->left;
        else curr = curr->right;
    }
    return false;
}


// ---- TODO 4 — insert, per mode -----------------------------------------------------
bool BinTree::insert(int key) {
    // TODO: duplicates return false in every mode. Then:
    //   VANILLA  — plain recursive BST attach
    //   AVL      — attach, then rebalance up the path (heights, 4 cases; count
    //              each single rotation in rot_)
    //   REDBLACK — the left-leaning insert: attach RED, then on the way up
    //              rotate-left / rotate-right / flip-colors as the three ifs
    //              require (count rotations in rot_, flips in flips_);
    //              finally force the root black
    //(void)key;
    //return false;
    bool inserted = false;
    if(mode_ == Mode::VANILLA) root = insVanilla(root, key, inserted);
    else if(mode_ == Mode::AVL) root = insAVL(root, key, inserted);
    else{
        root = insRB(root, key, inserted);
        if(root) root->red = false; 
    }
    return inserted;
}
BinTree::Node* BinTree::insVanilla(Node* curr, int key, bool& inserted){
    if(!curr){
        inserted = true;
        return new Node{key};
    }
    if(key < curr->key){
        curr->left = insVanilla(curr->left, key, inserted);
    }else if(key > curr->key){
        curr->right = insVanilla(curr->right, key, inserted);
    }else inserted = false;
    return curr;
}
BinTree::Node* BinTree::insAVL(Node* curr, int key, bool& inserted){
    if(!curr){
        inserted = true;
        return new Node{key, nullptr, nullptr, 1}; //setting leaves to 1 this time.
    }
    if(key < curr->key){
        curr->left = insAVL(curr->left, key, inserted);
    }else if(key > curr->key){
        curr->right = insAVL(curr->right, key, inserted);
    }else {
        inserted = false;
        return curr;
    }
    return rebalance(curr);
}
BinTree::Node* BinTree::insRB(Node* curr, int key, bool& inserted){
    if(!curr){
        inserted = true;
        return new Node{key, nullptr, nullptr, 0, true};
    }
    if(key < curr->key){
        curr->left = insRB(curr->left, key, inserted);
    }else if(key > curr->key){
        curr->right = insRB(curr->right, key, inserted);
    }else {
        inserted = false;
        return curr;
    }
    if(isRed(curr->right) && !isRed(curr->left)) curr = RL(curr);
    if(isRed(curr->left) && isRed(curr->left->left)) curr = RR(curr);
    if(isRed(curr->left) && isRed(curr->right)) flipC(curr);
    return curr;
}

//Rotations
BinTree::Node* BinTree::RL(Node* x){
    rot_++;
    Node* y = x->right;
    Node* temp = y->left;
    y->left = x;
    x->right = temp;
    if(mode_ == Mode::REDBLACK){
        y->red = x->red;
        x->red = true;
    }else{
        fix(x);
        fix(y);
    }
    return y;
}
BinTree::Node* BinTree::RR(Node* y){
    rot_++;
    Node* x = y->left;
    Node* temp = x->right;
    x->right = y;
    y->left = temp;
    if(mode_ == Mode::REDBLACK){
        x->red = y->red;
        y->red = true;
    }else{
        fix(y);
        fix(x);
    }
    return x;
}

//AVL tree helpers
int BinTree::nheight(Node* n) const { return n ? n->height : 0; }
void BinTree::fix(Node* n){
    if(!n) return;
    n->height = 1 + max(nheight(n->left), nheight(n->right));
}
int BinTree::bf(Node* n){
    if(!n) return 0;
    return nheight(n->left) - nheight(n->right);
}
BinTree::Node* BinTree::rebalance(Node* n) {
    fix(n);
    if(bf(n) > 1){
        if(bf(n->left) < 0) { //LR rotation if true, other
            n->left = RL(n->left);
        }
        return RR(n);
    }
    if(bf(n) < -1){
        if(bf(n->right) > 0){ //RL rotation, RR if not.
            n->right = RR(n->right);
        }
        return RL(n);
    }
    return n;
}
//RB tree helpers
bool BinTree::isRed(const Node* n) const{
    return n ? n->red : false;
}
void BinTree::flipC(Node* n){
    flips_++;
    n->red = !n->red; //I just find the syntax funny.
    if (n->left)  n->left->red  = !n->left->red;
    if (n->right) n->right->red = !n->right->red;
}

// ---- TODO 5 — remove (VANILLA only) --------------------------------------------------
bool BinTree::remove(int key) {
    // TODO: if mode_ != Mode::VANILLA return false (leave the tree unchanged).
    //       Otherwise Hibbard: leaf → unlink; one child → splice; two children
    //       → copy the in-order successor's key down, remove the successor.
    //(void)key;
    //return false;
    if(mode_ != Mode::VANILLA){
        return false;
    }
    bool rm = false;
    root = rmRecurse(root, key, rm);
    return rm;
}
BinTree::Node* BinTree::rmRecurse(Node* curr, int key, bool& rm){
    if(!curr){
        rm = false;
        return nullptr;
    }
    if(key < curr->key){
        curr->left = rmRecurse(curr->left, key, rm);
    }else if(key > curr->key){
        curr->right = rmRecurse(curr->right, key, rm);
    }else{
        rm = true;
        if(!curr->left){ //right child
            Node* temp = curr->right;
            delete curr;
            return temp;
        }else if(!curr->right){
            Node* temp = curr->left;
            delete curr;
            return temp;
        }else{
            Node* temp = curr->right;
            while(temp->left != nullptr){
                temp = temp->left;
            }
            curr->key = temp->key;
            bool work;
            curr->right = rmRecurse(curr->right, temp->key, work);
        }
    }
    return curr;
} 
// ---- TODO 6 — flatten + merge ----------------------------------------------------------
void BinTree::toSortedArray(vector<int>& out) const {
    // TODO: in-order walk, push_back each key (do not modify the tree)
    //(void)out;
    inOrderVector(root, out);
}
void BinTree::inOrderVector(Node* curr, vector<int>& out) const{
    if(!curr) return;
    inOrderVector(curr->left, out);
    out.push_back(curr->key);
    inOrderVector(curr->right, out);
}

void BinTree::mergeWith(const BinTree& other) {
    // TODO: YOUR merge algorithm — any approach meeting the header contract.
    //       Remember: set auxBytes_ to the peak heap bytes you allocated
    //       (count vector capacities, explicit stacks, and every new Node);
    //       keep `other` unchanged; handle mergeWith(*this).
    //(void)other;
    if (this == &other || other.isEmpty()) {
        auxBytes_ = 0;
        return;
    }
    vector<int> v;
    other.toSortedArray(v);
    auxBytes_ = v.capacity() * sizeof(int);
    for(int val : v){
        insert(val);
    }
    //simple but... does this work?
}

// ---- TODO 7 — in-order print --------------------------------------------------------------
ostream& operator<<(ostream& os, const BinTree& t) {
    // TODO: in-order traversal, each key followed by one space, then a newline
    //(void)t;
    vector<int> v;
    t.toSortedArray(v);
    for(int val: v){
        os << val << " ";
    }
    os << '\n';
    return os;
}
