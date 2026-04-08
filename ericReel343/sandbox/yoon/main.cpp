#include <iostream>
#include <string>
#include "CircularLinkedList.h"

void testCase() {
    cout << "\nTEST\n";

    CircularLinkedList<string> list({"First", "Second",  "Third"});

    list.printList();

    while (list.size() > 1) {
        string removed = list.removeNext(1);
        cout << "Removed: " << removed << endl;
        list.printList();
    }

    string winner = list.getCurrent();

    if (winner == "Third") {
        cout << "TEST PASSED.Expected: Third, actual value: " << winner << endl;
    } else {
        cout << "TEST FAILED. Expected: Third, actual value: " << winner << endl;
    }

    cout << "-----\n";
}

int main() {

    testCase();

    CircularLinkedList<string> residents({"Laing", "Wilder",  "Frobisher"});

    while(residents.size() > 1) {
        string eaten = residents.removeNext(1);  // k == 1
        cout << "Eaten: " << eaten << "\n";
    }

    string winner = residents.getCurrent();
    cout << "The winner is " << winner << "!\n";
}