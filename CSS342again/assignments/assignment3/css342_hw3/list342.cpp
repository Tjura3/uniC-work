#include "list342.h"
#include <fstream>
//#include <iostream>
//using namespace std;
/**
 * overall I think I learned more how derefrencing works, mainly with the amount of debugging I had to do to figure out why some things wern't working,
 * Another thing, Insert broke at some point, so I rebuilt it, and tried to make optimizations using more logic in while loops and if statements,
 * One regret is using a for loop for the copy constructor and the copy constructor only? I can shift it to a while loop, but I thought at the time it
 * would be funny if I used for loops in the copy constructor only for some reason, that lead to a big debugging time where I realized insert was adding onto
 * size and causing segmentation faults.
 */
List342::List342() : head_(nullptr) , size_(0) {}
List342::List342(const List342& other){
    if(this == &other){
        head_ = nullptr;
        size_ = 0;
    }else{
        head_ = nullptr;
        size_ = 0;
        Node* curr = other.head_;
         
        for(int i = 0; i < other.size(); i++){ //breaks at 4 and 5
            //cout << insert(curr->data) << endl;
            insert(curr->data);
            curr = curr->next; 
        }
    }

}
List342::~List342(){
    clear();
}
void List342::clear(){
    size_ = 0;
    Node* curr = head_;
    while (curr != nullptr) {
        Node* next = curr->next;
        //curr->next = nullptr; 
        delete curr;
        //curr->next = nullptr; //was breaking becasue I didn't set curr -> next to nullptr.... Why did I do this.
        curr = next;
    }
    head_ = nullptr;
}

int List342::size() const{
    return size_;
}
/************************************************************************************************
 * END OF BIG 3 + GETTERS
 */
List342& List342::operator=(const List342 &other){
    if(this == &other){
        return *this;
    }
    clear();
    Node* curr = other.head_;
    //size_ =  
    for(int i = 0; i < other.size(); i++){
        insert(curr->data);
        curr = curr->next; 
    }
    return *this;
}
bool List342::buildList(const std::string &filename){
    clear(); //delete the current list that is storing data?\
    //open file
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        return false;
    }
    //this should work, it makes a temporary student, it inputs into that student,
    Student temp;
    while (infile >> temp) {
        insert(&temp);
    }
    infile.close();
    return true;
}

bool List342::isInList(const Student* obj){
    if(head_ == nullptr) return false;
    if(obj == nullptr) return false;
    Node* curr = head_;
    //int fun = 0;
    while(curr != nullptr){
        //cout << *(head_->data) << endl;
        //if(curr->data->first_name() == obj->first_name() && obj->last_name() == curr->data->last_name() && obj->age() == curr->data->age()){
        if(*(curr->data) == *obj){ //swapped it after becoming more confident in derefrencing pointers
            return true;
        }
        if (*obj < *(curr->data)) {
            return false; 
        }
        curr = curr->next;
    }
    return false;
}
/*
//I dont even know anymore what I was trying to do here, I just rewrote it with some aid.
bool List342::insert(const Student* obj){
    //cout << "inserted: " << *(obj) << endl; 
    if(obj == nullptr) return false;
    if(isInList(obj)) return false;
    Node* new_node = new Node(new Student(obj->first_name(), obj->last_name(), obj->age()));
    if(head_ == nullptr){
        head_ = new_node;
        size_++;
        return true;
    }
    if(new_node->data < head_->data){
        new_node->next = head_;
        head_ = new_node;
        size_++;
        return true;
    }
    if(head_->next == nullptr){ //guarentees 2 elements in the list
        head_->next = new_node;
        size_++;
        return true;
    }
    //two poiners, one where its comparing the value, the previous being the one that has to point to the new node.
    Node* curr = head_->next;
    Node* prev = head_;
    while(true){
        if(curr == nullptr){
            break;
        }
        if(new_node->data > curr->data){
            curr = curr->next;
            prev = prev->next;
        }else break;
    }
    //now at this point, curr is greater then newnode, or is null ptr, and previous is the node that comes right before the new node.
    new_node->next = curr;
    prev->next = new_node;
    size_++;
    return true;
}*/

