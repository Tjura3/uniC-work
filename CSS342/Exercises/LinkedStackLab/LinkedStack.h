#include <iostream>
#include "slinkedlist.h"
using namespace std;
using namespace slinkedlist;



namespace linkedstack{ //gives you a way to organize things and group things together
    typedef string Elem;
    class LinkedStack
    {
    public:
        LinkedStack();
        int size() const;
        bool empty() const;
        const Elem &top() const; //throw(StackEmpty);
        void push(const Elem &e);
        void pop(); //throw(StackEmpty);
        void print();
        void reverse();

    private:
        LinkedList<Elem> S;
        int n;
    };

    LinkedStack::LinkedStack() : S(), n(0) {}

    int LinkedStack::size() const
    {
        return n;
    }

    bool LinkedStack::empty() const
    {
        return n == 0;
    }

    const Elem& LinkedStack::top() const //throw(StackEmpty)
    {
        //if (empty()) return;//throw StackEmpty("Top of empty stack");
        return S.front();
    }

    void LinkedStack::push(const Elem &e)
    {
        ++n;
        S.addFront(e);
    }

    void LinkedStack::pop() //throw(StackEmpty)
    {
        //if (empty()) return;//throw StackEmpty("Pop from empty stack");
        --n;
        S.removeFront();
    }

    void LinkedStack::print(){
        S.printList();
    }

    void reverse(){
        
    }


}

