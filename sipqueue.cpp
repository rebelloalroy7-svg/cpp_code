#include <iostream>
using namespace std;

#define SIZE 100

class Queue {
private:
    int arr[SIZE];
    int front, rear;

public:
    Queue() {
        front = -1;
        rear = -1;
    }

    void enqueue(int value) {
        if (rear == SIZE - 1) {
            cout << "Queue Overflow!\n";
            return;
        }

        if (front == -1) front = 0;
        rear++;
        arr[rear] = value;
        cout << value << " enqueued.\n";
    }

    void dequeue() {
        if (front == -1 || front > rear) {
            cout << "Queue Underflow!\n";
            return;
        }

        cout << arr[front] << " dequeued.\n";
        front++;
    }

    void display() {
        if (front == -1 || front > rear) {
            cout << "Queue is empty.\n";
            return;
        }

        cout << "Queue elements: ";
        for (int i = front; i <= rear; i++) {
            cout << arr[i] << " ";
        }
        cout << "\n";
    }
};

int main() {
    Queue q;
    int choice, value;

    while (true) {
        cout << "\nQueue Operations Menu:\n";
        cout << "1. Enqueue\n";
        cout << "2. Dequeue\n";
        cout << "3. Display\n";
        cout << "4. Exit\n";
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
            cout << "Exiting...\n";
            return 0;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}
