#include <iostream>
#include <list>

using namespace std;

bool is_odd(const int& value) {return (value % 2) == 1; }

int main() {
	list<int> intList;
	for (int i = 0; i < 5; ++i) {
		intList.push_back(i*2 + 1);
	}

	for (int i = 1; i < 6; ++i) {
		intList.push_back(i * 2);
	}

	cout << "first " << intList.front() << endl;
	cout << "end " << intList.back() << endl;

	intList.remove(3);
	
	intList.sort();

	cout << "sorted list" << endl;
	for (list<int>::iterator it = intList.begin(); it != intList.end(); ++it) {
		cout << *it << " ";
	}
	cout << endl;

	intList.remove_if(is_odd);

	cout << "after removing odd values" << endl;
	for (list<int>::iterator it = intList.begin(); it != intList.end(); ++it) {
		cout << *it << " ";
	}
	cout << endl;

	return 0;
}