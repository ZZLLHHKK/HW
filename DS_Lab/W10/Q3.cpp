//PREPEND BEGIN
/*some text*/
//PREPEND END

//TEMPLATE BEGIN
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <ctime>
using namespace std;

template<class T>
class Node {
public:
	Node() {
		data = new T;
	}
	Node(T d) {
		data = new T;
		(*data) = d;
	}
	Node &operator=(T d) {
		(*data) = d;
		return *this;
	}
	friend ostream &operator<<(ostream &out, Node n) {
		out << *(n.data);
		return out;
	}
	friend ostream &operator<<(ostream &out, Node *n) {
		out << *(n->data);
		return out;
	}
	void setData(T d) {
		*data = d;
	}
	T &getData() const {
		return *data;
	}
protected:
	T *data;
};

template<class T>
class BinaryTreeNode : public Node<T> {
public:
	BinaryTreeNode() : Node<T>() {
		left = NULL;
		right = NULL;
	}
	BinaryTreeNode(T d) : Node<T>(d) {
		left = NULL;
		right = NULL;
	}
	BinaryTreeNode(BinaryTreeNode<T> *l, BinaryTreeNode<T> *r) : Node<T>() {
		left = l;
		right = r;
	}
	BinaryTreeNode(T d, BinaryTreeNode<T> *l, BinaryTreeNode<T> *r) : Node<T>(d) {
		left = l;
		right = r;
	}
	void setLeft(BinaryTreeNode<T> *l) {
		left = l;
	}
	void setRight(BinaryTreeNode<T> *r) {
		right = r;
	}
	BinaryTreeNode<T> *&getLeft() {
		return left;
	}
	BinaryTreeNode<T> *&getRight() {
		return right;
	}
	bool operator>(BinaryTreeNode<T> n) {
		if (*(this->data) > *(n.data))
			return true;
		return false;
	}
	bool operator==(BinaryTreeNode<T> n) {
		if (*(this->data) == *(n.data))
			return true;
		return false;
	}
private:
	BinaryTreeNode<T> *left, *right;
};

template<class T>
class AVLTree {
private:
    BinaryTreeNode<T> *root;
    void inorder(BinaryTreeNode<T> *cur, int n) {
        if (cur == NULL)
            return;
        inorder(cur->getRight(), n + 1);
        for (int j = 0; j < n; ++j)
            cout << "  ";
        cout << cur << endl;
        inorder(cur->getLeft(), n + 1);
    }
public:
    AVLTree() {
        root = new BinaryTreeNode<T>();
    }
    int height(BinaryTreeNode<T> *n) {
        if (n == nullptr)
            return -1;
        return 1 + max(height(n->getLeft()), height(n->getRight()));
    }
    int BalanceH(BinaryTreeNode<T> *l, BinaryTreeNode<T> *r) { // |balanceH| <= 1
        return height(l) - height(r);
    }
    BinaryTreeNode<T>* rotateleft(BinaryTreeNode<T> *x) {
        BinaryTreeNode<T> *y = x->getRight();
        BinaryTreeNode<T> *t2 = y->getLeft();
        y->setLeft(x);
        x->setRight(t2);
        return y;
    }
    BinaryTreeNode<T>* rotateright(BinaryTreeNode<T> *x) {    
        BinaryTreeNode<T> *y = x->getLeft();
        BinaryTreeNode<T> *t2 = y->getRight();
        y->setRight(x);
        x->setLeft(t2);
        return y;
    }
    void insert(T d) {
        root = in(root, d);
    }

    BinaryTreeNode<T>* in(BinaryTreeNode<T> *n, T d) {
        if (n == nullptr)
            return new BinaryTreeNode<T>(d);
        
        if (d < n->getData())
            n->setLeft(in(n->getLeft(), d));
        else if (d > n -> getData())
            n->setRight(in(n->getRight(), d));
        else 
            return n;
        
        int b = BalanceH(n->getLeft(), n->getRight());

        if (b > 1 && d < n->getLeft()->getData()) //LL case
            return rotateright(n);
        if (b < -1 && d > n->getRight()->getData()) //RR case
            return rotateleft(n);
        if (b > 1 && d > n->getLeft()->getData()) { //RL case
            n->setLeft(rotateleft(n->getLeft()));
            return rotateright(n);
        }
        if (b < -1 && d < n->getRight()->getData()) { //LR case
            n->setRight(rotateright(n->getRight()));
            return rotateleft(n);
        }

        return n;
    }
    void inorder() {
        inorder(root, 0);
    }
};

int main() {
    AVLTree<int> *tree = new AVLTree<int>();
    srand(0);
    for (int j = 0; j < 20; ++j) {
        tree->insert(rand() % 100);
        tree->inorder();
    }
}
