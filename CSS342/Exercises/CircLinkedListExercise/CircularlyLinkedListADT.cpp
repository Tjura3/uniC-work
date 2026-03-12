//ADT = abstract data type
#include <iostream>
#include <string>
using namespace std;

typedef string Elem;
class CNode{
    private:
    Elem elem;
    CNode* next;
    friend class CircleList;
};

class CircleList{
    public:
    CircleList(); //empty cursor, needs to add elements into it
    CircleList(const Elem& e){
        cursor->elem = e;
        cursor->next = cursor;
    }
    ~CircleList(){
        while(!empty()) remove();
    }
    bool empty() const{
        return cursor == NULL;
    }
    const Elem& front() const{
        return cursor->elem;
    }
    const Elem& back() const{
        return cursor->next->elem;
    }
    void advance(){
        cursor = cursor->next;
    }

    void add(const Elem& e){
        CNode* temp = new CNode();
        temp->elem = e;

        if(cursor == nullptr){
           cursor = temp;
           cursor->next = cursor;
        }else{
            temp->next = cursor->next;
            cursor->next = temp;
        }
    }

    void remove(){
        if(cursor == nullptr){
            return;
        }
        else if(cursor->next == cursor){
            delete cursor;
            cursor = nullptr;
        }else{
            CNode* temp = cursor->next;
            cursor->next = cursor->next->next;

            delete temp;
            temp = nullptr;
        }
    }

    private:
    CNode* cursor;
};


int main(){
    CircleList circ;
    circ.add("one");
    circ.add("two");
    circ.add("three");
    cout << circ.front() << endl;
    cout << circ.back() << endl;
    circ.remove();
    cout << "post removal" << endl;
    cout << circ.front() << endl << circ.back() << endl;
}