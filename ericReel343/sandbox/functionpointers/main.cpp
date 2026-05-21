#include <iostream>
#include <string>
using namespace std;

void processUserInput(bool (*process)(string)) {
    string input;
    while (true) {
        cout << ">>> ";
        getline(cin, input);
        if (process(input)) {
            break;
        }
    }
}

bool whatIHeardYouSay(string input) { 
    cout << "what I heard you say is: " << input << "\n";  
    return input == "quit"; 
}

bool polight(string input) { 
    if (input.find("please quit") == 0) { 
        cout << "nicely said\n"; 
        return true; 
    }  
    cout << "I don't understand\n"; 
    return false; 
}

bool custserv(string input) { 
    if (input == "hangup") {
        return true;
    }
    cout << "I'm sorry. I didn't quite get that. Can you repeat it?\n"; 
    return false; 
}

int main() {
    
    cout << "whatIHeardYouSay ('quit' to exit)\n";
    processUserInput(whatIHeardYouSay);

    cout << "\npolight ('please quit' to exit)\n";
    processUserInput(polight);

    cout << "\n'custserv' (Type 'hangup' to exit)\n";
    processUserInput(custserv);

    cout << "\nLambda!!!! ('pull fire alarm' to exit)\n";
    processUserInput([](string input) -> bool {
        if (input == "pull fire alarm") {
            cout << "* and everyone escaped *\n";
            return true;
        }
        cout << "HURRY PEOPLE ARE BURNING HEELLLPPPPP\n";
        return false;
    });

    cout << "\nYou saved the day!\nA winner is you!!\n";
    return 0;
}