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







/*
//PQ exercise, also starting to murk the includes as well
#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <stdexcept>
using namespace std;
//priority queue exercise
//Nieve implementation
template <typename T>
class MyPriorityQueue{
    private:
    vector<T> data;
    public:
    void enqueue(T item){
        //ok what...? this is the in class work...
        data.push_back(item);
    }
    T dequeue(){
        //if(data.size() == 0) throw exception;
        if(data.size() == 0){
            throw new runtime_error("Queue is empty.");
        }
        int idxMax = 0;
        for(int i = 0; i < data.size(); i++){
            if(data[i] > data[idxMax]){
                idxMax = i;
            }
        }
        T ret = data[idxMax];
        data[idxMax] = data.back();//data[data.size()-1];
        data.pop_back();
        return ret;
    }
    int size(){
        return data.size();
    }
};

int main(void){
    MyPriorityQueue<int> q;
    q.enqueue(7);
    q.enqueue(9);
    q.enqueue(8);
    q.enqueue(1);
    while(q.size() != 0){
        cout << q.dequeue() << endl;
    }
}
*/

/*
//Bit of fun exercise
class BitWriter {
private:
    vector<uint8_t> data;
    uint8_t currentByte = 0; //REMEMBER BYTE = WHOLE THING BIT = SINGLE BIT
    int bitCount = 0;
    size_t totalBits = 0;

public:
    void write(bool bitValue) {
        //Ok so doing = breaks stuff and delets stuff so |= lets us keep the byte.
        if (bitValue) currentByte |= (1 << (7 - bitCount));
        bitCount++;
        totalBits++;
        //push to vector when 8
        if (bitCount == 8) {
            data.push_back(currentByte);
            currentByte = 0;
            bitCount = 0;
        }
    }
    size_t getData(vector<uint8_t>& out) {
        out = data;
        if (bitCount > 0) {
            out.push_back(currentByte);
        }
        return totalBits;
    }
};

string toHexString(vector<uint8_t> bytes, const string& delim = "") {
    //I forgot you could do a char an array this way.
    string out = "";
    const char* hexArray = "0123456789ABCDEF";

    for (size_t i = 0; i < bytes.size(); ++i) {
        //Nibble first 4
        out += hexArray[(bytes[i] >> 4) & 0x0F];
        //Nibble last 4
        out += hexArray[bytes[i] & 0x0F];

        if (!delim.empty() && i < bytes.size() - 1) {
            out += delim;
        }
    }
    return out;
}

int main() {
    //I love lambdas
    auto report = [&](bool* testBits, int size, string expected) {
        BitWriter bitWrite;
        for(int i = 0; i < size; i++){
            bitWrite.write(testBits[i]);
        }
        vector<uint8_t> resultVector;
        bitWrite.getData(resultVector);
        string result = toHexString(resultVector, "-");
        cout << "Expected: " << expected << "\nResult:   " << result << endl;
    };

    bool bits1[] = {1,0,1,0,1,0,1,0,1,0,1,0};
    report(bits1, 12, "AA-A0");

    bool bits2[] = {0,1,0,0,1,0,1,1};
    report(bits2, 8, "4B");

    
    // //Ok now here is an interesting bug, I accidently did bits2, and 16,
    // //But whats cool is that it was adding the garbage data from bits1 to the mix to output 4B-AA
    // //An
    // bool bits3[] = {1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1};
    // report(bits2, 16, "FF-F3");
    

    bool bits3[] = {1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1};
    report(bits3, 16, "FF-F3");

    bool bits4[] = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,1,1,1,1};
    report(bits4, 25, "80-00-F7-80");

    return 0;
}
*/


