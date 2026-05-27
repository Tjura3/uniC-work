#include <iostream>
#include <string>
#include <fstream>
#include <regex>
using namespace std;
void findJo(string filename){
    //Regex: (jo.*),F,(\d*)
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open the file." << endl;
        exit(1);
    }
    regex pattern(R"(jo.*),F,(\d*)");
    smatch matches;
    string line;
    int unames = 0;
    int unumber = 0;
    while(getline(file, line)){
        if(regex_search(line, matches, pattern)){
            string name = matches[0].str();
            string scount = matches[1].str();
            int count = stoi(scount);
            cout << name << ", " << count << endl;
            unames++;
            unumber += count;
        }
    }
    cout << "Number of unique names: " << unames << endl;
    cout << "Number of total children: " << unumber << endl;
    file.close();
}

int main(){
    
    string testFileName = "test.txt";
    ofstream testFile(testFileName);
    if (testFile.is_open()) {
        testFile << "Jordan,M,500\n";    // N
        testFile << "Jolie,F,150\n";     // Y
        testFile << "Jo,F,10\n";         // Y
        testFile << "John,M,200\n";      // N
        testFile << "Joanna,F,85\n";     // Y
        testFile << "Amelia,F,300\n";    // N
        testFile.close();
    }
    findJo(testFileName);
    findJo("yob2024.txt");
    return 0;
}