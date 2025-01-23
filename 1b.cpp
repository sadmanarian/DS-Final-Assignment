#include <iostream>
using namespace std;

struct Node {
    int value;
    Node* next;

    Node(int val) {
        value = val;
        next = nullptr;
    }
};

class Queue {
    Node* head;
    Node* tail;

public:
    Queue() : head(nullptr), tail(nullptr) {}

    void enqueue(int val) {
        Node* newNode = new Node(val);
        if (!tail) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void reverse() {
        Node* prev = nullptr;
        Node* current = head;
        Node* nextNode = nullptr;
        tail = head;

        while (current) {
            nextNode = current->next;
            current->next = prev;
            prev = current;
            current = nextNode;
        }
        head = prev;
    }

    void printQueue() const {
        Node* temp = head;
        while (temp) {
            cout << temp->value << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {
    Queue queue;

    queue.enqueue(55);
    queue.enqueue(65);
    queue.enqueue(70);
    queue.enqueue(75);
    queue.enqueue(80);

    cout << "Front to Rear: ";
    queue.printQueue();

    queue.reverse();
    cout << "Rear to Front: ";
    queue.printQueue();

    return 0;
}
