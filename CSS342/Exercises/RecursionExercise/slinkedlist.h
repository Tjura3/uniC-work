//prof work
#include <iostream>
#ifndef _SLINKEDLIST_H_
#define _SLINKEDLIST_H_
using namespace std;
namespace slinkedlist{
    template <typename T>
    class LinkedList{
        public:
            template <typename U>
            class Node{
                private:
                    U elem; 
                    Node<U>* next;
                public:
                    Node(){
                    };
                    ~Node(){
                    };

                    Node<U>* getNext() const{
                        return this->next;
                    };
                
                    friend class LinkedList<U>;
            };
        private:
            Node<T>* head;
        public:            
            LinkedList();
            ~LinkedList();
            bool empty() const;
            const T& front() const;
            void addFront(const T& e);
            void removeFront();
            void printList() const;
            void printList(Node<T>* tmp) const;
            void printListReverse(Node<T>* tmp) const;
            void addBack(const T& e);
            void removeBack();
            void addAt(Node<T>* n, const T& e);
            void remove(Node<T>* n);

            Node<T>* getHead() const{
                return this->head;
            }
            void setHead(Node<T>* newHead){
                this->head = newHead;
            }
    };    


    template <typename T>
    LinkedList<T>::LinkedList(){
        this->head = NULL;
    }

    template <typename T>
    LinkedList<T>::~LinkedList(){
        while (!empty()){
            removeFront();
        }
    }

    template <typename T>
    bool LinkedList<T>::empty() const{
        return this->head == NULL;
    }

    template <typename T>
    const T& LinkedList<T>::front() const{
        return this->head->elem;
    }

    template <typename T>
    void LinkedList<T>::addFront(const T& e){
        Node<T>* newNode = new Node<T>();
        newNode->elem = e;
        newNode->next = this->head;
        this->head = newNode;
    }

    template <typename T>
    void LinkedList<T>::removeFront(){
        Node<T>* oldHead = this->head;
        this->head = oldHead->next;
        delete oldHead;
    }

    template <typename T>
    void LinkedList<T>::printList() const{
        Node<T>* tmp;
        if (!empty()){
            tmp = this->head;
            while (tmp != NULL){
                cout << tmp->elem << " ";
                tmp = tmp->next;
            }
            cout << endl;
        }
        else {
            // cout << "List empty";
            throw "Exception occured : List empty.";
        }
    }
    template <typename T>
    void LinkedList<T>::printList(Node<T>* tmp) const{
        if (tmp == NULL){
            return;
        }
        cout << tmp->elem << " ";
        printList(tmp->next);
    }

    template <typename T>
    void LinkedList<T>::printListReverse(Node<T>* tmp) const{
        if (tmp == NULL){
            return;
        }        
        printListReverse(tmp->next);
        cout << tmp->elem << " ";
    }
    template <typename T>
    void LinkedList<T>::addBack(const T& e){
        Node<T>* newNode = new Node<T>();
        newNode->elem = e;
        newNode->next = NULL;
        
        Node<T>* tmp;
        if (!empty()){
            tmp = this->head;
            while (tmp->next != NULL){
                tmp = tmp->next;
            }        
            tmp->next = newNode; 
        }
        else {
            addFront(e);
        }
    }
    template <typename T>
    void LinkedList<T>::removeBack(){
        Node<T>* tmp;
        Node<T>* prev;

        if (!empty()){
            tmp = this->head;
            while (tmp->next != NULL){
                prev = tmp;
                tmp = tmp->next;
            }        
            delete tmp;
            prev->next = NULL;
        }
    }
    template <typename T>
    void LinkedList<T>::addAt(Node<T>* n, const T& e){    
        if (empty()){
            // addFront(e);
            addBack(e);
        }
        else{
            if (n->next != NULL){
                Node<T>* newNode = new Node<T>();
                newNode->elem = e;
                newNode->next = n->next;
                n->next = newNode;
            }
            else{
                addBack(e);
            }
        }
    }
    template <typename T>
    void LinkedList<T>::remove(Node<T>* n){
        Node<T>* tmp;
        Node<T>* prev;

        if (!empty()){
            tmp = this->head;
            while(tmp != n){
                prev = tmp;
                tmp = tmp->next;
            }

            prev->next = tmp->next;

            delete tmp;
        }
    }

} // namespace slinkedlist

#endif