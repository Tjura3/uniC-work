#include "rng.h"
#include <string>
using namespace std;
class Fruit {
public:
    virtual string getName() = 0;               // returns name of fruit, ex: Avocado
    virtual string getAttackMessage() = 0;      // returns message used when attacking
    virtual int getAttackDamage() = 0;          // returns amount of damage inflicted by attack
    virtual string takeDamage(int amount) = 0;  // returns reaction message 
    virtual bool isLiving() = 0;                // true if living, false otherwise
};

class FruitFactory {
public:
    FruitFactory(Rng& rng);
    Fruit* spawn() {
        // todo;
    }
};

int main(){
    return 0;
}