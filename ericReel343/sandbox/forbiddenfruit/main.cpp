#include <iostream>
#include <string>
#include <vector>
using namespace std;
/**
 * Virtual creates a method made at compile time.
 */
class Fruit{
    public:
    //void eatMe(){ cout << "yum!\n";}
    virtual void eatMe(){ cout << "yum!\n";}
};

class Ripe : public Fruit{
    void eatMe(){ cout << "BIG YUM!\n";}
};

class Mold : public Fruit{
    void eatMe(){ cout << "YUCK!\n";}
};

int main(){
    vector<Fruit*> vec {new Ripe(), new Mold()};
    for(Fruit* ptr : vec){
        ptr -> eatMe();
    }
    for(auto& ptr : vec){
        delete ptr;
    }
    vec.clear();
    return 0;
}