/* //terminate uint32
namespace reason{
    const uint32_t ITS_NOT_YOU_ITS_ME = 1;              // 1 << 0; //"It's not you no no, its me, its all me. "
    const uint32_t I_NEED_TO_FOCUS_ON_MYSELF = 2;       // 1 << 1; //"I need to focus on myself, I haven't had any time to even THINK properly. "
    const uint32_t THIS_IS_BETTER_FOR_EVERYONE = 4;     // 1 << 2; //"It must be hard to admit, but this is better for everyone. "
    const uint32_t I_DONT_DESERVE_YOU_NEVER_HAVE = 8;   // 1 << 3; //"From the moment I have laied my eyes upon you, I have never been worhty of your very presence. "
    const uint32_t ESCORT_OUT_IMMEDIATE = 16;           // 1 << 4; //"I need to leave, the feds are after me after what I did in the horse factory. "
    const uint32_t ZAP_WITH_LAZER = 32;                 // 1 << 5; //"From the moment I have laied my eyes upon your flesh, it disgusted me. ( ╥﹏╥) ノシ ︻デ═一 *ZWAAAAaAAAaAAAAaAAAAAaAAAAAAAAAaAAAaAAA*"
}

void terminate(string name, uint32_t flags){
    cout << name << "... I'm sorry, its just not working out. ";
    if(flags & reason::ITS_NOT_YOU_ITS_ME){
        cout << "It's not you no no, its me, its all me. ";
    }
    if(flags & reason::I_NEED_TO_FOCUS_ON_MYSELF){
        cout << "I need to focus on myself, I haven't had any time to even THINK properly. ";
    }
    if(flags & reason::THIS_IS_BETTER_FOR_EVERYONE){
        cout << "It must be hard to admit, but this is better for everyone. ";
    }
    if(flags & reason::I_DONT_DESERVE_YOU_NEVER_HAVE){
        cout << "From the moment I have laied my eyes upon you, I have never been worhty of your very presence. ";
    }
    if(flags & reason::ESCORT_OUT_IMMEDIATE){
        cout << "I need to leave, the feds are after me after what I did in the horse factory. ";
    }
    if(flags & reason::ZAP_WITH_LAZER){
        cout << "From the moment I have laied my eyes upon your flesh, it disgusted me. ( ╥﹏╥) ノシ ︻デ═一 *ZWAAAAaAAAaAAAAaAAAAAaAAAAAAAAAaAAAaAAA*";
    }
    cout << endl;
}


int main(){
    cout << "Breaking up with daniel" << endl;
    terminate("Daniel", 11);
    cout << endl;

    //test
    cout << "Breaking up with JoJo" << endl;
    terminate("JoJo", (32+4+1));
    cout << endl;
    
    //hitting Connor with the kitchen sink
    cout << "Breaking up with connor my beloved wife and husband ;-;" << endl; //I don't know if im gonna get docked points for this
    terminate("Connor", 63);
    cout << endl;

    return 0;
}
*/










/*
namespace Flavors{
    const uint32_t VANILLA = 1;     // 1 << 0;
    const uint32_t CHOCOLATE = 2;   // 1 << 1;
    const uint32_t CHILI = 4;       // 1 << 2;
    //custom flag?
    const uint32_t BORING = VANILLA | CHOCOLATE; // 3 aka 0b011

}
int countBits(uint32_t flavors){
    int count = 0;
    while (flavors > 0){
        count += flavors & 1;
        flavors >>= 1;
    }
    return count;
}

float orderIceCream(uint32_t flavors){
    float cost = 0;
    std::map<uint32_t, std::string> messages = {{Flavors::BORING, "yawn\n"},{Flavors::CHILI, "Now you is talking!\n"}};
    if(flavors & Flavors::VANILLA){
        cout << "yawn\n";
        cost += 1.75;
    }
    if(flavors & Flavors::CHOCOLATE){
        cout << "Really?\n";
        cost += 1.75;
    }
    if(flavors & Flavors::CHILI){
        cout << "Now you is talking!\n";
        cost += 1.75;
    } else { 
        cout << "I feel very sorry for you.\n";
    }
    return cost;
    
}

int main(){
    uint8_t val = 8;
    uint32_t myOrder = Flavors::CHILI | Flavors::CHOCOLATE;
    float cost = orderIceCream(myOrder);
    cout << "That will be " << cost << " sirmaddam \n";
    return 0;
}
*/








// class Node{
//     public:
//     string value;
//     Node* left;
//     Node* right;
//     Node(string val): value(val), left(nullptr), right(nullptr) {}
// };
// void printHeightTree(Node* root, int height = 0){
//     if(root == nullptr){
//         return;
//     }
    
//     printHeightTree(root->left, height+1);
//     cout << "[Node = " << root->value << "|Height = "<< height << "]" << endl;
//     printHeightTree(root->right, height+1);
// }

// int main(){
    
//     Node* root = new Node("A");
//     Node* leftc = new Node("B");
//     Node* rightc = new Node("C");
//     Node* leftg = new Node("D");

//     root -> left = leftc;
//     root -> right = rightc;
//     leftc -> left = leftg;

//     printHeightTree(root);
//     delete root;
//     delete leftc;
//     delete rightc;
//     delete leftg;
//     return 0;
// }