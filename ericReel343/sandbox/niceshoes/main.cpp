//Thomas Juranich Nice Shoes
#include <string>
#include <iostream>
#include <unordered_set>
#include <functional>
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
    friend ostream& operator<<(ostream& os, const Shoe& n){
        os << n.size << " " << n.color << " " << n.type;
        return os; 
    }
    
    // Add an overload of operator== 
    bool operator==(const Shoe& n) const{
        return ((size == n.size) && (color == n.color) && (type == n.type));
    }

    // Add a specialization of std::hash<Shoe> 
    friend struct hash<Shoe>;
    
};

namespace std {
    template <>
    struct hash<Shoe> {
        size_t operator()(const Shoe& s) const {
            size_t h1 = hash<double>{}(s.size);
            size_t h2 = hash<string>{}(s.color);
            size_t h3 = hash<string>{}(s.type);
            return h1 ^ (h2 << 1) ^ (h3 << 2);
        }
    };
}

int main(){
    // Write code to add a bunch of shoes to an std::unordered_set<Shoe>.  
    // Validate that the unordered_set identifies and eliminates duplicates correctly.
    unordered_set<Shoe> shoeset;

    
    Shoe s1(10.5, "Red", "Sneaker");
    Shoe s2(9.0, "Black", "Boot");
    Shoe s3(10.5, "Red", "Sneaker"); //Dupe
    Shoe s4(11.5, "Green", "Sneaker");
    Shoe s5(11.5, "Green", "Sneaker");

    shoeset.insert(s1);
    shoeset.insert(s2);
    shoeset.insert(s3);
    shoeset.insert(s4);
    shoeset.insert(s5); 

    cout << "Inserted 5 Shoes" << endl;
    cout << "Total shoes: " << shoeset.size() << endl;
    cout << "_______________Shoes in set_______________" << endl;
    for (const auto& shoe : shoeset) {
        cout << shoe << endl;
    }

    if (shoeset.size() == 3) {
        cout << "\nSuccess, Dupes eliminated.\n" << endl;
    } else {
        cout << "\nFailure, Duplicate found in set.\n" << endl;
    }

    return 0;
}