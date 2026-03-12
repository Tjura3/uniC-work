#include <iostream>

using namespace std;

class StringNode{
    private:
    string elem;
    StringNode* next;

    friend class StringLinkedList;
};

class StringLinkedList{  //decided to put the methods in the class this time because I find it harder to read when it is outside the class blocks
    private:
    StringNode* head;

    string printNext(StringNode* s){ //I do wonder why this prints in reverse order ofc
        if(s == NULL) return "";
        return s->elem + " " + printNext(s->next);
        //return  printNext(s->next)+ " " + s->elem ; //this actually prints it in the correct order.
    }
    public:
    StringLinkedList() : head(NULL) {} //what exactly does this do? why is there a colon here? is head(NULL) supposed to set head to null?
    ~StringLinkedList(){
        while (!empty()) removeFront();
    }
    bool empty(){ return head == NULL;}
    const string& front() const{ //why is the const keyword after the method name? why is const called twice?
        return head->elem;
    }
    void removeFront(){
        StringNode* old = head;
        head = old->next;
        delete old; //delete calls the deconstructor for the stringnode?
    }
    void addFront(const string& e){ //& is a refrence to a string and not an address
        StringNode* v = new StringNode;
        v->elem = e;
        v->next = head;
        head = v;
    }

    string printlist(){
        return printNext(head);
    }
};

int main(){
    StringLinkedList list = StringLinkedList();
    //StringLinkedList* list = new StringLinkedList();
    list.addFront("James");
    list.addFront("Charles");
    list.addFront("Alexanderia");
    cout << list.printlist() << endl;
    return 0;
}