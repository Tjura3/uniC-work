// CDLList.cpp — template implementation for CDLList.
// #included at the bottom of CDLList.h. Do NOT compile it directly.
// Compilable skeleton: the constructor builds a valid empty circular list with a
// dummy header; the rest are stubs for you to implement.

//#include "CDLList.h" //why is this not in here and in the .h? //comment on compile.

template <class Object>
CDLList<Object>::CDLList() {
    header = new DLListNode<Object>;   // dummy header (its item is unused)
    header->next = header;             // empty list: header points to itself
    header->prev = header;             //points to the end of the list
}

template <class Object>
CDLList<Object>::CDLList(const CDLList& rhs) {
    header = new DLListNode<Object>;
    header->next = header;
    header->prev = header;
    // TODO: deep-copy every DATA node of rhs (in order) into this list.
    if(rhs.header->next == rhs.header) return;
    DLListNode<Object>* rcurr = rhs.header->next; //at this point, rhs is at the node after header
    DLListNode<Object>* curr = header; //curr is at header
    while(rcurr != rhs.header){
        curr->next = new DLListNode<Object>{rcurr->item, curr, header}; //item prev next
        rcurr = rcurr->next;  
        curr = curr->next;
        
    }
    header->prev = curr;
} 

template <class Object>
CDLList<Object>::~CDLList() {
    clear();          // clear() must delete every DATA node (implement it).
    delete header;    // then free the dummy header.
}

template <class Object>
const CDLList<Object>& CDLList<Object>::operator=(const CDLList& rhs) {
    // TODO: guard self-assignment; clear current data nodes; deep-copy rhs.
    if(&rhs == this) return *this;
    clear();
    if(rhs.header->next == rhs.header) return *this;
    DLListNode<Object>* rcurr = rhs.header->next; 
    DLListNode<Object>* curr = header;
    while(rcurr != rhs.header){
        curr->next = new DLListNode<Object>{rcurr->item, curr, header};
        rcurr = rcurr->next;  
        curr = curr->next;
        
    }
    header->prev = curr;
    return *this;
}

template <class Object>
bool CDLList<Object>::isEmpty() const {
    return header->next == header;
}

template <class Object>
int CDLList<Object>::size() const {
    // TODO: count data nodes (walk header->next until back at header).
    DLListNode<Object>* curr = header->next;
    int i = 0;
    while(curr != header){
        i++;
        curr = curr->next;
    }
    return i;
}

template <class Object>
void CDLList<Object>::clear() {
    // TODO: delete every data node; leave the header pointing to itself.
    DLListNode<Object>* curr = header->next;
    while(curr != header){
        DLListNode<Object>* next = curr->next;
        delete curr;
        curr = next;
    }
    header->next = header;
    header->prev = header; 
}

template <class Object>
void CDLList<Object>::insert(const Object& obj, int index) {
    // TODO: splice a new node into the doubly linked ring at the given index.
    //assuming 0 is the head
    
    //handling negative index
    // if(index < 0){
    //     int size = size();
    //     while(index < 0){
    //         index = index - size;
    //     }
    // }

    //and now the index should either be 0 or a positive number
    //0 inserts in header's next
    //I imagine header is skipped over?
    //like a list of 3 and I insert at 5, I am dealing with headder and lets say 1 2 and 3
    //it goes to 1, 2, 3, skip headder, 1, insert at 2?
    //stop overthinking, just use modulos to figure out the index.
    //after messing with them in sandbox, negative_index % size = negative number
    //so add size to find the real index, and modulo that whole thing to get it account for positive numbers

    int siz = size();
    //also if size is just at the head just make index 0 and I think that works?
    if(siz == 0){
        index = 0;
    }else if(index < 0 || index > siz){
        index = ((index % siz) + siz) % siz;
    }

    DLListNode<Object>* ins = new DLListNode<Object>{obj, nullptr, nullptr}; //item, prev, next
    DLListNode<Object>* temp = nullptr;
    if(index == siz){
        temp = header;
    }else{
        temp = header->next;
        while(index != 0){
            temp = temp->next;
            index--;
        }   
    }
    
    ins->next = temp;
    ins->prev = temp->prev;
    temp->prev->next = ins;
    temp->prev = ins;
}

template <class Object>
int CDLList<Object>::find(const Object& obj) const {
    // TODO: return the 0-based index of the first match, or -1.
    DLListNode<Object>* curr = header->next;
    int index = 0;
    while(curr != header){
        if(curr->item == obj) return index;
        index++;
        curr = curr->next;
    }
    //curr equals header
    return -1;
}
//check
template <class Object>
void CDLList<Object>::remove(const Object& obj) {
    // TODO: unlink (fix prev/next) and delete the first matching data node.
    DLListNode<Object>* curr = header->next;
    while(curr != header){
        if(curr->item == obj){
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
            delete curr;
            return;
        }     
        curr = curr->next;
    }
}

template <class Object>
Object CDLList<Object>::retrieve(int index) const {
    // TODO: return the item at index.
    //does this mean that 0 should return the head?
    //ill just say no and copy what I did with insert.
    //aaand I way overengineered this... cause we could assume valid indexes.
    
    int siz = size();
    if (siz == 0) return Object{};
    index = ((index % siz) + siz) % siz; //if index is 0, its still 0.
    DLListNode<Object>* curr = header->next; 
    while(index != 0){
        curr = curr->next;
        index--;
    }
    return curr->item;
}
