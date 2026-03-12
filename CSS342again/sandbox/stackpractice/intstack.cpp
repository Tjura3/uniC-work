#include <iostream>
#include <list>

//using namespace std;
//We dont need a constructor, the complier generated constructor is good and no initialization is needed either.
//because this is a wrapper class, this does not directly manage any resources (no raw pointers an no new / delete). it deletages ownership to std list
//OOOOOhhh ok I see now, and ADT is the type.
//stack == LIFO
class StackList {
    private:
    std::list<int> data_;

public:
    void push(int x){
        data_.push_back(x);
    }
    void pop(){
        if(empty()){
            throw std::underflow_error("Stack is empty");
        }
        data_.pop_back();
    }
    int top() const{
        if(empty()){
            throw std::underflow_error("Stack is empty");
        }
        return data_.back();
    }
    bool empty() const{
        return data_.empty();
    }
};
class CharList {
    private:
    std::list<char> data_;

public:
    void push(char x){
        data_.push_back(x);
    }
    void pop(){
        if(empty()){
            throw std::underflow_error("Stack is empty");
        }
        data_.pop_back();
    }
    char top() const{
        if(empty()){
            throw std::underflow_error("Stack is empty");
        }
        return data_.back();
    }
    bool empty() const{
        return data_.empty();
    }
};

class Queue{
    private:
    std::list<int> data;
    public:
    void enqueue(int x){
        data.push_back(x);
    }
};

bool validParens(const std::string& input){
    CharList list;
    for(char c : input){
        if(c == '{' || c == '(' || c == '['){
            list.push(c);
        }
        if(c == '}'){
            if(list.top() != '{') return false;
            list.pop();
        }else if(c == ')'){
            if(list.top() != '(') return false;
            list.pop();
        }else if(c == ']'){
            if(list.top() != '[') return false;
            list.pop();
        }
    }
    if(list.empty()){
        return true;
    }else return false;
}


int main() {

    
    return 0;
}
