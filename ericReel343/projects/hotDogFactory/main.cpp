#include <iostream>
#include <string>
#include <vector>
#include "rng.h"
#include "foodstuff.h"
#include "heap.h"   // TODO
#include "functors.h" // TODO

using std::cout;
using std::string;


// TODO:  implement heap class
// TODO:  implement Cheapest functor to prioritize queue of foodstuffs by lowest cost per weight

template <typename T>
bool report(string testName, T actual, T expected) {
    if (actual == expected) {
        cout << "[PASS] " << testName << endl;
        return true;
    } else {
        cout << "[FAIL] " << testName << endl;
        cout << "   Expected: " << expected << endl;
        cout << "   Actual:   " << actual << endl;
        return false;
    }
}

void runTests() {
    // TODO:  add some tests make sure the code actually works?
    Heap<Foodstuff, Cheapest> h;
    report(string("Report Test, Fail is pass"), string("And it failed!"), string("Expected this to fail..."));
    
    Foodstuff a("Hot dogger!", 10, 50);
    Foodstuff b("Cheap dogger", 10, 10);
    Foodstuff c("Tripple aged dogger", 2, 40);

    h.add(a);
    h.add(b);
    h.add(c);
    
    //Size check
    //checking the 3 values were outputting in the right order
    //lastly, checking if empty works.
    
    report("Size Test", (int)h.size(), 3);
    report("Cheapest Item", h.remove().name, string("Cheap dogger"));
    report("Middle Item", h.remove().name, string("Hot dogger!"));
    report("Most Expensive Item", h.remove().name, string("Tripple aged dogger"));
    report("Empty Heap Check", h.empty(), true);

    
}

void makeHotDogs() {
    Rng rng(21324); 

    Heap<Foodstuff, Cheapest> h;
    vector<Foodstuff> ingredients;

    for(int i = 0; i < 10; i++) {
        while(h.size() < 10) {
            Foodstuff ingredient = getRandomFoodstuff(rng);
            h.add(ingredient);
        }
        ingredients.push_back(h.remove());
    }

    int totalCost = 0;
    int totalWeight = 0;
    for(Foodstuff ingredient : ingredients) {
        printf("%-12s - cost: %3d  weight: %3d  CostPerPound: %3f\n", ingredient.name.c_str(), ingredient.cost, ingredient.weight, ingredient.getCostPerPound());
        totalCost += ingredient.cost;
        totalWeight += ingredient.weight;
    }
    cout << "total cost:   " << totalCost << "\n";
    cout << "total weight: " << totalWeight << "\n";
}


int main() {
    runTests();
    makeHotDogs();
    return 0;
}