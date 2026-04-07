#include "CircularLinkedList.h"
#include <iostream>

using namespace std;

void runTests();


int main(){
    
    //Testing the first scenario
    CircularLinkedList<string> residents({"Laing", "Wilder",  "Frobisher"});
    while(residents.size() > 1) {
        residents.visualize();
        string eaten = residents.removeNext(1);  // k == 1
        cout << "Eaten: " << eaten << "\n";
    }
    string winner = residents.getCurrent();
    cout << "The winner is " << winner << "!\n";


    //One more test here to make sure the code runs right
    CircularLinkedList<int> numbers({1, 2, 3, 4, 5});
    while(numbers.size() > 1) {
        numbers.visualize();
        int killed = numbers.removeNext(3);  // k == 1
        cout << "Killed: " << killed << "\n";
    }
    int success = numbers.getCurrent();
    cout << "The winner is " << success << "!\n";

    cout << "\n\nProper test time _________________________________________" << endl; // I know its proper to do endl but I feel like using \n at the end of a string is just more efficient, im not sure though.
    //writing proper tests now
    runTests();


    return 0;

    

}

void runTests() {
    int passed = 0;
    int total = 0;

    auto report = [&](bool condition, string name) {
        total++;
        if (condition) {
            cout << "[PASS] " << name << endl;
            passed++;
        } else {
            cout << "[FAIL] " << name << endl;
        }
    };
    //write a test on adding 5, then removing a specific one.
    //write a test to get the size.
    //write a test to get the current
    //bounds check
    //empty remove + size check

    // Origional scenario
    {
        CircularLinkedList<string> residents({"Laing", "Wilder", "Frobisher"});
        string wild;
        string lai;
        while(residents.size() > 1) {
            string temp = residents.removeNext(1);
            if(wild == "") wild = temp;
            else lai = temp;
        }
        bool match = (wild == "Wilder" && lai == "Laing");
        bool winner = (residents.getCurrent() == "Frobisher");
        report(match && winner, "Original Scenario");
    }

    // --- TEST 2: Removing with k=0 (Current node) ---
    {
        CircularLinkedList<int> nums({10, 20, 30});
        int removed = nums.removeNext(0); // Should remove 10 (curr)
        report(removed == 10 && nums.getCurrent() == 20 && nums.size() == 2, "RemoveNext(0) Logic");
    }

    // --- TEST 3: Large k (Wrapping multiple times) ---
    {
        CircularLinkedList<string> chars({"A", "B", "C"});
        // k=4: Move from A -> B -> C -> A -> B. Victim is B.
        string victim = chars.removeNext(4);
        report(victim == "B" && chars.getCurrent() == "C", "Large k Wrapping");
    }

    //goto empty
    {
        CircularLinkedList<int> singleton({99});
        int val = singleton.removeNext(1); //basically just make sure this circles back
        report(val == 99 && singleton.size() == 0, "Go To Empy");
    }

    //Bounds check
    {
        CircularLinkedList<int> nums({1, 2});
        int val = nums.removeNext(-5); 
        report(val == 1 && nums.size() == 1, "If this doesn't say error above, it failed");
    }

    
    cout << "Results: " << passed << " / " << total << " passed." << endl;
}
