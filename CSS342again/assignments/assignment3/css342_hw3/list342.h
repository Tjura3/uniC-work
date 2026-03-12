#ifndef LIST342_H
#define LIST342_H
#include "student.h"
/**
 * Each node owns exactly one Student*
 * The list owns all nodes and all Student objects
 * No sharing of Student* between lists	is allowed
 */
struct Node{
    Student* data;
    Node* next; // pointer to next node
    Node(Student* val) : data(val), next(nullptr) {}
    ~Node(){
        if(data != nullptr) delete data;
    }
};
class List342
{
    private:
    Node* head_;
    int size_;
    void clear();
    bool isInList(const Student* obj);

    public:
    List342();
    List342(const List342 &other);
    ~List342();
    //Node* head() const; //mahy not need this UPD: yeah I didnt need this, thought I would need to add an extra public caller for head but no apparently
    // c++ makes it so files of the same type are capable of accessing eachother's private nodes, so that's something new I learned from this.
    List342 &operator=(const List342& other);
    bool buildList(const std::string &filename);
    bool insert(const Student *obj);
    bool remove(const Student &target, Student &result);
    bool peek(const Student &target, Student &result) const;
    int size() const;
    void deleteList();
    bool merge(List342 &other);
    bool operator==(const List342 &rhs) const;
    bool operator!=(const List342& rhs) const;
    friend std::ostream& operator<<(std::ostream& os, const List342& list); // had to do this so I could make this work, not sure if that was allowed in the spec.
};

#endif