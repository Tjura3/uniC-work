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
    bool operator==(const Shoe& n){
        return ((size == n.size) && (color == n.color) && (type == n.type));
    }

    // Add a specialization of std::hash<Shoe> 
    // Write code to add a bunch of shoes to an std::unordered_set<Shoe>.  
    // Validate that the unordered_set identifies and eliminates duplicates correctly.
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
    unordered_set<Shoe> closet;

    // 2. Add shoes, including duplicates
    Shoe s1(10.5, "Red", "Sneaker");
    Shoe s2(9.0, "Black", "Boot");
    Shoe s3(10.5, "Red", "Sneaker"); // Exact duplicate of s1

    closet.insert(s1);
    closet.insert(s2);
    closet.insert(s3); // Should be ignored

    // 3. Validate results
    cout << "Total shoes in set: " << closet.size() << endl;
    cout << "Contents:" << endl;
    for (const auto& shoe : closet) {
        cout << shoe << endl;
    }

    if (closet.size() == 2) {
        cout << "\nValidation Success: Duplicates were correctly eliminated!" << endl;
    } else {
        cout << "\nValidation Failed: Duplicate found in set." << endl;
    }

    return 0;
}