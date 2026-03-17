// Extended testing for BonusBST
// Compile:
//   g++ -std=c++17 -Wall -Wextra -pedantic -fsanitize=address main_extended.cpp bst.cpp -o bst_bonus_extended
// Run:
//   ./bst_bonus_extended

#include <iostream>
#include <vector>
#include "bst.h"

using namespace std;

int passed = 0;
int failed = 0;

void check(const string& test_name, bool condition) {
    if (condition) {
        cout << "  [PASS] " << test_name << "\n";
        passed++;
    } else {
        cout << "  [FAIL] " << test_name << "\n";
        failed++;
    }
}

// ─────────────────────────────────────────────
// Constructor & Destructor
// ─────────────────────────────────────────────
void test_constructor() {
    cout << "\n[Constructor & Destructor]\n";

    // Empty tree: level_order_print should return empty vector
    BST tree;
    check("Empty tree level_order returns empty vector",
          tree.level_order_print().empty());

    // Empty tree: kth_smallest should return false
    int result;
    check("Empty tree kth_smallest(1) returns false",
          !tree.kth_smallest(1, result));

    // Empty tree: is_balanced should return true (vacuously)
    check("Empty tree is_balanced returns true",
          tree.is_balanced());

    // Empty tree: lca should return false
    check("Empty tree lca returns false",
          !tree.lca(1, 2, result));

    // Destructor tested implicitly via ASan — allocate and let go out of scope
    {
        BST temp;
        for (int i = 1; i <= 10; ++i) temp.insert(i);
    }
    check("Destructor runs without leak (ASan will catch if not)", true);
}

// ─────────────────────────────────────────────
// Insert
// ─────────────────────────────────────────────
void test_insert() {
    cout << "\n[Insert]\n";

    BST tree;

    check("Insert into empty tree returns true",  tree.insert(50));
    check("Insert left child returns true",       tree.insert(30));
    check("Insert right child returns true",      tree.insert(70));
    check("Insert duplicate returns false",       !tree.insert(50));
    check("Insert duplicate (left) returns false",!tree.insert(30));
    check("Insert duplicate (right) returns false",!tree.insert(70));

    // BST ordering: level order should be 50, 30, 70
    vector<int> expected = {50, 30, 70};
    check("BST ordering maintained after inserts",
          tree.level_order_print() == expected);

    // Insert a full balanced tree
    BST balanced;
    int vals[] = {50, 30, 70, 20, 40, 60, 80};
    for (int v : vals) balanced.insert(v);
    vector<int> exp2 = {50, 30, 70, 20, 40, 60, 80};
    check("Full balanced tree level order correct",
          balanced.level_order_print() == exp2);
}

// ─────────────────────────────────────────────
// kth_smallest
// ─────────────────────────────────────────────
void test_kth_smallest() {
    cout << "\n[kth_smallest]\n";

    BST tree;
    int vals[] = {50, 30, 70, 20, 40, 60, 80};
    for (int v : vals) tree.insert(v);
    // Sorted order: 20, 30, 40, 50, 60, 70, 80

    int result;

    check("k=1 returns smallest (20)",
          tree.kth_smallest(1, result) && result == 20);
    check("k=2 returns 30",
          tree.kth_smallest(2, result) && result == 30);
    check("k=4 returns median (50)",
          tree.kth_smallest(4, result) && result == 50);
    check("k=7 returns largest (80)",
          tree.kth_smallest(7, result) && result == 80);

    // Invalid k
    check("k=0 returns false",
          !tree.kth_smallest(0, result));
    check("k=-1 returns false",
          !tree.kth_smallest(-1, result));
    check("k=8 (> n) returns false",
          !tree.kth_smallest(8, result));
    check("k=100 returns false",
          !tree.kth_smallest(100, result));

    // Single node tree
    BST single;
    single.insert(42);
    check("Single node: k=1 returns 42",
          single.kth_smallest(1, result) && result == 42);
    check("Single node: k=2 returns false",
          !single.kth_smallest(2, result));

    // Right-skewed tree
    BST skewed;
    for (int i = 1; i <= 5; ++i) skewed.insert(i);
    check("Right-skewed: k=3 returns 3",
          skewed.kth_smallest(3, result) && result == 3);
    check("Right-skewed: k=5 returns 5",
          skewed.kth_smallest(5, result) && result == 5);
}

