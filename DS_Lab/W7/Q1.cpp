#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

template<class T>
class BinarySearchTree {
private:
    struct Node {
        T data;
        Node *left, *right;
    };
    Node *root;
public:
    BinarySearchTree() : root(nullptr) {}
    void insertElement(T d) {
        Node *newN = new Node();
        newN -> data = d;
        newN -> left = newN -> right = nullptr;
        if (root == nullptr) {
            root = newN;
            return;
        }
        else {
            Node *cur = root, *par = nullptr;
            while (cur != nullptr) {
                par = cur;
                if (cur -> data > d)
                    cur = cur -> left;
                else 
                    cur = cur -> right;
            }
            if (par -> data > d)
                par -> left = newN;
            else 
                par -> right = newN;
        }
    }
    void print() {
        inorder(root);
        cout << endl;
    }
    bool search(T d) {
        Node *cur = root;
        while (cur != nullptr) {
            if (cur -> data == d)
                return true;
            else if (cur -> data > d)
                cur = cur -> left;
            else 
                cur = cur -> right;
        }
        return false;
    }
    int height() {
        return h(root);
    }
    int h(Node *root) {
        if (root == NULL)
            return -1;
        else 
            return 1 + max(h(root -> left), h(root -> right));
    }
    void inorder(Node *n) {
        if (n == nullptr) return;
        inorder(n -> left);
        cout << n -> data << " ";
        inorder(n -> right);
    }
};

int main() {
    int data;
    string command;
    BinarySearchTree<int> *bst = new BinarySearchTree<int>();
    while (cin >> command) {
        if (command == "insert") {
            cin >> data;
            bst -> insertElement(data);
        }
        else if (command == "search") {
            cin >> data;
            if (bst -> search(data))
                cout << "true" << endl;
            else
                cout << "false" << endl;
        }
        else if (command == "height") 
            cout << bst -> height() << endl;
        else if (command == "print") 
            bst -> print();
        else if (command == "exit") 
            break;
    }
}
