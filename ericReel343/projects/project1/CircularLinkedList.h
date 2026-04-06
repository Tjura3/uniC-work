#include <iostream>
#include <initializer_list>
#pragma once
using namespace std;
template <typename T>
class CircularLinkedList {
    //private and node struct
    private:
    struct Node{
        T data;
        Node* next;
        Node(T val) : data(val), next(nullptr){}
    };
    Node* curr; //for current
    int size_; //for some reason when it isn't an underscore, it conflicts with the name of the getter? 
    //Looked it up, C++ does weird stuff when variables and functions are the same, so this one will be snake case? I can't find any class documentation on canvas at this time so that's what it will be for now.

    public:
    CircularLinkedList() : curr(nullptr), size_(0) {}
    CircularLinkedList(const initializer_list<T>& inlist) : curr(nullptr), size_(0){
        for (const auto& listval : inlist){
            add(listval);
        }
    }
    ~CircularLinkedList(){
        while(size_ != 0){
            removeNext(1);
        }
    }

    int size() const{
        return size_;
    }

    T getCurrent() const{
        return curr->data;
    }

    void add(T val){
        Node* newNode = new Node(val);
        if(curr == nullptr){
            curr = newNode;
            newNode->next = curr;
        }else{
            Node* temp = curr;
            while(temp->next != curr){
                temp = temp->next;

            }
            temp->next = newNode;
            newNode->next = curr;
        }
        size_++;
    }
    T removeNext(int place){ 
        if(size_ == 0) return {};
        if(place < 0){
            cerr << "Error: Can't removeNext negative values. Updating input value to 0\n";
            place = 0;
        }

        T returnVal;
        //had a valgrind issue, not an issue moreso an error,
        if (size_ == 1) {
            returnVal = curr->data;
            delete curr;
            curr = nullptr;
        }
        else if(place == 0){
            Node* temp = curr;
            while(temp->next != curr){
                temp = temp->next;
            }
            //at this point temp is the node before curr so set its next to node after curr, then delete curr, and update curr.
            returnVal = curr->data;
            temp->next = curr->next;
            delete curr;
            curr = temp->next;
        }
        else{
            //specifically we want to stop at the point just before we do the thang
            //also we are directly editing curr now, since we are in the circle.
            for(int i = 1; i < place; i++){
                curr = curr->next;
            }
            Node* toDel = curr->next;
            returnVal = toDel->data;
            curr->next = toDel->next;
            delete toDel;
            curr = curr->next;
        }
        size_--;
        return returnVal;
    }

    void visualize() const {
        if (curr == nullptr) {
            cout << "List is empty.\n";
            return;
        }

        Node* temp = curr;
        cout << "[Curr: " << curr->data << "]\n";
        
        //rare do while appearance
        do {
            cout << "[" << temp->data << "]" << " -> ";
            temp = temp->next;
        } while (temp != curr);

        cout << "[curr]\n";
    }
    
};