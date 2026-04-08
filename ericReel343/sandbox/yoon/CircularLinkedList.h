#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class CircularLinkedList {
private:
    struct Node {
        T data;         // Data stored in the node
        Node* next;     // Pointer to the next node

        // Initialize
        Node(const T& d) {
            data = d;
            next = nullptr;
        }
    };
    Node* current; // Pointer to the current node
    int count; // Number of nodes in the list

public:
    // Constructor
    CircularLinkedList(const vector<T>& items) {
        current = nullptr;
        count = 0;

        for (const auto& item : items) {
            add(item);
        }
    }

    // Destructor
    ~CircularLinkedList() {
        while (count > 0) {
            removeNext(0);
        }
    }

    // Add new node into the circular list
    void add(const T& value) {
        Node* newNode = new Node(value);

        if (!current) {
            // If list is empty, new node points itself
            current = newNode;
            current->next = current;
        } else {
            // Insert new node after current
            newNode->next = current->next;
            current->next = newNode;
        }
        count++;
    }

    // Return the number of nodes
    int size() const {
        return count;
    }

    // Return the current data
    T getCurrent() const {
        return current->data;
    }

    // Remove k-th node after current
    T removeNext(int k){
        Node* prev = current;

        for (int i = 0; i < k; i++) {
            prev = prev->next;
        }

        Node* target = prev->next;
        T value = target->data;

        if (target == prev) {
            current = nullptr;
        } else {
            prev->next = target->next; // Remove node from the list
            current = target->next; // Move current pointer to next
        }

        delete target;
        count--;

        return value;
    }

    // Print circular list for debugging
    void printList() const {
        if (!current) {
            cout << "Empty list\n";
            return;
        }

        Node* temp = current;
        cout << "\nList: ";

        cout << temp->data << ", ";
        temp = temp->next;

        while (temp != current) {
            cout << temp->data << ", ";
            temp = temp->next;
        }
        cout << "(move to starting point)\n";
    }
};