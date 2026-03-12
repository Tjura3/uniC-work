#include <iostream>
#include "slinkedlist.h"

using namespace std;
using namespace slinkedlist;
int main(){
    LinkedList<string> list = LinkedList<string>();
    string e = "running";
    while (e != "quit"){        
        cout << "Enter a new item : ";
        cin >> e;
        if (e == "quit"){
            break;
        }
        // myList.addFront(e);
        list.addBack(e);
    }
    //list.printList();
    return 0;
}