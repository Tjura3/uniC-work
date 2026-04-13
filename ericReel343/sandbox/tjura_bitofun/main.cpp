#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
using namespace std;



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

    /*
    //Ok now here is an interesting bug, I accidently did bits2, and 16,
    //But whats cool is that it was adding the garbage data from bits1 to the mix to output 4B-AA
    //An
    bool bits3[] = {1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1};
    report(bits2, 16, "FF-F3");
    */

    bool bits3[] = {1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1};
    report(bits3, 16, "FF-F3");

    bool bits4[] = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,1,1,1,1};
    report(bits4, 25, "80-00-F7-80");

    return 0;
}