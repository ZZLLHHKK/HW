#include <iostream>
#include <cstdlib>
#include <ctime>
#define SIZE 100
using namespace std;

class Node {
public:
    Node() : next(NULL), pre(NULL) {}
    Node(int n) : data(n), next(NULL), pre(NULL) {}
    int getData() { 
        return data; 
    }
    Node *getNext() { 
        return next; 
    }
    Node *getPre() { 
        return pre; 
    }
    void setData(int d) { 
        data = d; 
    }
    void setNext(Node *n) { 
        next = n; 
    }
    void setPre(Node *p) { 
        pre = p; 
    }
private:
    int data;
    Node *next, *pre; 
};

class List {
public:
    List() : list(NULL) {}
    List(int n) { 
        generate(n); 
    }
    void generate(int n) {
        list = NULL;
        for(int j = 0; j < n; ++j)
            generate();
    }
    void generate() {
        Node *buf = new Node(rand() % 10);
        buf -> setNext(list);
        if (list != NULL)
            list -> setPre(buf);
        list = buf;
    }
    void bubbleSort() {
        for (Node *i = list; i != NULL; i = i -> getNext()) {
            for (Node *j = list; j -> getNext() != NULL; j = j -> getNext()) {
                if (j -> getData() > j -> getNext() -> getData())
                    swapN(j, j -> getNext());
            }
        }
    }
    void selectionSort() {
        Node *s = list;
        while (s != NULL) {
            Node *tmp = s -> getNext();
            while (tmp != NULL) {
                if (tmp -> getData() < s -> getData())
                    swapN(s, tmp);
                tmp = tmp -> getNext();
            }
            s = s -> getNext();
        }
    }
    void insertionSort() {
        for (Node *i = list; i != NULL; i = i -> getNext()) {
            Node *j = i -> getPre(), *ind = i;
            while (j != NULL) {
                if (j -> getData() > ind -> getData())
                    swapN(j, ind);
                ind = j;
                j = j -> getPre();
            }
        }
    } 
    void print() {
        Node *cur = list;
        while (cur != NULL) {
            cout << cur -> getData() << " ";
            cur = cur -> getNext();
        }
        cout << endl;
    }
    void swapN(Node *x, Node *y) {
        int tmp = x -> getData();
        x -> setData(y -> getData());
        y -> setData(tmp);
    }
private:
    Node *list;
};

int main() {
    srand(time(NULL));
    List *l = new List(10);
    l -> print();
    l -> bubbleSort();
    l -> print();

    l = new List(10);
    l -> print();
    l -> insertionSort();
    l -> print();

    l = new List(10);
    l -> print();
    l -> selectionSort();
    l -> print();
}
