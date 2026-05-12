#include <string>
#include <iostream>
using namespace std;
class Shoe {
private:
   double size;
   string color;
   string type;
public:
  Shoe(double size, string color, string type)
    : size(size), color(color), type(type) {;}

    // Add an overload of operator<< that will allow Shoes to be written to an ostream
    // Add an overload of operator== 
    // Add a specialization of std::hash<Shoe> 
    // Write code to add a bunch of shoes to an std::unordered_set<Shoe>.  
    // Validate that the unordered_set identifies and eliminates duplicates correctly.

    bool operator==(const Shoe& n){
        return((size == n.size) && (color == n.color) && (type == n.type));
    }

    friend ostream& operator<<(ostream& os, const Shoe& n){
        os << n.size << " " << n.color << " " << n.type;
        return os; 
    }
};