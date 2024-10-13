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
        for (int j = 0; j < n; ++j)
            generate();
    }
    void generate() {
        Node *buf = new Node(rand() % 10 + 1);
        buf -> setNext(list);
        if (list != NULL)
            list -> setPre(buf);
        list = buf;
    }
    void bubbleSort() {
        Node *be4, *aft, *tmp;
        bool sorted = false;
        
        while (sorted == false) {
            sorted = true;
            tmp = list;
            while (tmp -> getNext() != NULL) {
                if (tmp -> getData() > tmp -> getNext() -> getData()) {
                    be4 = tmp -> getPre();
                    aft = tmp -> getNext();
                    if (be4 != NULL)
                        be4 -> setNext(aft);
                    else
                        list = aft;
                    tmp -> setNext(aft -> getNext());
                    if (aft -> getNext() != NULL) {
                        Node *i = aft -> getNext();
                        i -> setPre(tmp);
                    }
                    tmp -> setPre(aft);
                    aft -> setNext(tmp);
                    aft -> setPre(be4);
                    sorted = false;
                }
                else
                    tmp = tmp -> getNext();
            }
        }
    }
    void selectionSort() {
        Node *cur = list;
        while (cur != NULL) {
            Node *min = cur;
            Node *run = cur -> getNext();
            while (run != NULL) {
                if (run -> getData() < min -> getData())
                    min = run;
                run = run -> getNext();
            }
            if (min != cur) {
                swapN(cur, min);
                cur = min -> getNext();
            }
            else 
                cur = cur -> getNext(); 
        }
    }
    void insertionSort() {
        Node *cur = list;
        Node *ans = NULL;

        while (cur != NULL) {
            Node *next = cur -> getNext();
            if (ans == NULL || ans -> getData() >= cur -> getData()) {
                cur -> setNext(ans);
                if (ans != NULL)
                    ans -> setPre(cur);
                cur -> setPre(NULL);
                ans = cur;
            }
            else {
                Node *tmp = ans;
                while (tmp -> getNext() != NULL && tmp -> getNext() -> getData() < cur -> getData())
                    tmp = tmp -> getNext();
                cur -> setNext(tmp -> getNext());
                cur -> setPre(tmp);
                tmp -> setNext(cur);
                if (cur -> getNext() != NULL)
                    cur -> getNext() -> setPre(cur);
            }
            cur = next;
        }

        list = ans;
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
        if (x == y) return;
        bool adj = (x -> getNext() == y || y -> getNext() == x);
        if (adj) {
            if (x -> getNext() == y) {
                Node *preX = x -> getPre();
                Node *nextY = y -> getNext();
                if (preX != NULL) 
                    preX -> setNext(y);
                else 
                    list = y;
                y -> setPre(preX);
                y -> setNext(x);
                x -> setPre(y);
                x -> setNext(nextY);
                if (nextY != NULL)
                    nextY -> setPre(x);
            }
            else 
                swapN(y, x);
        }
        else {
            Node *preX = x -> getPre(), *nextX = x -> getNext();
            Node *preY = y -> getPre(), *nextY = y -> getNext();
            if (preX != NULL)
                preX -> setNext(y);
            else
                list = y;
            if (preY != NULL)
                preY -> setNext(x);
            else
                list = x;
            if (nextX != NULL)
                nextX -> setPre(y);
            if (nextY != NULL)
                nextY -> setPre(x);
            x -> setPre(preY);
            x -> setNext(nextY);
            y -> setPre(preX);
            y -> setNext(nextX);
        }
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
