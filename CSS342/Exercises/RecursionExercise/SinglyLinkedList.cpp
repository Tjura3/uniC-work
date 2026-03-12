/* //Stbh ignore this script, its dumb.
template <typename T>

void LinkedList<T>::printList() const{
    Node<T>* tmp; //address of the value
    if(!empty()){
        tmp = this -> head;
        while(tmp!= NULL){
            cout << tmp->elem << " ";
            tmp = tmp -> next;
        }
        cout << endl;
    }
    else {
        //cout << "List empty";
        throw "Exception occured : List empty.";
    }
}

//make the above recursion in slinkedlist

*/