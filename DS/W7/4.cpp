#include <iostream>
#include <stdexcept>
using namespace std;

class Circlelist {
private :
    struct Node {
        int d;
        Node *next;
        Node() : d(0), next(nullptr) {}
        Node(int _d) : d(_d), next(nullptr) {}
    };
    Node *cursor;
public :
    Circlelist() : cursor(nullptr) {}
    ~Circlelist() {
        while (!empty())
            Remove();
    }
    bool empty() const {
        return cursor == nullptr;
    }
    int front() const {
        if (empty()) 
            throw runtime_error("List is empty");
        return cursor -> next -> d;
    }
    int back() const {
        if (empty()) 
            throw runtime_error("List is empty");
        return cursor -> d;
    }
    void advance() {
        cursor = cursor -> next;
    }
    void add(int d) {
        Node *newN = new Node(d);
        if (cursor == nullptr) {
            newN -> next = newN;
            cursor = newN; //cursor point to newN
        }
        else {
            newN -> next = cursor -> next;
            cursor -> next = newN;
        }
    }
    void Remove() {
        if (empty())
            throw runtime_error("List is empty\n");
        Node *old = cursor -> next; //remove node after cursor
        if (old == cursor)
            cursor = nullptr;
        else
            cursor -> next = old -> next;
        delete old;
    }
    int countNode(int cnt = 0) {
        if (empty())
            return 0;
        Node *cur = cursor -> next;
        while (cur != cursor) {
            cnt++;
            cur = cur -> next;
        }
        cnt++;
        return cnt;
    }
};

int main() {
    Circlelist cl;

    cl.add(10);
    cl.add(20);
    cl.add(30);
    
    cout << "Numbers of Nodes : " << cl.countNode() << endl;

    cout << "Front: " << cl.front() << endl;
    cout << "Back: " << cl.back() << endl;   

    cl.advance();
    cout << "After advancing, Front: " << cl.front() << endl; 

    cl.Remove();
    cout << "After removing front, Front: " << cl.front() << endl; 

    cl.Remove();
    cout << "After removing front, Front: " << cl.front() << endl;

    cl.Remove();
    cout << "Is the list empty : " << (cl.empty() ? "Yes" : "No") << endl; 
}
