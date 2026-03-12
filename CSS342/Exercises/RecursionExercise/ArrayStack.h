#include <iostream>

#pragma once
using namespace std;

/* what is the use of namespace here?
namespace StackArray{
    template <typename E>
    class StackArray{
        private:
            E* S;
            int capacity;
            int t;
        public:            
            
    };
}
*/

template <typename E>
class Stack{
    public:
    int size() const;
    bool empty() const;
    const E& top() const throw(StackEmpty);
    void push(const E& e);
    void pop() throw(StackEmpty);
};

template <typename E>
class StackArray{
    private:
        E* S;
        int capacity;
        int t;
    public:            
    Algorithem size();
};