#include <iostream>
#include <queue>
#include <string>
#include <random>
#include <iomanip>
using namespace std;

class SalesLead {
public:
  string name;
  int income;
  int insertionNumber;
  SalesLead(string n, int i, int ins) : name(n), income(i), insertionNumber(ins) {}
};
class InquiryComparator{
    public:
    bool operator()(const SalesLead& first, const SalesLead& second) {
        if (first.income == second.income) { 
            return first.insertionNumber > second.insertionNumber; 
        }
        else { 
            return first.income < second.income; //if B is first, it goes on top, or above it
        }
    }
};
int main(){
    priority_queue<SalesLead, vector<SalesLead>, InquiryComparator> leadQueue;
    int lineNumber = 0;
    auto qPush = [&](string name, int income){
        leadQueue.push(SalesLead(name, income, lineNumber++));
    };
    
    qPush("Average Joe Schmoe", 50000);
    qPush("Kaching the spender", 150000);
    qPush("Late Tycoon", 150000);
    qPush("Window Shopper", 30000);

    while(!leadQueue.empty()){
        SalesLead curr = leadQueue.top();
        cout << curr.name << " " << curr.income << " " << curr.insertionNumber << endl;
        leadQueue.pop(); 
    }

    //This just makes a ton of "Alvins" to properly test income and number
    cout << "\nLimit test\n";
    lineNumber = 0;
    srand(static_cast<unsigned int>(time(nullptr)));
    string a = "alvin ";
    for(int i = 0; i < 50; i++){
        qPush(a+to_string(lineNumber), rand() % 10 + 1);
    }
    cout << left << setw(20) << "NAME" << setw(15) << "INCOME" << setw(10) << "NUMBER" << endl;
    cout << string(40, '-') << endl;
    while(!leadQueue.empty()){
        SalesLead curr = leadQueue.top();
        cout << left << setw(20) <<curr.name << setw(15)<< curr.income << setw(10) << curr.insertionNumber << endl;
        leadQueue.pop(); 
    }
    return 0;
}