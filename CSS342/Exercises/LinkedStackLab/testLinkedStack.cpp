#include <iostream>
#include "LinkedStack.h"
using namespace std;
using namespace linkedstack;


int main(){
    LinkedStack stack;
    cout << stack.empty() << endl;
    stack.push("James");
    cout << stack.empty() << " " << stack.top() << endl;
    stack.print();

    return 0;
}