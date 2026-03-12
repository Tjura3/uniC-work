#include <iostream>
#include "clinkedlist.h"

#ifndef _LINKEDQUEUE_H_
#define _LINKEDQUEUE_H_

using namespace std;
using namespace clinkedlist;

namespace lqueue {
    
    template <typename T>
    class ArrayQueue{
        private:
            CircleList<T> C;
            int n;
        
        public:
            ArrayQueue();
            ~ArrayQueue();
            int size() const;
            bool empty() const;
            const T& front() const; //throw (QueueEmpty);
            void enqueue(const T& e);
            void dequeue(); // throw (QueueEmpty);
            void printQueue() const;

    };


    template <typename T>
    ArrayQueue<T>::ArrayQueue(): C(), n(0) {}

    template <typename T>
    ArrayQueue<T>::~ArrayQueue(){}

    template <typename T>
    int ArrayQueue<T>::size() const{
        return n;
    }

    template <typename T>
    bool ArrayQueue<T>::empty() const{
        return n == 0;
    }

    template <typename T>
    const T& ArrayQueue<T>::front() const{
        if (empty()){
            cerr << "Front of the queue empty error" << endl;
        } //throw QueueEmpty("front of the queue empty");
        return C.front();
    }

    template <typename T>
    void ArrayQueue<T>::enqueue(const T& e){
        C.add(e);
        C.advance();
        n++;
    }

    template <typename T>
    void ArrayQueue<T>::dequeue(){
        if (empty()){
            cerr << "Front of the queue empty error" << endl;
        }
        C.remove();
        n--;
    }    

    template <typename T>
    void ArrayQueue<T>::printQueue() const{
        if (!empty()){
            C.printList();
        }        
    }


} // end of namespace linkedqueue

#endif