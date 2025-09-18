#include <iostream>
using namespace std;

// Node structure for linked list
struct Node {
    int data;       // Data part of the node
    Node* next;     // Pointer to the next node
};

// Queue class using linked list
class Queue {
private:
    Node* front;    // Pointer to the front of the queue
    Node* rear;     // Pointer to the rear of the queue

public:
    // Constructor to initialize front and rear as nullptr
    Queue() {
        front = nullptr;
        rear = nullptr;
    }

    // Function to add data to the queue (enqueue)
    void enqueue(int value) {
        Node* newNode = new Node;   // Create a new node
        newNode->data = value;      // Assign data
        newNode->next = nullptr;    // New node will be at the rear, so next is nullptr

        if (rear == nullptr) {
            // If queue is empty, new node is both front and rear
            front = rear = newNode;
        } else {
            rear->next = newNode;   // Link old rear node to new node
            rear = newNode;         // Update rear pointer
        }
        cout << value << " enqueued to queue\n";
    }

    // Function to remove data from the queue (dequeue)
    void dequeue() {
        if (front == nullptr) {
            cout << "Queue is empty. Nothing to dequeue.\n";
            return;
        }
        Node* temp = front;          // Store front node temporarily
        cout << "Dequeued element: " << front->data << "\n";
        front = front->next;         // Move front pointer to next node

        // If front becomes nullptr, then queue is empty, update rear as well
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;                 // Delete old front node
    }

    // Function to display queue elements from front to rear
    void display() {
        if (front == nullptr) {
            cout << "Queue is empty.\n";
            return;
        }
        cout << "Queue elements: ";
        Node* temp = front;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;      // Move to next node
        }
        cout << "\n";
    }

    // Destructor to clean up all nodes when queue is destroyed
    ~Queue() {
        while (front != nullptr) {
            dequeue();
        }
    }
};

int main() {
    Queue q;     // Create queue object
    int choice, value;

    do {
        // User menu
        cout << "\n1. Enqueue\n2. Dequeue\n3. Display\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to enqueue: ";
                cin >> value;
                q.enqueue(value);
                break;
            case 2:
                q.dequeue();
                break;
            case 3:
                q.display();
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
