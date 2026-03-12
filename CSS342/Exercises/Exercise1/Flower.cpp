#include <iostream>

using namespace std;

class Flower
{

private:
    std::string name;
    int petals;
    float price;
public:
    
    Flower();
    Flower(string x, int y, float z);
    Flower(const Flower&);
    //~Flower(); doesnt need to be here because its data is on the stack and not the heap.

    string getName(){
        return name;
    }
    int getPetals(){
        return petals;
    }
    float getPrice(){
        return price;
    }
};
Flower::Flower(){
    name = "NONE";
    petals = 0;
    price = 0.0f;
}
Flower::Flower(string x, int y, float z) //the constructor for the class, you can also put this inside of the constructor itself    
{
    name = x;
    petals = y;
    price = z;
}

Flower::~Flower() //the deconstructor for the class
{
    //you only need to delete things if your class puts things in the heap
}

int main(){
    cout << "Hello world!" << endl;
    return 0;
}
