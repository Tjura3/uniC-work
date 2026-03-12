#include <iostream>
#include "toyvec.h"
#include <string>

using namespace std;
int main(){

    //trying to run this gives me undefined refrences...
    ToyVector<int> v;
    cout << "enter vector to run:" << endl;
    int num;
    while(cin >> num){
        if(num == -1){
            break;
        }
        v.push_back(num);
    }
    cout << v.erase_duplicates();
    return 0;
    
}