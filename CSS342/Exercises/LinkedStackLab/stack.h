//this is the professors use for LinkedStack
#include "slinkedlist.h"
// #include <exception>
#ifndef _LINKEDSTACK_H_
#define _LINKEDSTACK_H_
using namespace slinkedlist;
using namespace std;
namespace linkedstack
{
    // typedef string Elem;
    template <typename T>
    class LinkedStack
    {
    private:
        LinkedList<T> S; // linked list of elements
        int n;           // number of elements
    public:
        LinkedStack();         // constructor
        ~LinkedStack();        // constructor
        int size() const;      // number of items in the stack
        bool empty() const;    // is the stack empty?
        const T &top() const;  // throw(StackEmpty); // the top element
        void push(const T &e); // push element onto stack
        void pop();            // throw(StackEmpty); // pop the stack
    };
    template <typename T>
    LinkedStack<T>::LinkedStack()
        : S(), n(0) {}
    template <typename T>
    LinkedStack<T>::~LinkedStack()
    {
    }
    template <typename T>
    int LinkedStack<T>::size() const
    {
        return n;
    }
    template <typename T>
    bool LinkedStack<T>::empty() const
    {
        return n == 0;
    }
    template <typename T>
    const T &LinkedStack<T>::top() const
    { // throw(StackEmpty){
        if (empty())
        {
            cerr << "Top of empty stack" << endl;
        } // throw StackEmpty("Top of empty stack");
        return S.front();
    }
    template <typename T>
    void LinkedStack<T>::push(const T &e)
    {
        ++n;
        S.addFront(e);
    }
    template <typename T>
    void LinkedStack<T>::pop()
    { // throw(StackEmpty){
        if (empty())
        { // throw StackEmpty("Pop from empty stack");
            cerr << "Top of empty stack" << endl;
        }
        --n;
        S.removeFront();
    }
} // end of namespace linkedstack
#endif