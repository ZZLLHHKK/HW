#include <iostream>
using namespace std;

template<class T>
class List {
private :
    struct Node {
        T d;
        Node *next, *prev;
        Node() : d(T()), next(nullptr), prev(nullptr) {}
        Node(T data) : d(data), next(nullptr), prev(nullptr) {}
    };
    Node *head, *trailer;
public :
    List() {
        head = new Node();
        trailer = new Node();
        head -> next = trailer;
        trailer -> prev = head;
    }
    ~List() {
        while (!empty())
            removeFront();
        delete head;
        delete trailer;
    }
    bool empty() const {
        return (head -> next == trailer);
    }
    T front() const {
        if (!empty())
            return head -> next -> d;
        else 
            return T();
    }
    T back() const {
        if (!empty())
            return trailer -> prev -> d;
        else 
            return T();
    }
    void addFront(T d) {
        add(head -> next, d);
    }
    void addBack(T d) {
        add(trailer, d);
    }
    void removeFront() {
        if (!empty())
            Remove(head -> next);
    }
    void removeBack() {
        if (!empty())
            Remove(trailer -> prev);
    }
protected :
    void add(Node *v, T d) { //insert new Node before v
        Node *newN = new Node(d);
        newN -> next = v;
        newN -> prev = v -> prev;
        v -> prev = newN;
        newN -> prev -> next = newN;
    } 
    void Remove(Node *v) {
        Node *u = v -> prev;
        Node *w = v -> next;
        u -> next = w;
        w -> prev = u;
        delete v;
    }
};

int main() {
    List<int> l;
    l.addFront(10);
    l.addFront(20);
    l.addFront(30);

    cout << "Front : " << l.front() << endl; 
    cout << "Back : " << l.back() << endl;  

    l.removeFront();
    cout << "New Front : " << l.front() << endl; 

    l.removeBack();
    cout << "New back : " << l.back() << endl; 

    l.removeFront();
    cout << "Move front, is it empty : " << (l.empty() ? "Yes" : "No") << endl; 

    l.removeBack();
    cout << "Move back, is it empty : " << (l.empty() ? "Yes" : "No") << endl;
}
