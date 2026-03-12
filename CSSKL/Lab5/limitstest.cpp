#include <iostream>
#include <limits>

using namespace std;

int main() {
	cout << "max of int is " << numeric_limits<int>::max() << endl;
	cout << "min of int is " << numeric_limits<int>::min() << endl;

	cout << "max of unsigned int is " << numeric_limits<unsigned int>::max() << endl;
	cout << "min of unsigned int is " << numeric_limits<unsigned int>::min() << endl;

	cout << "max of long is " << numeric_limits<long>::max() << endl;
	cout << "min of long is " << numeric_limits<long>::min() << endl;

	cout << "max of double is " << numeric_limits<double>::max() << endl;
	cout << "min of double is " << numeric_limits<double>::min() << endl;

	cout << "max of float is " << numeric_limits<float>::max() << endl;
	cout << "min of float is " << numeric_limits<float>::min() << endl;

	return 0;
}