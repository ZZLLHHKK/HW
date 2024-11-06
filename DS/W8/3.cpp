#include <iostream>
#include <stdexcept>
using namespace std;

template <class T>
class Queue {
private :
    int *q;
    int n;
    int capacity;
    int r; //rear
public :
    Queue() : n(0), r(0), capacity(100) {
        q = new T[capacity];
    }
    ~Queue() {
        delete [] q;
    }
    int size() const {
        return n;
    }
    bool empty() const {
        return (n == 0);
    }
    const T& front() const {
        if (empty())
            throw runtime_error("Queue is empty\n");
        return q[0];
    }
    void enqueue(const T& e) {
        if (n == capacity)
            throw runtime_error("Queue is full\n");
        q[r++] = e;
        n++;
    }
    void dequeue() {
        if (n == 0)
            throw runtime_error("Queue is empty\n");
        n--;
        for (int i = 0; i < n; ++i)
            q[i] = q[i+1];
    }
    void print() {
        for (int i = 0; i < n; ++i)
            cout << q[i] << " ";
        cout << endl;
    }
};

int main() {
    Queue<int> q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.print();
    q.dequeue();
    q.print();
    cout << "Size of queue: " << q.size() << endl;
    cout << "Is it empty: " << (q.empty() ? "Yes" : "No") << endl;
}
