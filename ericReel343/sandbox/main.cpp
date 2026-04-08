#include <iostream>
#include <string>
#include <cstdint>
#include <map>
using namespace std;

namespace reason{
    const uint32_t ITS_NOT_YOU_ITS_ME = 1;              // 1 << 0;
    const uint32_t I_NEED_TO_FOCUS_ON_MYSELF = 2;       // 1 << 1;
    const uint32_t THIS_IS_BETTER_FOR_EVERYONE = 4;     // 1 << 2;
    const uint32_t I_DONT_DESERVE_YOU_NEVER_HAVE = 8;   // 1 << 3;
    const uint32_t ESCORT_OUT_IMMEDIATE = 16;           // 1 << 4;
    const uint32_t ZAP_WITH_LAZER = 32;                 // 1 << 5;
}

void terminate(){
    
}




int main(){
    return 0;
}











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