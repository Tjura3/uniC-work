#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	vector<int> vectorInt(5);

	cout << "initial random even value:" << endl;
	for (vector<int>::iterator it = vectorInt.begin(); it != vectorInt.end(); ++it) {
		*it = rand() * 2;
		cout << *it << " ";
	}
	cout << endl;

	cout << "added random odd value " << endl;
	for (int i = 0; i < 5; ++i) {
		int v = rand() * 2 - 1;
		vectorInt.push_back(v);
		cout << v << " ";
	}
	cout << endl;

	sort(vectorInt.begin(), vectorInt.end());

	cout << "sorted vector" << endl;
	for (vector<int>::iterator it = vectorInt.begin(); it != vectorInt.end(); ++it) {
		cout << *it << " " << endl;
	}
	cout << endl;

	vector<int> increasedVec(vectorInt);
	for (vector<int>::iterator it = increasedVec.begin(); it != increasedVec.end(); ++it) {
		*it *= 2;
	}
	vector< vector<int> > vofvInt;
	vofvInt.push_back(increasedVec);

	cout << "vector of vector" << endl;
	for (vector< vector<int> >::iterator it = vofvInt.begin(); it != vofvInt.end(); ++it) {
		for (vector< int >::iterator itInternal = it->begin(); itInternal != it->end(); ++itInternal) {
			cout << *itInternal << " " << endl;
		}
	}

	return 0;
}