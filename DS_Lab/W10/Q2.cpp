#include <bits/stdc++.h>
using namespace std;

class Trie {
private :
    struct Node {
        bool isEnd;
        string segment;
        vector<int> order;
        Node* child[26];
        Node() : isEnd(false) {
            for (int i = 0; i < 26; ++i)
                child[i] = nullptr;
        }
    };
    Node *root;
public:
	/*
	construct a Trie.
	*/
    Trie() {
        root = new Node();
    }
	/*
	search trie for key, return true if exist, false if not.
	*/
    bool search(string key) {
        Node *cur = root;
        for (char ch : key) {
            int id = ch - 'a';
            if (cur->child[id] == nullptr)
                return false;
            cur = cur->child[id];
        }
        return cur->isEnd;
    }
	/*
	insert value into trie.
	*/
    void insert(string value) {
        Node* cur = root;
        int idx = 0;

        while (idx < value.size()) {
            int id = value[idx] - 'a';

            if (!cur->child[id]) {
                cur->child[id] = new Node();
                cur->order.push_back(id);
                cur->child[id]->segment = value.substr(idx);  // 儲存剩餘的字串
                cur->child[id]->isEnd = true;
                return;
            }

            Node* next = cur->child[id];
            string& seg = next->segment;

            int matchLen = 0;  // 找到匹配的前綴長度
            while (matchLen < seg.size() && idx + matchLen < value.size() &&
                    seg[matchLen] == value[idx + matchLen])
                ++matchLen;

            if (matchLen == seg.size()) {  // 完全匹配，繼續往下走
                idx += matchLen;
                cur = next;
            } else {  // 需要拆分節點
                Node* splitNode = new Node();
                splitNode->segment = seg.substr(matchLen);  // 剩下的部分
                splitNode->isEnd = next->isEnd;
                splitNode->order = next->order;

                for (int i : next->order)
                    splitNode->child[i] = next->child[i];

                next->segment = seg.substr(0, matchLen);
                next->isEnd = false;
                next->order.clear();
                fill(begin(next->child), end(next->child), nullptr);

                int splitId = splitNode->segment[0] - 'a';
                next->child[splitId] = splitNode;
                next->order.push_back(splitId);

                if (matchLen + idx < value.size()) {  // 插入新的部分
                    Node* newNode = new Node();
                    newNode->segment = value.substr(idx + matchLen);
                    newNode->isEnd = true;

                    int newId = newNode->segment[0] - 'a';
                    next->child[newId] = newNode;
                    next->order.push_back(newId);
                } 
                else   // 當前節點就是單字結尾
                    next->isEnd = true;
                return;
            }
        }
        cur->isEnd = true;
    }
	/*
	display trie in pre-order, each element in a line, display space befoer element base on the level of 	the element. level 1 for 2 space, level 2 for 4 space, level 3 for 6 space and so on, root is level 	0.
	*/
    void preorder() { //中左右 1->2 2->4 3->6
        cout << "[]\n";
        pre(root, 1);
    }
    void pre(Node *n, int l) {
        if (n == nullptr) return;

        for (int i : n -> order) {
            if (n->child[i] != nullptr) {
                cout << string(l * 2, ' ') << n->child[i]->segment << endl;
                pre(n->child[i], l + 1);
            }
        }
    }
};

int main() {
    Trie *trie = new Trie();
    string command, key, value;
    while (1) {
        cin >> command;
        if (command == "insert") {
            cin >> value;
            trie->insert(value);
        }
        else if (command == "search") {
            cin >> key;
            if (trie->search(key))
                cout << "exist" << endl;
            else
                cout << "not exist" << endl;
        }
        else if (command == "print") 
            trie->preorder();
        else if (command == "exit")
            break;
    }
}
