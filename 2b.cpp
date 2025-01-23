#include <iostream>
#include <queue>
using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;

    Node(int val) {
        value = val;
        left = nullptr;
        right = nullptr;
    }
};

class BinarySearchTree {
    Node* root;

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(int val) {
        Node* newNode = new Node(val);
        if (!root) {
            root = newNode;
            return;
        }

        Node* current = root;
        Node* parent = nullptr;

        while (current) {
            parent = current;
            if (val < current->value) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        if (val < parent->value) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
    }

    int calculateHeight(Node* node) {
        if (!node) return 0;
        int leftHeight = calculateHeight(node->left);
        int rightHeight = calculateHeight(node->right);
        return max(leftHeight, rightHeight) + 1;
    }

    void inorderTraversal(Node* node) {
        if (!node) return;
        inorderTraversal(node->left);
        cout << node->value << " ";
        inorderTraversal(node->right);
    }

    void display() {
        inorderTraversal(root);
        cout << endl;
    }

    int getHeight() {
        return calculateHeight(root);
    }
};

int main() {
    BinarySearchTree bst;
    int elements[] = {3, 2, 1, 5, 7, 6, 10};

    for (int val : elements) {
        bst.insert(val);
    }

    cout << "Inorder Traversal of BST: ";
    bst.display();
    cout << "Height of BST: " << bst.getHeight() << endl;

    return 0;
}
