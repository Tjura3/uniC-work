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
    CircularLinkedList(initializer_list<T> inlist) : curr(nullptr), size(0){
        for (const auto& listval : inlist) {
            add(listval);
        }
    }
    void add(T val){
        Node* newnode = new Node(val);
        if(curr == nullptr){
            curr = newnode;
            newnode->next = curr;
        }else{
            Node* temp = curr;
            while(temp->next != curr){
                temp = temp->next;

            }
            temp->next = newnode;
            newnode->next = curr;
        }
        size++;
    }
    
    
    
};