bool List342::insert(const Student *obj) {
    //
    if (obj == nullptr) return false;
    if (isInList(obj)) return false;

    Node* new_node = new Node(new Student(*obj)); //derefrenceing here to use the copy constructor.
    
    //combining head check with 1 value check
    if (head_ == nullptr || *(new_node->data) < *(head_->data)) {
        new_node->next = head_;
        head_ = new_node;
    } else{
        Node* curr = head_;
        while (curr->next != nullptr && *(curr->next->data) < *(new_node->data)) {
            curr = curr->next;
        }
        new_node->next = curr->next;
        curr->next = new_node;
    }
    size_++;
    return true;
}


bool List342::remove(const Student &target, Student &result){
    if (head_ == nullptr) return false;
    Node* curr = head_;
    Node* previous = nullptr;
    while (curr != nullptr && *(curr->data) < target) { //derefrence to get the data
        previous = curr;
        curr = curr->next;
    }if (curr == nullptr || !(*(curr->data) == target)) {
        return false;
    }
    result = *(curr->data); // have to derefrene to find object.
    if (previous == nullptr) {
        //head check
        head_ = curr->next;
    } else {
        previous->next = curr->next;
    }
    delete curr;
    size_--;
    //cout << *(head_->data) << endl;
    return true;
    
}
bool List342::peek(const Student &target, Student &result) const{
    if (head_ == nullptr) return false;
    Node* curr = head_;
    while (curr != nullptr && *(curr->data) < target) {
        curr = curr->next;
    }
    if (curr == nullptr || !(*(curr->data) == target)) {
        return false; // Not found; result is NOT modified
    }
    result = *(curr->data);
    
    return true;
}
void List342::deleteList(){
    clear(); //I basically already did this above with clear, whoops.
}

bool List342::merge(List342 &other){
    if (this == &other) return true;
    if (other.head_ == nullptr) return true;
    if (this->head_ == nullptr) {
        this->head_ = other.head_;
        this->size_ = other.size_;
        other.head_ = nullptr;
        other.size_ = 0;
        return true;
    }

    
    Node helper(nullptr);
    Node* curr = &helper;
    Node* l1 = this->head_;
    Node* l2 = other.head_;

    while (l1 != nullptr && l2 != nullptr) {
        if (*(l1->data) < *(l2->data)) {
            curr->next = l1;
            l1 = l1->next;
            curr = curr->next;
        } 
        else if (*(l2->data) < *(l1->data)) {
            curr->next = l2;
            l2 = l2->next;
            curr = curr->next;
        } 
        else {
            //dupe: keep first list, delete seconed list
            curr->next = l1;
            l1 = l1->next;
            curr = curr->next;

            // Remove l2 dupe
            Node* temp = l2;
            l2 = l2->next;
            delete temp;
            other.size_--;
        }
    }

    // attach nodes together
    if (l1 != nullptr) {
        curr->next = l1;
    } else if (l2 != nullptr) {
        curr->next = l2;
    }

    this->head_ = helper.next;
    this->size_ += other.size_; 
    other.head_ = nullptr;
    other.size_ = 0;
    
    return true;
}

bool List342::operator==(const List342 &rhs) const{
    //size check
    if (this->size_ != rhs.size_) {
        return false;
    }
    //nullptr check
    if (this->head_ == nullptr && rhs.head_ == nullptr) {
        return true;
    }
    Node* left = this->head_;
    Node* right = rhs.head_;

    while (left != nullptr && right != nullptr) {
        if (!(*(left->data) == *(right->data))) {
            return false; 
        }
        left = left->next;
        right = right->next;
    }
    return true;
}
bool List342::operator!=(const List342& rhs) const{
    return !(*this == rhs);
}
std::ostream& operator<<(std::ostream& os, const List342& list) {
    Node* curr = list.head_;
    bool first = true;

    while (curr != nullptr) {
        if (!first) {
            os << " ";
        }
        if (curr->data != nullptr) {
            os << *(curr->data);
        }
        
        first = false;
        curr = curr->next;
    }

    return os;
}