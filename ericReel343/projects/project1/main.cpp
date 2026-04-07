#include "CircularLinkedList.h"
#include <iostream>

using namespace std;

void runTests();


int main(){
    /**
     * In main, I have two tests I ran without proper test cases.
     * Afterwards, I run a proper system of test cases below.
     */
    //Testing the first scenario
    CircularLinkedList<string> residents({"Laing", "Wilder",  "Frobisher"});
    while(residents.size() > 1) {
        residents.visualize();
        string eaten = residents.removeNext(1);  // k == 1
        cout << "Eaten: " << eaten << "\n";
    }
    string winner = residents.getCurrent();
    cout << "The winner is " << winner << "!\n\n";


    //One more test here to make sure the code runs right
    CircularLinkedList<int> numbers({1, 2, 3, 4, 5});
    while(numbers.size() > 1) {
        numbers.visualize();
        int killed = numbers.removeNext(3);  // k == 1
        cout << "Killed: " << killed << "\n";
    }
    int success = numbers.getCurrent();
    cout << "The winner is " << success << "!\n";

    cout << "\nProper test time _________________________________________" << endl; // I know its proper to do endl but I feel like using \n at the end of a string is just more efficient, im not sure though.
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

    //Example
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
        report(match && winner, "Example");
    }

    //Removal check, should remove curr, and it should be 20.
    {
        CircularLinkedList<int> nums({10, 20, 30});
        int removed = nums.removeNext(0); // Should remove 10 (curr)
        report(removed == 10 && nums.getCurrent() == 20 && nums.size() == 2, "Removal check");
    }

    //wrap around to B
    {
        CircularLinkedList<string> chars({"A", "B", "C"});
        // k=4: Move from A -> B -> C -> A -> B. Victim is B.
        string kill = chars.removeNext(4);
        report(kill == "B" && chars.getCurrent() == "C", "Wrap removing B");
    }

    //goto empty
    {
        CircularLinkedList<int> singleton({99});
        int val = singleton.removeNext(99); //basically just make sure this circles back
        report(val == 99 && singleton.size() == 0, "Empty after many loops");
    }

    //Bounds check
    {
        CircularLinkedList<int> nums({1, 2});
        int val = nums.removeNext(-5); 
        report(val == 1 && nums.size() == 1, "If this doesn't say error above, it failed");
    }
    
    //size is 12
    {
        CircularLinkedList<int> intcircle({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
        int val = intcircle.size();
        report(val == 12, "Size is 12");
    }

    //empty remove
    {
        CircularLinkedList<int> emptycircle({});
        emptycircle.removeNext(1);
        emptycircle.removeNext(20);
        int val = emptycircle.size();
        report(val == 0, "Empty removal");
    }

    cout << "Results: " << passed << " / " << total << " passed." << endl;
}
