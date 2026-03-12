#include <iostream>
#include <string>
#include <stack>
using namespace std;

/*
PSUDOCODE

FUNCTION int evaluate int int char
switch case
    if operator, do expression  {has a case for every operator}
return expression awnser
END FUNCTION

FUNCTION int evaluate string&
create an int stack
get expression from user
    for each charachter in expression do
        if the char is a didget, add to stack
        else if expression,
            pop two didgets and preform operator using operator function that returns int
            Push int to stack
        else print invalid token and exit
if valid return stack pop
END FUNCTION

FUNCITON main
Get expression from user
try
    clear white space in expression
    call evaluate pass in expression
    print result of evaluate
catch
    invalid tokens, incorrect size of stack.
END FUNCTION
*/


int operation(int a, int b, char sign){
    switch(sign){
        case '+':
            return a+b;
        case '-':
            return a-b;
        case '*':
            return a*b;
        case '/':
            return a/b;
        default:
            return 0;
    }
}

int postFixEval(const string& expresion){
    
    stack<int> intstack;
    for(char c : expresion){
        if(isdigit(c)){
            intstack.push(c -'0');
        }else if(c == '+' || c == '-' || c == '*' || c == '/'){
            if(intstack.size() <= 1){ //errors if there is less then 2 in the stack.
                cout << "Invalid expression" << endl;
                throw 451;
            }
            
            int two = intstack.top();
            intstack.pop();
            int one = intstack.top();
            intstack.pop();
            //cout << one << " " << two << endl;
            int res = operation(one, two, c);
            intstack.push(res);
        }else throw 40;
    }
    int finalresult = intstack.top();
    intstack.pop();
    if(!intstack.empty()){
        throw 404;
    }
    return finalresult;

}

int main(){
    string input;
    cout << "Enter a Postfix expression." << endl;
    cin >> input;
    try{
        int result = postFixEval(input);
        cout << "awnser to \"" << input << "\" is: " << result << endl;
    }catch(int error){
        cout << "Invalid input for Postfix." << endl;
        if(error == 451){
            cout << "Too many operation signs." << endl;
        }else if(error == 40){
            cout << "Unexpected token was entered." << endl;
        }else{
            cout << "Numbers did not match operation ammount,\nor numbers were not single-didgit" << endl;
        }
    }
    
    return 0;
}