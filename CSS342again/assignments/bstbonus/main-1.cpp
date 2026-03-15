#include <iostream>
#include "bst.h"

using namespace std;

int main() {
    BST tree;

    // Insert values
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    for (int x : values) {
        tree.insert(x);
    }

    // Duplicate test
    cout << (tree.insert(30) ? "inserted\n" : "duplicate\n");

    // kth smallest tests
    int result;
    if (tree.kth_smallest(1, result)) cout << result << "\n";
    if (tree.kth_smallest(4, result)) cout << result << "\n";
    if (!tree.kth_smallest(8, result)) cout << "invalid k\n";

    // LCA tests
    if (tree.lca(20, 40, result)) cout << result << "\n";
    if (tree.lca(20, 80, result)) cout << result << "\n";
    if (!tree.lca(20, 99, result)) cout << "lca not found\n";

    // Level order
    auto level = tree.level_order_print();
    for (size_t i = 0; i < level.size(); ++i) {
        cout << level[i];
        if (i + 1 < level.size()) cout << " ";
    }
    cout << "\n";

    // is_balanced test
    cout << (tree.is_balanced() ? "balanced\n" : "not balanced\n");

    // Create an unbalanced tree
    BST skewed;
    for (int i = 1; i <= 7; ++i) {
        skewed.insert(i);
    }
    cout << (skewed.is_balanced() ? "balanced\n" : "not balanced\n");

    return 0;
}