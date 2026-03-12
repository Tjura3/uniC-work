#include <iostream>
#include "stack.h"
using namespace std;
using namespace linkedstack;
/*
bool ParenMatch(const char* X, int n){
    LinkedStack<char> S;
    for(int i = 0; i < n; i++){
        if(X[i] == '(' || X[i] == '[' || X[i] == '{'){
            S.push(X[i]);
        }
        else if (X[i] == ')'){
            if(S.empty()){
                return false; //matches with nothing
            }
            if(S.top() != '('){
                return false; //wrong type
            }
            S.pop();
        }
        else if (X[i] == ']'){
            if(S.empty()){
                return false; //matches with nothing
            }
            if(S.top() != '['){
                return false; //wrong type
            }
            S.pop();
        }
        else if (X[i] == '}'){
            if(S.empty()){
                return false; //matches with nothing
            }
            if(S.top() != '{'){
                return false; //wrong type
            }
            S.pop();
        }
        
    }

    if(S.empty()) return true; //symbols all matched
    else return false; //leftover symbols
}
*/

bool ParenMatch(const char* X, int n){
    LinkedStack<char> S;
    for(int i = 0; i < n; i++){
        if(X[i] == '(' || X[i] == '[' || X[i] == '{'){
            S.push(X[i]);
        }
        if(X[i] == ')' || X[i] == ']' || X[i] == '}'){
            if (X[i] == ')' && S.top() != '(') return false; //wrong type
            if (X[i] == ']' && S.top() != '[') return false; //wrong type
            if (X[i] == '}' && S.top() != '{') return false; //wrong type
            if(S.empty()) return false; //matches with nothing
            S.pop();
        }
    }
    if(S.empty()) return true; //symbols all matched
    else return false; //leftover symbols
}

int main(){
    string input;
    cout << "Enter an expression : ";
    cin >> input;
    const char* charstring = input.c_str();
    if(ParenMatch(charstring, input.size())){
        cout << "Matched" << endl;
    } else cout << "Did not match" << endl;
    

    return 0;
}