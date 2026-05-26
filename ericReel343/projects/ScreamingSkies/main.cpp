#include <iostream>
#include <vector>
#include <string>
#include <random>

using namespace std;

// ==========================================
// Rng
// ==========================================

class Rng {
private:
    std::mt19937 gen;

public:
    inline Rng(int seed) : gen(seed) {}
    inline Rng() : gen(std::random_device{}()) {}

    inline int randint(int low, int high) {
        std::uniform_int_distribution<> dist(low, high);
        return dist(gen);
    }
};

class Fruit {
public:
    virtual ~Fruit() = default;
    virtual string getName() = 0;
    virtual string getAttackMessage() = 0;
    virtual int getAttackDamage() = 0;
    virtual string takeDamage(int amount) = 0;
    virtual bool isLiving() = 0;
};

// ==========================================
// Fruit monsters
// ==========================================
class FlyingAvocado : public Fruit {
private:
    int hp = 30;
public:
    string getName() override { return "Flying Avocado"; }
    string getAttackMessage() override { return "launches it's pit at your chest!"; }
    int getAttackDamage() override { return 12; }
    string takeDamage(int amount) override {
        hp -= amount;
        if (hp <= 0) return "The Avocado splits open, spilling all over the wasteland!";
        return "Your strike gashes its leathery skin, but it stays airborne!";
    }
    bool isLiving() override { return hp > 0; }
};

class ShriekingStrawberry : public Fruit {
private:
    int hp = 15;
public:
    string getName() override { return "Shrieking Strawberry"; }
    string getAttackMessage() override { return "fires a barrage of razor-sharp outer seeds!"; }
    int getAttackDamage() override { return 6; }
    string takeDamage(int amount) override {
        hp -= amount;
        if (hp <= 0) return "The Strawberry bursts as jam flies everywhere!";
        return "The Strawberry shrieks piercingly as its juices leak!";
    }
    bool isLiving() override { return hp > 0; }
};

class VampireWatermelon : public Fruit {
private:
    int hp = 60;
public:
    string getName() override { return "Vampire Watermelon"; }
    string getAttackMessage() override { return "swoops down, attempting to drain your fluids with its serrated rind!"; }
    int getAttackDamage() override { return 25; }
    string takeDamage(int amount) override {
        hp -= amount;
        if (hp <= 0) return "The massive Watermelon shatters into a hundred chunks!";
        return "The thick rind absorbs most of the impact, echoing a hollow thud!";
    }
    bool isLiving() override { return hp > 0; }
};

// ==========================================
// Fruit Factory 
// ==========================================
class FruitFactory {
private:
    Rng& rng;
    typedef Fruit* (*SpawnFunction)();
    vector<pair<int, SpawnFunction>> fruitVector;
    int totalWeight = 0;

    // Pass as function pointers
    static Fruit* createAvocado() { return new FlyingAvocado(); }
    static Fruit* createStrawberry() { return new ShriekingStrawberry(); }
    static Fruit* createWatermelon() { return new VampireWatermelon(); }

public:
    FruitFactory(Rng& engine) : rng(engine) {
        // Strawberry 50%, Avocado 35%, Watermelon 15%
        fruitVector.push_back({50, &createStrawberry});
        fruitVector.push_back({35, &createAvocado});
        fruitVector.push_back({15, &createWatermelon});
        // Total weight in case I want to add more later.
        for (const pair<int, SpawnFunction>& item : fruitVector) {
            totalWeight += item.first;
        }
    }

    Fruit* spawn() {
        int roll = rng.randint(0, totalWeight - 1);
        int accumulatedWeight = 0;

        
        for (const pair<int, SpawnFunction>& item : fruitVector) {
            accumulatedWeight += item.first;
            
            if (accumulatedWeight > roll) {
                // Invoke the function pointer
                return item.second(); 
            }
        }
        return fruitVector.back().second(); 
    }
};

// ==========================================
// Validation
// ==========================================
void factoryProportionTest() {
    cout << "--- STARTING FACTORY PROPORTION TEST ---\n";
    Rng testRng(42); 
    FruitFactory factory(testRng);

    int strawberryCount = 0;
    int avocadoCount = 0;
    int watermelonCount = 0;
    const int TEST_RUNS = 1000000;

    for (int i = 0; i < TEST_RUNS; ++i) {
        Fruit* f = factory.spawn();
        if (f->getName() == "Shrieking Strawberry") strawberryCount++;
        else if (f->getName() == "Flying Avocado") avocadoCount++;
        else if (f->getName() == "Vampire Watermelon") watermelonCount++;
        delete f; 
    }

    cout << "Target Ratio:  Strawberry: 50% | Avocado: 35% | Watermelon: 15%\n";
    cout << "Actual Results over " << TEST_RUNS << " spawns:\n";
    cout << " - Strawberries: " << strawberryCount << " (" << (strawberryCount * 100.0 / TEST_RUNS) << "%)\n";
    cout << " - Avocados:    " << avocadoCount << " (" << (avocadoCount * 100.0 / TEST_RUNS) << "%)\n";
    cout << " - Watermelons: " << watermelonCount << " (" << (watermelonCount * 100.0 / TEST_RUNS) << "%)\n";
    cout << "---------------------------------------\n\n";
}

// ==========================================
// Game
// ==========================================
void playGame(){
    Rng gameRng; 
    FruitFactory factory(gameRng);

    int playerHp = 100;
    int daysSurvived = 0;

    cout << "Welcome to the Produce Wasteland. Protect your vitals.\n";
    cout << "========================================================\n\n";

    while (playerHp > 0) {
        daysSurvived++;
        cout << "=== Day " << daysSurvived << " in the Wasteland ===\n";
        
        // Spawn fruiet
        Fruit* enemy = factory.spawn();
        cout << "A wild " << enemy->getName() << " drops from the radioactive clouds!\n";

        // Loop battle till death do part
        while (enemy->isLiving() && playerHp > 0) {
            // Player attacks first
            int playerDamage = gameRng.randint(10, 25);
            cout << " -> You strike with your machete for " << playerDamage << " damage.\n";
            cout << "    " << enemy->takeDamage(playerDamage) << "\n";

            // If it survived, it strikes back
            if (enemy->isLiving()) {
                int enemyDamage = enemy->getAttackDamage();
                playerHp -= enemyDamage;
                cout << " -> The " << enemy->getName() << " " << enemy->getAttackMessage() << "\n";
                cout << "    You take " << enemyDamage << " damage! (Your HP: " << (playerHp < 0 ? 0 : playerHp) << ")\n";
            }
            cout << "\n";
        }
        delete enemy; 

        if (playerHp > 0) {
            cout << "You managed to find a safe spot to sleep for the night.\n";
            // Small healing between rounds
            playerHp = min(100, playerHp + 15);
            cout << "Resting recovers 15 HP. Current Health: " << playerHp << "\n\n";
        }
    }

    cout << "========================================================\n";
    cout << "GAME OVER. Produce Got ya.\n";
    cout << "Survived for " << daysSurvived << " days.\n";
}

int main() {
    // Validate proportion
    factoryProportionTest();

    // Play the game
    playGame();
    
    
    return 0;
}