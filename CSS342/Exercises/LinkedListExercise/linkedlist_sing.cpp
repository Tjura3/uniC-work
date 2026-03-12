//professor work
#include <iostream>
using namespace std;
class StringNode {
    private:
        string elem;
        StringNode* next;
    public:
        StringNode();
        ~StringNode();

        StringNode* getNext() const;
    
        friend class StringLinkedList;

};
class StringLinkedList{
    private:
        StringNode* head;
    public:
        StringLinkedList();
        ~StringLinkedList();
        bool empty() const;
        const string& front() const;
        void addFront(const string& e);
        void removeFront();
        void printList() const;
        void addBack(const string& e);
        void removeBack();
        void addAt(StringNode* n, const string& e);
        void remove(StringNode* n);

        StringNode* getHead() const;
};



StringNode::StringNode(){    
}

StringNode::~StringNode(){    
}

StringNode* StringNode::getNext() const{
    return this->next;
}

StringLinkedList::StringLinkedList(){
    this->head = NULL;
}

StringLinkedList::~StringLinkedList(){
    while (!empty()){
        removeFront();
    }
}

bool StringLinkedList::empty() const{
    return this->head == NULL;
}

const string& StringLinkedList::front() const{
    return this->head->elem;
}

void StringLinkedList::addFront(const string& e){
    StringNode* newNode = new StringNode();
    newNode->elem = e;
    newNode->next = this->head;
    this->head = newNode;
}

void StringLinkedList::removeFront(){
    StringNode* oldHead = this->head;
    this->head = oldHead->next;
    delete oldHead;
}

void StringLinkedList::printList() const{
    StringNode* tmp;
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

void StringLinkedList::addBack(const string& e){
    StringNode* newNode = new StringNode();
    newNode->elem = e;
    newNode->next = NULL;
    
    StringNode* tmp;
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

void StringLinkedList::removeBack(){
    StringNode* tmp;
    StringNode* prev;

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

void StringLinkedList::addAt(StringNode* n, const string& e){    

    if (empty()){
        // addFront(e);
        addBack(e);
    }
    else{
        if (n->next != NULL){
            StringNode* newNode = new StringNode();
            newNode->elem = e;
            newNode->next = n->next;
            n->next = newNode;
        }
        else{
            addBack(e);
        }
    }
}

void StringLinkedList::remove(StringNode* n){
    StringNode* tmp;
    StringNode* prev;

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

StringNode* StringLinkedList::getHead() const{
    return this->head;
}


int main(){
    StringLinkedList myList = StringLinkedList();

    string e = "bazinga";
    while (e != "quit"){        
        cout << "Enter a new item : ";
        cin >> e;
        if (e == "quit"){
            break;
        }
        // myList.addFront(e);
        myList.addBack(e);
    }

    myList.printList();
    // myList.removeFront();
    // myList.printList();
    // myList.removeBack();
    // myList.printList();

    myList.addAt(myList.getHead(), "H");
    myList.printList();

    // myList.addAt(myList.getHead()->getNext()->getNext()->getNext(), "H->next->next->next");
    myList.addAt(myList.getHead()->getNext(), "H->next");
    myList.printList();

    return 0;
}