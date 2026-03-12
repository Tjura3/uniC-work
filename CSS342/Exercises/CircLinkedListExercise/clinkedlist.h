#include <iostream>

#ifndef _CLINKEDLIST_H_
#define _CLINKEDLIST_H_

using namespace std;

namespace clinkedlist {

    template <typename T>
    class CircleList {

        public: 
            template <typename U>
            class CNode{
                    private:
                        U elem; 
                        CNode<U>* next;
                    public:
                        CNode(){
                        };
                        ~CNode(){
                        };

                        CNode<U>* getNext() const{
                            return this->next;
                        };

                        U getElement() const{
                            return this->elem;
                        };
                    
                        friend class CircleList<U>;
                };

        private:
                CNode<T>* cursor;

        public:
                CircleList();
                ~CircleList();
                bool empty() const;
                const T& front() const;
                const T& back() const;
                void advance();
                void add(const T& e);
                void remove();
                void printList() const;

    };


    template <typename T>
    CircleList<T>::CircleList(){
        this->cursor = NULL;
    }

    template <typename T>
    CircleList<T>::~CircleList(){
        while (!empty()){
            remove();
        }
    }

    template <typename T>
    bool CircleList<T>::empty() const{
        return this->cursor == NULL;
    }

    template <typename T>
    const T& CircleList<T>::front() const{
        return this->cursor->next->elem;
    }

    template <typename T>
    const T& CircleList<T>::back() const{
        return this->cursor->elem;
    }

    template <typename T>
    void CircleList<T>::advance(){
        this->cursor = this->cursor->next;
    }


    template <typename T>
    void CircleList<T>::add(const T& e){
        CNode<T>* v = new CNode<T>();
        v->elem = e;
        
        if (this->cursor == NULL){
            v->next = v;
            this->cursor = v;
        }
        else {
            v->next = this->cursor->next;
            this->cursor->next = v;
        }
    }

    template <typename T>
    void CircleList<T>::remove(){
        CNode<T>* old = this->cursor->next;
        
        if (old == this->cursor){
            this->cursor = NULL;
        }
        else {
            this->cursor->next = old->next;
            delete old;
        }
    }

    template <typename T>
    void CircleList<T>::printList() const{
        CNode<T>* tmp = this->cursor->next; // node at front
        
        if (!empty()){
            while (tmp != cursor){
                cout << tmp->elem << " ";
                tmp = tmp->next;
            }
            cout << tmp->elem << " "; // last node: cursor, back
        }
    }

} // end of namespace clinkedlist

#endif