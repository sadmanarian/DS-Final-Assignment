#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

const int MAX_SIZE = 100;
char stack[MAX_SIZE];
int topIndex = -1;

void push(char element) {
    stack[++topIndex] = element;
}

char pop() {
    return stack[topIndex--];
}

void reverseExpression(char* expression) {
    int length = strlen(expression);
    for (int i = 0; i < length / 2; i++) {
        swap(expression[i], expression[length - i - 1]);
    }
}

int getPrecedence(char operatorChar) {
    if (operatorChar == '+' || operatorChar == '-') return 1;
    if (operatorChar == '*' || operatorChar == '/') return 2;
    if (operatorChar == '^') return 3;
    return 0;
}

void convertToPrefix(char* infix, char* prefix) {
    reverseExpression(infix);
    int prefixIndex = 0;

    for (int i = 0; infix[i] != '\0'; i++) {
        char currentChar = infix[i];

        if (isalnum(currentChar)) {
            prefix[prefixIndex++] = currentChar;
        } else if (currentChar == ')') {
            push(currentChar);
        } else if (currentChar == '(') {
            while (stack[topIndex] != ')') {
                prefix[prefixIndex++] = pop();
            }
            pop();
        } else {
            while (topIndex != -1 && getPrecedence
            (stack[topIndex]) >= getPrecedence(currentChar)) {
                prefix[prefixIndex++] = pop();
            }
            push(currentChar);
        }
    }

    while (topIndex != -1) {
        prefix[prefixIndex++] = pop();
    }

    prefix[prefixIndex] = '\0';
    reverseExpression(prefix);
}

int evaluatePrefix(char* prefix) {
    int numberStack[MAX_SIZE];
    int numTopIndex = -1;

    for (int i = strlen(prefix) - 1; i >= 0; i--) {
        char currentChar = prefix[i];

        if (isdigit(currentChar)) {
            numberStack[++numTopIndex] = currentChar - '0';
        } else {
            int operand1 = numberStack[numTopIndex--];
            int operand2 = numberStack[numTopIndex--];

            switch (currentChar) {
                case '+': numberStack[++numTopIndex] = operand1 + operand2; break;
                case '-': numberStack[++numTopIndex] = operand1 - operand2; break;
                case '*': numberStack[++numTopIndex] = operand1 * operand2; break;
                case '/': numberStack[++numTopIndex] = operand1 / operand2; break;
                case '^': numberStack[++numTopIndex] = pow(operand1, operand2); break;
            }
        }
    }
    return numberStack[numTopIndex];
}

int main() {
    char infixExpression[MAX_SIZE], prefixExpression[MAX_SIZE];
    cout << "Enter the infix expression: ";
    cin >> infixExpression;

    convertToPrefix(infixExpression, prefixExpression);

    cout << "Converted Prefix Expression: " << prefixExpression << endl;
    cout << "Evaluation Result: " << evaluatePrefix(prefixExpression) << endl;

    return 0;
}
