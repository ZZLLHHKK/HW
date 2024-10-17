#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

template<class T>
class TreeInLinkedList {
private:
    class TreeNode {
    private:
    public:
        TreeNode(T d, TreeNode *p) : data(d), parent(p) {}
        TreeNode *parent;
        T data;
    };
    vector<TreeNode *> *nodeList;
public:
    TreeInLinkedList() {
        nodeList = new vector<TreeNode *>();
    }
    void addElement(T data) {
        int k = nodeList -> size();

        if (data == 1) {
            nodeList -> clear();
            nodeList = new vector<TreeNode *>();
            TreeNode *newNode = new TreeNode(data, nullptr);
            nodeList -> push_back(newNode);
        }
        else {
            for (int j = 0; j < k; j++) {
                if (data % (*nodeList)[j] -> data == 0) {
                    TreeNode *newNode = new TreeNode(data, (*nodeList)[j]);
                    nodeList -> push_back(newNode);
                }
            }
        }
    }
    void displayPreorder() {
        if (!nodeList -> empty()) {
            for (TreeNode *node : *nodeList) {
                if (node -> parent == nullptr) {
                    Pre(node);
                    break;
                }
            }
        }
    }
    void displayPostorder() {
        if (!nodeList -> empty()) {
            for (TreeNode *node : *nodeList) {
                if (node -> parent == nullptr) {
                    Pos(node);
                    break;
                }
            }
        }
    }
    void Pre(TreeNode *p) { //中左右
        if (p == nullptr) return;
        cout << p -> data << " ";
        for (TreeNode *c : *nodeList) {
            if (c -> parent == p)
                Pre(c);
        }
    }
    void Pos(TreeNode *p) { //左右中
        if (p == nullptr) return;
        for (TreeNode *c : *nodeList) {
            if (c -> parent == p)
                Pos(c);
        }
        cout << p -> data << " ";
    }
};

int main() {
    TreeInLinkedList<int> *tree = new TreeInLinkedList<int>();
    int n;
    cin >> n;
    for (int j = 1; j <= n; j++) 
        tree -> addElement(j);
    tree -> displayPreorder();
    cout << endl;
    tree -> displayPostorder();
    cout << endl;
}
