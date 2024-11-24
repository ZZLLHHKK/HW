#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;

//design your won SuffixTreeNode using in SuffixTree
class SuffixTreeNode {
public :
    unordered_map<char, SuffixTreeNode*> child;
    vector<int> order;
};

class SuffixTree {
private:
    SuffixTreeNode *root;
    string text;
public:
    SuffixTree(const string &text) : text(text) {
        root = new SuffixTreeNode();
        for (int i = 1; i <= text.size(); ++i)
            build(text.substr(text.size() - i));
    }

    void build(string sub) {
        SuffixTreeNode *cur = root;
        int idx = text.size() - sub.size();
        for (char c : sub) {
            if (cur->child[c] == nullptr) 
                cur->child[c] = new SuffixTreeNode();
            cur = cur->child[c];
            cur->order.push_back(idx);
        }
    }

    bool exist(const string &substring) {
        SuffixTreeNode *cur = root;
        for (char c : substring) {
            if (!cur->child.count(c)) //是否存在
                return false;
            cur = cur->child[c];
        }
        return true;
    }

    int count(const string &substring) {
        SuffixTreeNode *cur = root;
        for (char c : substring) {
            if (!cur->child.count(c))
                return 0;
            cur = cur->child[c];
        }
        return cur->order.size();
    }

    ~SuffixTree() {
        delete root;
    }
};

int main() {
    string text = "";
    while (true) {
        string temp;
        getline(cin, temp);
        if (temp == "")
            break;
        text += temp;
    }
    SuffixTree tree(text);

    string query;
    while (true) {
        getline(cin, query);
        if (query == "")
            break;
        cout << "Existence of '" << query << "': " << (tree.exist(query) ? "Yes" : "No") << endl;
        cout << "Count of '" << query << "': " << tree.count(query) << endl;
    }
    return 0;
}
