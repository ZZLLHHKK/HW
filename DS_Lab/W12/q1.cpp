#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

template<class T>
class BinaryThreadedTreeNode {
public:
    T* data;
    BinaryThreadedTreeNode *left, *right;
    bool isThread;

    BinaryThreadedTreeNode(T d) : data(new T(d)), left(nullptr), right(nullptr), isThread(false) {}
    BinaryThreadedTreeNode() : data(nullptr), left(nullptr), right(nullptr), isThread(false) {}
};

template<class T>
class BinarySearchThreadedTree {
private:
    BinaryThreadedTreeNode<T>* root;

    void CreateThread() {
        BinaryThreadedTreeNode<T>* p = nullptr;
        CT(root, p);
    }

    void CT(BinaryThreadedTreeNode<T>* r, BinaryThreadedTreeNode<T>*& p) {
        if (!r) return;
        
        CT(r->left, p);
        
        if (p && !p->right) {
            p->isThread = true;
            p->right = r;
        }
        
        p = r;
        
        if (!r->isThread)
            CT(r->right, p);
    }

public:
    BinarySearchThreadedTree() : root(nullptr) {}

    void insert(T d) {
        if (!root) {
            root = new BinaryThreadedTreeNode<T>(d);
        } else {
            insertRec(root, d);
        }
    }

    void insertRec(BinaryThreadedTreeNode<T>* node, T d) {
        if (d < *node->data) {
            if (node->left) {
                insertRec(node->left, d);
            } else {
                node->left = new BinaryThreadedTreeNode<T>(d);
            }
        } else {
            if (node->right) {
                insertRec(node->right, d);
            } else {
                node->right = new BinaryThreadedTreeNode<T>(d);
            }
        }
    }

    void print() {
        CreateThread();
        if (!root) return;
        
        BinaryThreadedTreeNode<T>* cur = root;
        while (cur->left) 
            cur = cur->left;
        
        while (cur) {
            cout << *(cur->data) << " ";
            if (cur->isThread) {
                cur = cur->right;
            } else {
                cur = cur->right;
                while (cur && cur->left)
                    cur = cur->left;
            }
        }
    }
};

int main() {
    int j;
    BinarySearchThreadedTree<int> bstt;
    srand(time(nullptr));
    for (j = 0; j < 10; j++) {
        bstt.insert(rand() % 100);
    }
    bstt.print();
    return 0;
}
