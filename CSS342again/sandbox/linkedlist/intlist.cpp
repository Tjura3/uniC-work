#include <iostream>

struct Node{
    int data;
    Node* next; //pointer to next node
    Node(int val) : data(val), next(nullptr){}
};

using namespace std;

class LList {
private:
    Node* head_;
    int size_;

public:
    
    LList() : head_(nullptr), size_(0) {}
    LList(const LList& a) : head_(nullptr), size_(0){
        for(int i = 0; i < a.size()-1; i++){
            push_back(a.valueAt(i));
        }
    }
    int size() const{
        return size_;
    }
    Node* head() const{
        return head_;
    }

    //insert node at end of list
    void push_back(int val) {
        //Node* newNode = new Node{value, nullptr};
        Node* new_node = new Node(val);
        size_++;
        if (head_ == nullptr) {
            head_ = new_node;
            return;
        }
        Node* current = head_;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = new_node;
    }
    void push_front(int val){
        Node* new_node = new Node(val);
        size_++;
        if(head_ == nullptr){
            head_ = new_node;
            return;
        }
        new_node->next = head_;
        head_ = new_node;
    }

    //just displays the list
    void displayList() {
        Node* curr = head_;
        if (curr == nullptr) {
            cout << "List is empty" << endl;
            return;
        }
        while (curr != nullptr) {
            cout << "[" << curr->data << "]" << " -> ";
            curr = curr->next;
        }
        cout << "NULL" << endl;
    }

    int valueAt(int location) const{
        if(location >= size_){
            return -1;
        }
        Node* curr = head_;
        for(int i = 0; i < location; i++){
            curr = curr->next;
        }
        return curr->data; //why arrow instead of curr.data?
    }

    //delete first node
    void pop_front(){
        if(head_ == nullptr) return;
        size_--;
        Node* temp = head_;
        head_ = head_->next;
        delete temp;
    }
    //two edge cases for empty list and 1 element in list, otherwise itterates through the list and stops at the second to last, 
    void pop_back(){
        if (head_ == nullptr){
            return;
        }
        if(head_->next == nullptr){
            delete head_;
            head_ = nullptr;
            size_--;
            return;
        }
        Node* curr = head_;
        while(curr->next->next != nullptr){
            curr = curr->next;
        }
        delete curr->next;
        curr->next = nullptr;
        size_--;
    }
    void clear(){
        size_ = 0;
        Node* current = head_;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current->next = nullptr; //was breaking becasue I didn't set curr -> next to nullptr
            current = next;
        }
        head_ = nullptr;
    }


    
    LList operator=(const LList& other){
        if(this == &other){
            return *this;
        }
        //deletes list first
        clear();
        
        for(int i = 0; i < other.size(); i++){
            push_back(other.valueAt(i));
        }
        
        return *this;
    }
    
    LList returnReverse(){
        /**
         * Another way to do this is to create a prevous pointer listed as a nullpointer, and a current listed as head,
         * Node* prev = null
         * Node* curr = head
         * while(curr != nullptr){
         * node* temp = curr->next
         * curr->next = prev
         * prev = curr
         * curr = temp
         * }
         */
        Node* curr = head_;
        LList revlist;
        while(curr != nullptr){
            revlist.push_front(curr->data);
            cout << "pushed " << curr->data << endl;
            curr=curr->next;
        }
        return revlist;
    }
    void reversePointers(){
        Node* prev = nullptr;
        Node* curr = head_;
        while(curr != nullptr){
            Node* temp = curr->next;
            //cout << prev <<" " << curr << " "<< temp << endl;
            curr->next = prev;
            prev = curr;
            curr = temp;
        }
        head_ = prev;
    }
    
    /*
    LList merge(LList& other){
        if(this)
    }
    */
    void forceSetHead(Node* newhead){
        clear();
        head_ = newhead;
    }
    ~LList() {
        clear();
        //why dont I need to delete int size_?
    }

};

LList mergeTwoLists(LList L1, LList L2){
    Node* list1 = L1.head();
    Node* list2 = L2.head();
    if(list1 == nullptr) return L2;
    if(list2 == nullptr) return L1;
    Node* head = nullptr;
    Node* idx = nullptr;
    if (list1->data < list2->data) {
        head = list1;
        idx = list1;
        list1 = list1->next;
    }else{
        head = list2;
        idx = list2;
        list2 = list2->next;
    }
    while(list1 != nullptr && list2 != nullptr){
        if(list1->data < list2->data){
            idx->next = list1;
            list1 = list1->next;
        }else{
            idx->next = list2;
            list2 = list2->next;
        }
        idx = idx->next; 
    }
    if (list1 != nullptr) {
        idx->next = list1;
    }else{
        idx->next = list2;
    }

    LList newlist;
    Node* curr = head;
    while(curr != nullptr){
        newlist.push_back(curr->data);
        curr = curr->next;
    }
    return newlist;

}

int main() {

    LList list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    LList list2;
    for(int i = 0; i < 15; i++){
        list2.push_back(i*10);
    }
    /*
    list2.displayList();
    list2.push_front(7);
    list2.displayList();
    LList copy(list2);
    cout << "copied list" << endl;
    copy.displayList();
    //copy = list;
    list.displayList();
    copy = list;
    cout << list.valueAt(2) << endl;
    copy.displayList();

    cout << "reverse time" << endl;
    LList toreverse;
    for(int i = 1; i < 6; i++){
        toreverse.push_back(i);
    }
    toreverse.displayList();
    toreverse.reversePointers();
    toreverse.displayList();
    */
    list.displayList();
    list2.displayList();
    LList list3 = mergeTwoLists(list, list2); 
    list3.displayList();
    return 0;
}
