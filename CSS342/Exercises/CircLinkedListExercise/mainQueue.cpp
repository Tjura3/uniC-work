#include <iostream>
#include "queue_clinkedlist.h"

using namespace std;
using namespace lqueue;

int main(){
    ArrayQueue<int> Q; 

    int num;
    for (int i = 0; i < 10; i++){
        cout << "Enter a number : ";
        cin >> num;
        Q.enqueue(num);
    }
    
    Q.printQueue();
    cout << endl;
    
    for (int i = 0; i < 5; i++){        
        Q.dequeue();
    }    

    Q.printQueue();
    cout << endl;

    return 0;
}