// "auto" variable declaration is only defined in C++11
//
// compile with: (to generate "map" as the executable)
//      g++ -std=c++11 -o map maptest.cpp
//
#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
	map<string, int> testmap;
	testmap.insert(pair<string, int>("key1", 1));
	testmap.insert(pair<string, int>("key2", 2));
	testmap.insert(pair<string, int>("key3", 3));
	testmap.insert(pair<string, int>("key4", 4));
	testmap.insert(pair<string, int>("key5", 5));

	for (map<string, int>::iterator it = testmap.begin();
		it != testmap.end();
		++it
		) {
		cout << "[\"" << it->first << "\"] = " << it->second << endl;
	}

	auto ret = testmap.insert(pair<string, int>("key1", 11));
	cout << (ret.second ? ret.first->first: "invalid insertion") << endl;
	cout << ret.second << endl;

	ret = testmap.insert(pair<string, int>("key6", 6));
	cout << (ret.second ? ret.first->first : "invalid insertion") << endl;
	cout << ret.second << endl;

	testmap["key1"] = 111;
	testmap["key7"] = 7;

	for (map<string, int>::iterator it = testmap.begin();
	it != testmap.end();
		++it
		) {
		cout << "[\"" << it->first << "\"] = " << it->second << endl;
	}

	return 0;
}
