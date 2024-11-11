#include <bits/stdc++.h>
using namespace std;

class ExpressionTree {
private:
    struct Node {
        int precedence;
        string value;
        Node* left;
        Node* right;
        Node *parent;
        Node() : value(""), left(nullptr), right(nullptr), parent(nullptr), precedence(0) {}
        Node(const string& val) : value(val), left(nullptr), right(nullptr), parent(nullptr), precedence(0) {}
    };
    Node* root;
    vector<string> calexp;
public:
    //Constructor of class ExpressionTree take a string as an infix expression and build the expression tree base on that.
    //there are five different operation you have to consider, +(addition), -(subtraction), *(multiplication), /(division) and %(modulus).
    //you also need to consider -(negative) sign.
    //all operands are integer
    ExpressionTree(const string &expression) {
        root = new Node();
        root -> precedence = -1e7;
        Node *preOperand = nullptr;
        Node *preOperator = root;
        int cor = 0; //優先級

        string token;
        stringstream ss(expression);

        while (ss >> token) {
            if (isOperand(token)) 
                preOperand = new Node(token);
            else if (isOperator(token)) {
                Node *p = new Node(token);
                p -> precedence = getPrecedence(token) + cor;
                if (p -> precedence > preOperator -> precedence) {
                    p -> left = preOperand;
                    preOperator -> right = p;
                    p -> parent = preOperator;
                }
                else {
                    preOperator -> right = preOperand;
                    Node *q = preOperator -> parent;
                    while (p -> precedence <= q -> precedence)
                        q = q -> parent;
                    p -> left = q -> right;
                    q -> right = p;
                    p -> parent = q;
                }
                preOperand = nullptr;
                preOperator = p;
            }
            else if (token == "(")
                cor += 2;
            else if (token == ")")
                cor -= 2;
        }
        if (preOperand != nullptr) 
            preOperator -> right = preOperand;
        Node *real = root -> right;
        delete root;
        root = real;
    }
    ~ExpressionTree() { 
        deleteTree(root); 
    }
    bool isOperator(const string &c) {
        return (c == "+" || c == "-" || c == "*" || c == "/" || c == "%");
    }
    bool isOperand(const string &c) {
        int n;
        stringstream ss(c);
        if (ss >> n)
            return true;
        else 
            return false;
    }
    int getPrecedence(const string &x) {
        if (x == "*" || x == "/" || x == "%")
            return 2;
        else 
            return 1;
    }
    void deleteTree(Node* node) {
        if (node == nullptr) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
    //print all element in infix order.
    void printInFixOrder() { //中
        inorder(root);
        cout << endl;
    }
    void inorder(Node *root) {
        if (root == nullptr) return;
        if (isOperator(root -> value))
            cout << "(";
        inorder(root -> left);
        cout << root -> value << " ";
        inorder(root -> right);
        if (isOperator(root -> value))
            cout << ")";
    }
    //print all element in prefix order.
    void printPreFixOrder() { //前
        preorder(root);
        cout << endl;
    }
    void preorder(Node *root) {
        if (root == nullptr) return;
        cout << root -> value << " ";
        preorder(root -> left);
        preorder(root -> right);
    }
    //print all element in postfix order.
    void printPostFixOrder() { //後
        postorder(root);
        cout << endl;
    }
    void postorder(Node *root) {
        if (root == nullptr) return;
        postorder(root -> left);
        postorder(root -> right);
        cout << root -> value << " ";
        calexp.push_back(root -> value);
    }
    //evaluate the expression, this function return an int since % can only work with integer in C
    int eval() { //use postfix
        stack<int> n;
        for (string s : calexp) {
            if (isOperator(s)) {
                int op1 = n.top(); n.pop();
                int op2 = n.top(); n.pop();
                if (s == "+") n.push(op2 + op1);
                if (s == "-") n.push(op2 - op1);
                if (s == "*") n.push(op2 * op1);
                if (s == "/") n.push(op2 / op1);
                if (s == "%") n.push(op2 % op1);
            }
            else 
                n.push(stoi(s));
        }
        return n.top();
    }
};

int main() {
    string infix = "( -12 + 3 ) * 4 % 5"; //意義不明
    getline(cin, infix);
    ExpressionTree exprTree(infix);

    cout << "Inorder: ";
    exprTree.printInFixOrder();
    cout << "Preorder: ";
    exprTree.printPreFixOrder();
    cout << "Postorder: ";
    exprTree.printPostFixOrder();
    cout << "Evaluated result: " << exprTree.eval() << endl;
}
