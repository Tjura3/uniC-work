#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main() {
	vector<int> intvector(5);
    
    /*for(int num : intvector){
        intvector.at(num) = rand();
    }*/

    cout << "adding even numbers" << endl;
    for(vector<int>::iterator iterate = intvector.begin();
    iterate != intvector.end();
    iterate++){
        *iterate = rand() * 2; //the pointer iterate is pointing at = random int
        cout << *iterate << " ";
    }
    cout << endl;

    cout << "adding odd" << endl;
    for(int i = 0; i < 5; i++){ //cant use iterator from beginning so I have to use for loop
        int k = rand() * 2 - 1; //makes all even then subtracts for odd
        cout << k << " ";
        intvector.push_back(k);
    }
    cout << endl;

    sort(intvector.begin() , intvector.end()); //sorts
    cout << "Post sorted vector" << endl;
    for(auto iterate : intvector){  //auto can also be used where the compiler will figure out some things.
        cout << iterate << " ";
    }
    cout << endl;

    return 0;
}
