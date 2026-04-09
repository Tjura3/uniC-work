#include <iostream>
#include <string>
#include <cstdint>
#include <map>
using namespace std;

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