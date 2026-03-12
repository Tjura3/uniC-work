//professor work
#include "slinkedlist.h"
#include "complex.h"
#include <iostream>

using namespace std;
using namespace mycomplex;
using namespace slinkedlist;


int main(){
    LinkedList<string> myList = LinkedList<string>();

    string e = "bazinga";
    while (e != "quit"){        
        cout << "Enter a new item : ";
        cin >> e;
        if (e == "quit"){
            break;
        }
        // myList.addFront(e);
        myList.addBack(e);
    }

    myList.printList();
    myList.removeFront();
    myList.printList();
    myList.removeBack();
    myList.printList();

    myList.addAt(myList.getHead(), "H");
    myList.printList();

    // myList.addAt(myList.getHead()->getNext()->getNext()->getNext(), "H->next->next->next");
    myList.addAt(myList.getHead()->getNext(), "H->next");
    myList.printList();




    cout << endl << "Linked list with complex numbers : " << endl;
    LinkedList<Complex> myComplexList = LinkedList<Complex>();

    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i=0; i<5; i++){
        myComplexList.addFront(Complex(rand() % 10, rand() % 10));        
    }


    return 0;
}