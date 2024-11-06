#include <iostream>
#include <stdexcept>
#define SIZE 100
using namespace std;

class Deque {
private :
    int de[SIZE];
    int n; //current size
    int f, r; //front, rear
public :
    Deque() : n(0), f(0), r(0) {}
    int size() const {
        return n;
    }
    bool empty() const {
        return (n == 0);
    }
    void insertFront(const int& e) {
        if (n == SIZE)
            throw runtime_error("Deque is full\n");
        f = (f - 1 + SIZE) % SIZE;
        de[f] = e;
        n++;
    }
    void insertBack(const int& e) {
        if (n == SIZE)
            throw runtime_error("Deque is full\n");
        de[r] = e;
        r = (r + 1) % SIZE;
        n++;
    }
    void removeFront() {
        if (empty())
            throw runtime_error("Deque is empty\n");
        f = (f + 1) % SIZE;
        n--;
    }
    void removeBack() {
        if (empty())
            throw runtime_error("Deque is empty\n");
        r = (r - 1 + SIZE) % SIZE;
        n--;
    }
    void print() const {
        if (empty()) {
            cout << "Deque is empty\n";
            return;
        }
        int i = f;
        cout << "Current deque: ";
        for (int c = 0; c < n; c++) {
            cout << de[i] << " ";
            i = (i + 1) % SIZE;
        }
        cout << endl;
    }
};

int main() {
    Deque deq;
    deq.insertFront(3);
    deq.insertFront(2);
    deq.insertFront(1);
    deq.insertBack(4);
    deq.insertBack(5);
    deq.insertBack(6);
    deq.print();
    deq.removeFront();
    deq.removeBack();
    deq.print();
    cout << "Size of deque : " << deq.size() << endl;
    cout << "Is it empty : " << (deq.empty() ? "Yes" : "No") << endl;
}
