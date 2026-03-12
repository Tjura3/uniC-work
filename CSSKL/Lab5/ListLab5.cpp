#include <iostream>
#include <list>
using namespace std;

//returns true if odd
bool evenodd(const int& value) {return (value%2)==1;} 

int main() {
	list<int> intL;
	for (int i = 0; i < 5; ++i) {
		intL.push_back(i*2 + 1);
	}

	for (int i = 1; i < 6; ++i) {
		intL.push_back(i * 2);
	}

	cout << "First in list: " << intL.front() << endl;
	cout << "last in list: " << intL.back() << endl;

	intL.remove(3);
	intL.sort();

	cout << "sorted:" << endl;
	for (list<int>::iterator it = intL.begin(); it != intL.end(); ++it) {
		cout << *it << " ";
	}
	cout << endl;
	intL.remove_if(evenodd);
    
	cout << "List post odd-number removal" << endl;
	for (list<int>::iterator it = intL.begin();
	it != intL.end();
	++it) {
		cout << *it << " ";
	}
	cout << endl;

	return 0;
}