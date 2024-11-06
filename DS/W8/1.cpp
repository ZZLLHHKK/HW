#include <iostream>
#include <stdexcept>
using namespace std;

template <class T>
class Stack;

template <class T>
class Node {
private:
    T d;
    Node<T> *next;
    friend class Stack<T>;
public:
    Node() : d(T()), next(nullptr) {}
    Node(T _d) : d(_d), next(nullptr) {}
};

template <class T>
class Stack {
public:
    Stack() : head(nullptr), n(0) {}
    bool empty() const {
        return head == nullptr;
    }
    const T& top() const {
        if (empty()) 
            throw runtime_error("Stack is empty");
        return head -> d;
    }
    void push(const T& d) {
        Node<T> *newN = new Node(d);
        if (head == nullptr)
            head = newN;
        else {
            newN -> next = head;
            head = newN;
        }
        n++;
    }
    void pop() {
        if (empty())
            throw runtime_error("Stack is empty");
        cout << "The stack has been popped\n";
        Node<T> *tmp = head;
        head = head -> next;
        delete tmp;
        n--;
    }
    void print() const {
        if (empty()) {
            cout << "Stack is empty" << endl;
            return;
        }
        Node<T> *tmp = head;
        cout << "current stack : ";
        while (tmp != nullptr) {
            cout << tmp -> d << " ";
            tmp = tmp -> next;
        }
        cout << endl;
    }
    int size() const {
        return n;
    }
private:
    int n;
    Node<T> *head;
};

int main() {
    Stack<int> st;
    for (int i = 1; i <= 5; ++i) 
        st.push(i);
    st.print();
    cout << "The stack is empty or not : " << (!st.empty() ? "No" : "Yes") << endl;
    cout << "current size : " << st.size() << endl;
    st.pop();
    cout << "current top : " << st.top() << '\n'; 
    st.print();
    for (int i = 1; i <= 4; ++i)
        st.pop();
    cout << "The stack is empty or not : " << (!st.empty() ? "No" : "Yes") << endl;
}
