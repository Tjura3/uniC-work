#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

//A polynomial rolling hash
unsigned int Hash(const string& str) {
    unsigned int hash = 0;
    unsigned int prime = 31;
    for (char c : str) {
        hash = hash * prime + c;
    }
    return hash;
}

int main() {
    const string filename = "yob2024.txt";
    const int numberbuckets = 16;
    vector<int> buckets(numberbuckets, 0);
    int total = 0;

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "file failed to open " << filename << endl;
        cerr << "make sure text file is in same folder" << endl;
        return 1;
    }

    //for every element we are throwing in the bucket, increment.
    string sLine;
    while (getline(file, sLine)) {
        stringstream ss(sLine);
        string name;
        if (getline(ss, name, ',')) {
            unsigned int hashValue = Hash(name);
            int bucketIndex = hashValue % numberbuckets;
            buckets[bucketIndex]++;
            total++;
        }
    }
    file.close();

    
    cout << "___BUCKETS___" << endl;
    for (int i = 0; i < numberbuckets; ++i) {
        cout << "Bucket " << i << ": " << buckets[i] << " names" << endl;
    }
    cout << "Total names: " << total << "\n" << endl;

    
    double expected = static_cast<double>(total) / numberbuckets;
    double chiSquare = 0.0;

    for (int i = 0; i < numberbuckets; ++i) {
        double difference = buckets[i] - expected;
        chiSquare += (difference * difference) / expected;
    }

    //Aparently its measured by k-1 so I use 15 I think
    const double critical = 24.996;

    cout << "Names per bucket expected: " << expected << endl;
    cout << "Chi-square statistic: " << chiSquare << endl;
    cout << "Critical: " << critical << endl;

    if (chiSquare > critical) {
        cout << "Distribution uneven due to being over Chi-Square critical." << endl;
        cout << "We reject the null hypothesis of uniform distribution." << endl;
    } else {
        cout << "Chi-Square below critical value." << endl;
        cout << "We fail to reject the null hypothesis." << endl;
    }

    return 0;
}
