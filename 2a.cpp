#include <iostream>
#include <cctype>
using namespace std;

struct Node {
    char val;
    Node* next;
};

Node* stackTop = nullptr;

void push(char c) {
    Node* node = new Node;
    node->val = c;
    node->next = stackTop;
    stackTop = node;
}

char pop() {
    if (stackTop == nullptr) {
        cout << "Stack Underflow" << endl;
        return -1;
    }
    char tempVal = stackTop->val;
    Node* tempNode = stackTop;
    stackTop = stackTop->next;
    delete tempNode;
    return tempVal;
}

char peek() {
    return (stackTop != nullptr) ? stackTop->val : -1;
}

int getPrecedence(char c) {
    if (c == '(') return 0;
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    if (c == '^') return 3;
    return 0;
}

bool isStackEmpty() {
    return stackTop == nullptr;
}

int main() {
    char expression[100];
    char* ptr;
    char poppedChar;

    cout << "Enter infix expression: ";
    cin >> expression;

    ptr = expression;

    cout << "Converted Postfix Expression: ";
    while (*ptr != '\0') {
        if (isalnum(*ptr)) {
            cout << *ptr; // Print operands directly
        } else if (*ptr == '(') {
            push(*ptr);
        } else if (*ptr == ')') {
            while ((poppedChar = pop()) != '(') {
                cout << poppedChar; // Pop and print until '('
            }
        } else {
            while (!isStackEmpty() && getPrecedence(peek()) >= getPrecedence(*ptr)) {
                cout << pop();
            }
            push(*ptr);
        }
        ptr++;
    }

    while (!isStackEmpty()) {
        cout << pop();
    }

    cout << endl;
    return 0;
}
