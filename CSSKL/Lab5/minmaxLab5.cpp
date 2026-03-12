//create a c++ program to print the min and max values of the primitive types
//int, unsigned int, long, double and float

#include <iostream>
#include <limits>
using namespace std;
int main(){
    cout << "Integer max and min" << endl;
    cout << numeric_limits<int>::max() << endl;
    cout << numeric_limits<int>::min() << endl;
    cout<<endl;

    cout << "Unsigned int max and min" << endl;
    cout << numeric_limits<unsigned>::max() << endl;
    cout << numeric_limits<unsigned>::min() << endl;
    cout << endl;

    cout << "Long max and min" << endl;
    cout << numeric_limits<long>::max() << endl;
    cout << numeric_limits<long>::min() << endl;
    cout << endl;

    cout << "Double max and min" << endl;
    cout << numeric_limits<double>::max() << endl;
    cout << numeric_limits<double>::min() << endl;
    cout << endl;

    cout << "Float max and min" << endl;
    cout << numeric_limits<float>::max() << endl;
    cout << numeric_limits<float>::min() << endl;
    cout << endl;

    cout << "boolean max and min" << endl;
    cout << numeric_limits<bool>::max() << endl;
    cout << numeric_limits<bool>::min() << endl;
    cout << endl;


}