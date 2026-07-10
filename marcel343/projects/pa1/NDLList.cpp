// NDLList.cpp — template implementation for NDLList.
// This file is #included at the bottom of NDLList.h. Do NOT compile it directly.
// Compilable skeleton: every method has a stub so the project builds. Replace the
// TODOs with real implementations. (Stubs intentionally leak / return defaults.)
//#include "NDLList.h" //comment on compile
template <class Object>
NDLList<Object>::NDLList() : head(nullptr) {}

template <class Object>
NDLList<Object>::NDLList(const NDLList& rhs) : head(nullptr) {
    if(rhs.head == nullptr) return;
    head = new LListNode<Object>{rhs.head->item, nullptr};

    LListNode<Object>* rcurr = rhs.head->next;
    LListNode<Object>* curr = head;
    while(rcurr != nullptr){
        curr->next = new LListNode<Object>{rcurr->item, nullptr};
        rcurr = rcurr->next;
        curr = curr->next;
    }
}

template <class Object>
NDLList<Object>::~NDLList() {
    clear();   // clear() must delete every node (implement it).
}

template <class Object>
const NDLList<Object>& NDLList<Object>::operator=(const NDLList& rhs) {
    if(&rhs == this) return *this;
    clear();
    if(rhs.head == nullptr) return *this;
    head = new LListNode<Object>{rhs.head->item, nullptr};

    LListNode<Object>* rcurr = rhs.head->next;
    LListNode<Object>* curr = head;
    while(rcurr != nullptr){
        curr->next = new LListNode<Object>{rcurr->item, nullptr};
        rcurr = rcurr->next;
        curr = curr->next;
    }
    // TODO: guard self-assignment; free current nodes; deep-copy rhs.
    return *this;
}

template <class Object>
bool NDLList<Object>::isEmpty() const {
    return head == nullptr;
}

template <class Object>
int NDLList<Object>::size() const {
    // TODO: count the nodes.
    //assuming 1 = 1 node
    int siz = 0;
    LListNode<Object>* curr = head;
    while(curr != nullptr){
        siz++;
        curr = curr->next;
    }
    return siz;
}

template <class Object>
void NDLList<Object>::clear() {
    LListNode<Object>* curr = head;
    while(curr != nullptr){
        LListNode<Object>* next = curr->next;
        //curr->next = nullptr;
        delete curr; //remember when deleting, all associated values get deleted.
        curr = next;
    }
    head = nullptr;
}

template <class Object>
void NDLList<Object>::insert(const Object& obj, int index) {
    if(index < 0 || index > size()) return;
    
    LListNode<Object>* ins = new LListNode<Object>{obj, nullptr};
    
    if(index == 0 || head == nullptr){//insert at head
        ins->next = head;
        head = ins;
        return;
    }
    LListNode<Object>* curr = head;
    for (int i = 0; i < index - 1 && curr->next != nullptr; i++) {
        curr = curr->next;
    }   
    ins->next = curr->next;
    curr->next = ins;
    // TODO: index 0 inserts at the head; otherwise after (index-1) nodes.
    //Hopefully this logic is correct.
}

template <class Object>
int NDLList<Object>::find(const Object& obj) const {
    // TODO: return the 0-based index of the first match, or -1.
    int index = 0;
    LListNode<Object>* curr = head;
    while(curr != nullptr){
        if(curr->item == obj) return index;
        index++;
        curr = curr->next;
    }
    return -1;
}

template <class Object>
void NDLList<Object>::remove(const Object& obj) {
    // TODO: unlink and delete the first node whose item == obj.
    //if(obj == nullptr) return;
    if(head == nullptr) return; 
    if(head->item == obj){
        LListNode<Object>* temp = head->next;
        delete head;
        head = temp;
        return;
    }
    LListNode<Object>* curr = head;
    while(curr->next != nullptr){
        if(curr->next->item == obj){
            LListNode<Object>* temp = curr->next->next;
            delete curr->next;
            curr->next = temp;
            return;
        }
        curr = curr->next;
    }
}

template <class Object>
Object NDLList<Object>::retrieve(int index) const {
    // TODO: return the item at index (you may assume a valid index).
    //yeaaahhhh part 3 says we have to add handling for that, so idk, Im not sure.
    if(head == nullptr) return Object{};
    
    LListNode<Object>* curr = head;
    for(int i = 0; i < index && curr != nullptr; i++){
        curr = curr->next;
    }
    if(curr == nullptr) return Object{};
    return curr->item;
}
