#include <iostream>
using namespace std;

// Node structure for doubly linked list
struct Node {
    int data;       // Data stored in node
    Node* prev;     // Pointer to previous node
    Node* next;     // Pointer to next node

    Node(int val) : data(val), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
private:
    Node* head;     // Pointer to the first node
    Node* tail;     // Pointer to the last node

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Insert node at the end of the list
    void insert(int val) {
        Node* newNode = new Node(val);

        if (head == nullptr) {
            // If list is empty, new node is head and tail
            head = tail = newNode;
        } else {
            // Link the new node to the end of the list
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Display the list from head to tail
    void displayForward() {
        Node* temp = head;
        cout << "List (forward): ";
        while (temp != nullptr) {
            cout << temp->data << " <-> ";
            temp = temp->next;
        }
        cout << "nullptr" << endl;
    }

    // Display the list from tail to head
    void displayBackward() {
        Node* temp = tail;
        cout << "List (backward): ";
        while (temp != nullptr) {
            cout << temp->data << " <-> ";
            temp = temp->prev;
        }
        cout << "nullptr" << endl;
    }

    // Delete the first node with the given value
    void deleteNode(int val) {
        Node* temp = head;

        // Traverse the list to find the node to delete
        while (temp != nullptr && temp->data != val) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Value " << val << " not found in the list.\n";
            return;
        }

        // If node to delete is head
        if (temp == head) {
            head = head->next;
            if (head != nullptr) {
                head->prev = nullptr;
            } else {
                // List became empty
                tail = nullptr;
            }
        }
        // If node to delete is tail
        else if (temp == tail) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        // If node is in the middle
        else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }

        delete temp;
        cout << "Deleted node with value " << val << endl;
    }

    // Destructor to free all nodes
    ~DoublyLinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
};

int main() {
    DoublyLinkedList list;
    int n, val;

    cout << "How many nodes do you want to insert? ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "Enter value for node " << (i + 1) << ": ";
        cin >> val;
        list.insert(val);
    }

    list.displayForward();
    list.displayBackward();

    cout << "Enter a value to delete: ";
    cin >> val;
    list.deleteNode(val);

    list.displayForward();
    list.displayBackward();

    return 0;
}