// ─────────────────────────────────────────────
// level_order_print
// ─────────────────────────────────────────────
void test_level_order() {
    cout << "\n[level_order_print]\n";

    // Empty tree
    BST empty;
    check("Empty tree returns empty vector",
          empty.level_order_print().empty());

    // Single node
    BST single;
    single.insert(1);
    check("Single node returns {1}",
          single.level_order_print() == vector<int>{1});

    // Balanced tree
    BST tree;
    int vals[] = {50, 30, 70, 20, 40, 60, 80};
    for (int v : vals) tree.insert(v);
    vector<int> expected = {50, 30, 70, 20, 40, 60, 80};
    check("Balanced tree BFS order correct",
          tree.level_order_print() == expected);

    // Right-skewed tree
    BST right;
    for (int i = 1; i <= 4; ++i) right.insert(i);
    vector<int> exp_right = {1, 2, 3, 4};
    check("Right-skewed BFS order correct",
          right.level_order_print() == exp_right);

    // Left-skewed tree
    BST left;
    for (int i = 4; i >= 1; --i) left.insert(i);
    vector<int> exp_left = {4, 3, 2, 1};
    check("Left-skewed BFS order correct",
          left.level_order_print() == exp_left);
}

// ─────────────────────────────────────────────
// LCA
// ─────────────────────────────────────────────
void test_lca() {
    cout << "\n[LCA]\n";

    BST tree;
    int vals[] = {50, 30, 70, 20, 40, 60, 80};
    for (int v : vals) tree.insert(v);

    int result;

    // Standard cases
    check("LCA(20, 40) = 30",
          tree.lca(20, 40, result) && result == 30);
    check("LCA(40, 20) = 30 (order-independent)",
          tree.lca(40, 20, result) && result == 30);
    check("LCA(20, 80) = 50",
          tree.lca(20, 80, result) && result == 50);
    check("LCA(60, 80) = 70",
          tree.lca(60, 80, result) && result == 70);

    // Ancestor is one of the nodes
    check("LCA(30, 20) = 30 (ancestor case)",
          tree.lca(30, 20, result) && result == 30);
    check("LCA(50, 80) = 50 (root is ancestor)",
          tree.lca(50, 80, result) && result == 50);

    // Root as LCA
    check("LCA(20, 80) = 50 (root)",
          tree.lca(20, 80, result) && result == 50);

    // Same node
    check("LCA(40, 40) = 40 (same node)",
          tree.lca(40, 40, result) && result == 40);

    // Node not in tree
    check("LCA(20, 99) returns false (missing node)",
          !tree.lca(20, 99, result));
    check("LCA(99, 100) returns false (both missing)",
          !tree.lca(99, 100, result));

    // Empty tree
    BST empty;
    check("LCA on empty tree returns false",
          !empty.lca(1, 2, result));
}

// ─────────────────────────────────────────────
// is_balanced
// ─────────────────────────────────────────────
void test_is_balanced() {
    cout << "\n[is_balanced]\n";

    // Empty tree
    BST empty;
    check("Empty tree is balanced", empty.is_balanced());

    // Single node
    BST single;
    single.insert(1);
    check("Single node is balanced", single.is_balanced());

    // Perfectly balanced tree
    BST balanced;
    int vals[] = {50, 30, 70, 20, 40, 60, 80};
    for (int v : vals) balanced.insert(v);
    check("Perfect balanced tree (height 3) is balanced",
          balanced.is_balanced());

    // Balanced with slight lean (|diff| == 1)
    BST lean;
    int lean_vals[] = {50, 30, 70, 20};
    for (int v : lean_vals) lean.insert(v);
    check("Tree with |diff|=1 is balanced", lean.is_balanced());

    // Right-skewed (1,2,3,4,5,6,7) — unbalanced
    BST skewed;
    for (int i = 1; i <= 7; ++i) skewed.insert(i);
    check("Right-skewed tree (1–7) is not balanced",
          !skewed.is_balanced());

    // Left-skewed — unbalanced
    BST left_skewed;
    for (int i = 7; i >= 1; --i) left_skewed.insert(i);
    check("Left-skewed tree (7–1) is not balanced",
          !left_skewed.is_balanced());

    // Unbalanced at subtree level, not root
    BST sub;
    int sub_vals[] = {50, 30, 70, 20, 10};
    for (int v : sub_vals) sub.insert(v);
    check("Imbalance in subtree detected", !sub.is_balanced());
}

// ─────────────────────────────────────────────
// Summary
// ─────────────────────────────────────────────
int main() {
    cout << "========================================\n";
    cout << "         BST Comprehensive Tests        \n";
    cout << "========================================\n";

    test_constructor();
    test_insert();
    test_kth_smallest();
    test_level_order();
    test_lca();
    test_is_balanced();

    cout << "\n========================================\n";
    cout << "  Results: " << passed << " passed, " << failed << " failed\n";
    cout << "========================================\n";

    return failed == 0 ? 0 : 1;
}