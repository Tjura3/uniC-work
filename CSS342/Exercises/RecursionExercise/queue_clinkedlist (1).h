#include <iostream>
#include "clinkedlist.h"

#ifndef _LINKEDQUEUE_H_
#define _LINKEDQUEUE_H_

using namespace std;
using namespace clinkedlist;

namespace lqueue {

    template <typename T>
    class LinkedQueue{
        private:
            CircleList<T> C;
            int n;
        
        public:
            LinkedQueue();
            ~LinkedQueue();
            int size() const;
            bool empty() const;
            const T& front() const; //throw (QueueEmpty);
            void enqueue(const T& e);
            void dequeue(); // throw (QueueEmpty);
            void printQueue() const;

    };


    template <typename T>
    LinkedQueue<T>::LinkedQueue(): C(), n(0) {}

    template <typename T>
    LinkedQueue<T>::~LinkedQueue(){}

    template <typename T>
    int LinkedQueue<T>::size() const{
        return n;
    }

    template <typename T>
    bool LinkedQueue<T>::empty() const{
        return n == 0;
    }

    template <typename T>
    const T& LinkedQueue<T>::front() const{
        if (empty()){
            cerr << "Front of the queue empty error" << endl;
        } //throw QueueEmpty("front of the queue empty");
        return C.front();
    }

    template <typename T>
    void LinkedQueue<T>::enqueue(const T& e){
        C.add(e);
        C.advance();
        n++;
    }

    template <typename T>
    void LinkedQueue<T>::dequeue(){
        if (empty()){
            cerr << "Front of the queue empty error" << endl;
        }
        C.remove();
        n--;
    }    

    template <typename T>
    void LinkedQueue<T>::printQueue() const{
        if (!empty()){
            C.printList();
        }        
    }


} // end of namespace linkedqueue

#endif