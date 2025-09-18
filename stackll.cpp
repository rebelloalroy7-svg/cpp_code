#include <iostream>
using namespace std;

// Node structure for linked list
struct Node {
    int data;       // Data part of the node
    Node* next;     // Pointer to next node
};

// Stack class using linked list
class Stack {
private:
    Node* top;      // Pointer to the top of the stack

public:
    // Constructor to initialize top as nullptr
    Stack() {
        top = nullptr;
    }

    // Function to push data into the stack
    void push(int value) {
        Node* newNode = new Node; // Create a new node
        newNode->data = value;    // Assign data
        newNode->next = top;      // Link new node to current top
        top = newNode;            // Update top to new node
        cout << value << " pushed to stack\n";
    }

    // Function to pop data from the stack
    void pop() {
        if (top == nullptr) {
            cout << "Stack is empty. Nothing to pop.\n";
            return;
        }
        Node* temp = top;          // Temporarily store top node
        cout << "Popped element: " << top->data << "\n";
        top = top->next;           // Move top to next node
        delete temp;               // Delete old top node
    }

    // Function to display the stack elements
    void display() {
        if (top == nullptr) {
            cout << "Stack is empty.\n";
            return;
        }
        cout << "Stack elements: ";
        Node* temp = top;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;     // Move to next node
        }
        cout << "\n";
    }

    // Destructor to clean up all nodes when stack is destroyed
    ~Stack() {
        while (top != nullptr) {
            pop();
        }
    }
};

int main() {
    Stack s;    // Create stack object
    int choice, value;

    do {
        // Menu for user actions
        cout << "\n1. Push\n2. Pop\n3. Display\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to push: ";
                cin >> value;
                s.push(value);
                break;
            case 2:
                s.pop();
                break;
            case 3:
                s.display();
                break;
            case 4:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
