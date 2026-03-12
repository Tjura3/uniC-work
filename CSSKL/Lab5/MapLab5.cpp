#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
	map<string, int> SImap;
	SImap.insert(pair<string, int>("key 1", 1));
	SImap.insert(pair<string, int>("key 2", 2));
	SImap.insert(pair<string, int>("key 3", 3));
	SImap.insert(pair<string, int>("key 4", 4));
	SImap.insert(pair<string, int>("key 5", 5));


	for (map<string, int>::iterator it = SImap.begin();
		it != SImap.end();
		++it) {
		cout << "(" << it->first << ") = " << it->second << endl;
	}

	auto ret = SImap.insert(pair<string, int>("key 1", 11));
	cout << (ret.second ? ret.first->first: "invalid") << endl; //invalid because 
	cout << ret.second << endl;

	ret = SImap.insert(pair<string, int>("key 6", 6));
	cout << (ret.second ? ret.first->first : "invalid") << endl;
	cout << ret.second << endl;

	SImap["key 1"] = 111;
	SImap["key 7"] = 7;

	for (map<string, int>::iterator it = SImap.begin();
	it != SImap.end();
		++it
		) {
		cout << "(" << it->first << ") = " << it->second << endl;
	}

	return 0;
}
