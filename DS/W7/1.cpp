#include <iostream>
using namespace std;

class List {
private :
    struct Node {
        int data;
        Node *next;  
        Node() : data(0), next(nullptr) {}
        Node(int d, Node *n) : data(d), next(n) {}
    };
    Node *head = nullptr;
public :
    void insertFromHead(int n) {
        Node *newN = new Node(n, nullptr);
        if (head == nullptr) 
            head = newN;
        else {
            newN -> next = head;
            head = newN;
        }
    }
    void print() {
        Node *tmp = head;
        cout << "List : ";
        while (tmp != nullptr) {
            cout << tmp -> data << " ";
            tmp = tmp -> next;
        }
        cout << '\n';
    }
    int size(int cnt = 0) {
        Node *cur = head;
        while (cur != nullptr) {
            cur = cur -> next;
            cnt++;
        }
        return cnt;
    }
};

int main() {
    List l;
    l.insertFromHead(1);
    l.insertFromHead(2);
    l.insertFromHead(3);
    l.insertFromHead(4);
    l.insertFromHead(5);
    l.print();
    cout << "Size : " << l.size() << '\n';
}
