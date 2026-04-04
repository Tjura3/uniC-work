#include <iostream>
#include <initializer_list>
#pragma once
using namespace std;
template <typename T>
class CircularLinkedList {
    private:
    struct Node(){
        T data;
        Node* next;
        Node(T value) : data(val), next(nullptr){}
    };
    Node* curr;
    int size;

    public:
    CircularLinkedList() : curr(nullptr), size(0) {}
    CircularLinkedList(initializer_list<T> inilist) : curr(nullptr), size(0){
        
    }
    
    
};