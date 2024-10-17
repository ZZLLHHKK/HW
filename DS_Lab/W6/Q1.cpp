#include <iostream>
#include <cmath>
#include <queue>
using namespace std;

template<class T>
class BinaryTreeInArray {
private:
    T *array;
    int height;
    int numOfElement;
    void resize(int size) {
        T *temp = new T[numOfElement];
        for (int j = 0; j < numOfElement; j++)
            temp[j] = array[j];
        delete[] array;
        array = new T[static_cast<int>(pow(2, height + 1)) - 1];
        for (int j = 0; j < numOfElement; j++)
            array[j] = temp[j];
        height++;
        delete[] temp;
    }
public:
    BinaryTreeInArray() : array(nullptr), height(0), numOfElement(0) {}
    void addElementAsCompleteTree(T data) {
        int cap = pow(2, height) - 1;
        if (numOfElement + 1 > cap)
            resize((cap + 1) * 2 - 1);
        array[numOfElement] = data;
        numOfElement++;
    }
    void displayInorder(int n) { 
        if (n >= numOfElement) return; 
        displayInorder(2 * n + 1);
        cout << array[n] << " ";
        displayInorder(2 * n + 2);
    }
    void displayPreorder(int n) {
        if (n >= numOfElement) return; 
        cout << array[n] << " ";
        displayPreorder(2 * n + 1);
        displayPreorder(2 * n + 2);
    }
    void displayPostorder(int n) {
        if (n >= numOfElement) return; 
        displayPostorder(2 * n + 1);
        displayPostorder(2 * n + 2);
        cout << array[n] << " ";
    }
};

template<class T>
class BinaryTreeInLinkedList {
private:
    class TreeNode {
    private:
    public:
        TreeNode(T d) : data(d), left(nullptr), right(nullptr) {}
        TreeNode *left, *right;
        T data;
    };
    TreeNode *root;
    int numOfElement;
public:
    BinaryTreeInLinkedList() : root(nullptr), numOfElement(0) {}
    void addElementAsCompleteTree(T data) {
        TreeNode *newN = new TreeNode(data);
        if (root == nullptr) {
            root = newN;
            return;
        }
        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode *cur = q.front();
            q.pop();
            if (cur -> left == nullptr) {
                cur -> left = newN;
                return;
            }
            else
                q.push(cur -> left);
            if (cur -> right == nullptr) {
                cur -> right = newN;
                return;
            }
            else
                q.push(cur -> right);
        }
    }
    void displayInorder() {
        In(root);
    }
    void displayPreorder() {
        Pre(root);
    }
    void displayPostorder() {
        Pos(root);
    }
    void In(TreeNode *n) {
        if (n == nullptr) return;
        In(n -> left);
        cout << n -> data << " ";
        In(n -> right);
    }
    void Pre(TreeNode *n) {
        if (n == nullptr) return;
        cout << n -> data << " ";
        Pre(n -> left);
        Pre(n -> right);
    }
    void Pos(TreeNode *n) {
        if (n == nullptr) return;
        Pos(n -> left);
        Pos(n -> right);
        cout << n -> data << " ";
    }
};

int main() {
    BinaryTreeInArray<int> *b = new BinaryTreeInArray<int>;
    BinaryTreeInLinkedList<int> *tree = new BinaryTreeInLinkedList<int>;
    int n;
    cin >> n;
    for (int j = 0; j < n; j++) {
        b -> addElementAsCompleteTree(j);
        tree -> addElementAsCompleteTree(j);
    }
    b -> displayInorder(0);
    cout << endl;
    tree -> displayInorder();
    cout << endl;
    b -> displayPreorder(0);
    cout << endl;
    tree -> displayPreorder();
    cout << endl;
    b -> displayPostorder(0);
    cout << endl;
    tree -> displayPostorder();
    cout << endl;
    return 0;
}
