#include <iostream>

using namespace std;
template <typename E>
class SNode{
    private:
    E elem;
    SNode<E>* next;

    friend class SLinkedList<E>;
};

template <typename E>
class SLinkedList{
    private:
    SNode<E>* head;
    public:
    

};



int main(){
    
    
    return 0;
}