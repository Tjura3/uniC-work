#include <iostream>
using namespace std;
enum MealType {NO_PREF, REGULAR, LOW_FAT, VEGETARIAN};
class Passenger { // Passenger (as a class)
private:
string name; // passenger name
MealType mealPref; // meal preference
bool isFreqFlyer; // is a frequent flyer?
string freqFlyerNo; // frequent flyer number
public:
Passenger(); // constructor
Passenger(string, MealType, bool, string); // constructor
//accessor functions: getters/setters
bool isFrequentFlyer() const; // is this a frequent flyer?
// make this a frequent flyer
void makeFrequentFlyer(const string& newFreqFlyerNo);
void setName(const string& newName);
string getName() const;
// . . . other member functions
};
Passenger::Passenger(){
}
Passenger::Passenger(string passName, MealType mPref, bool isFreq, string
freqFlyNum){
name = passName;
mealPref = mPref;
isFreqFlyer = isFreq;
freqFlyerNo = freqFlyNum;
}
bool Passenger::isFrequentFlyer() const {
return isFreqFlyer;
}
void Passenger::setName(const string& newName){
name = newName;
}
string Passenger::getName() const {
return name;
}
void Passenger::makeFrequentFlyer(const string& newFreqFlyerNo) {
isFreqFlyer = true;
freqFlyerNo = newFreqFlyerNo;
}
int main(){
Passenger pass;
if ( !pass.isFrequentFlyer() ) { // not already a frequent flyer?
pass.makeFrequentFlyer("392953"); // set pass’s freq flyer number
}
// pass.name = "Michael Jordan";
pass.setName("Larry Bird");
// How to print passenger details on the screen?
// Passenger name : Johnny White
// Meal preference : ...
// If frequent flyer, print
// Frequent flyer number :
// Exercise
// Implement all accessor functions you think will be necessary and
return EXIT_SUCCESS;
}
