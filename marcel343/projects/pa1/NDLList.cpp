// NDLList.cpp — template implementation for NDLList.
// This file is #included at the bottom of NDLList.h. Do NOT compile it directly.
// Compilable skeleton: every method has a stub so the project builds. Replace the
// TODOs with real implementations. (Stubs intentionally leak / return defaults.)

template <class Object>
NDLList<Object>::NDLList() : head(nullptr) {}

template <class Object>
NDLList<Object>::NDLList(const NDLList& rhs) : head(nullptr) {
    // TODO: deep-copy every node of rhs into this list.
}

template <class Object>
NDLList<Object>::~NDLList() {
    clear();   // clear() must delete every node (implement it).
}

template <class Object>
const NDLList<Object>& NDLList<Object>::operator=(const NDLList& rhs) {
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
    int size = 0;
    LListNode<Object>* curr = head;
    while(curr != nullptr){
        size++;
        curr = curr->next;
    }
    return size;
}

template <class Object>
void NDLList<Object>::clear() {
    LListNode<Object>* curr = head;
    while(curr != nullptr){
        LListNode<Object>* next = curr -> next;
        delete curr;
        curr->next = nullptr;
        curr = next;
    }
    head = nullptr;
}

template <class Object>
void NDLList<Object>::insert(const Object& obj, int index) {
    if(index < 0) return;
    
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
    return -1;
}

template <class Object>
void NDLList<Object>::remove(const Object& obj) {
    // TODO: unlink and delete the first node whose item == obj.
}

template <class Object>
Object NDLList<Object>::retrieve(int index) const {
    // TODO: return the item at index (you may assume a valid index).
    return Object{};
}
