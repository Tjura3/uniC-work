#include <iostream>
using namespace std;
int main(){
    cout << -5 % 3 << endl;
    cout << 3 % -5 << endl;
    cout << 5 % -3 << endl;
    cout << -3 % 5 << endl;
    cout << ((5 % 3) + 3) % 3 << endl;
    cout << ((-5 % 3) + 3) % 3 << endl;
    cout << ((5 % 3) + 3) << endl;
    cout << ((-5 % 3) + 3) << endl;
    cout << "eval zero\n";
    cout << ((0 % 3) + 3) % 3 << endl;
    cout << ((0 % 1526) + 1526) % 1526 << endl;
    
    return 0;
}