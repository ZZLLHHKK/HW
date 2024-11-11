#include <bits/stdc++.h>
using namespace std;

template<class T>
class MinMaxHeap {
    vector<T> s;
    less<T> cmp;

    bool isMinLevel(int i)  {
        return !(__lg(++i) % 2);
    }

    void TrickleDown(int i) {
        if (isMinLevel(i)) 
            TrickleDownMin(i);
        else 
            TrickleDownMax(i);
    }

    int get_min_descendant(int id) {
        int res = (++id) * 2 - 1;
        for (int i = 2; i <= 4; i *= 2) {
            for (int j = 0; j < i; ++j) {
                int des = id * i + j - 1;
                if (des >= s.size())
                    return res;
                if (cmp(s[des], s[res]))
                    res = des;
            }
        }
        return res;
    }
    int get_max_descendant(int id) {
        int res = (++id) * 2 - 1;
        for (int i = 2; i <= 4; i *= 2) {
            for (int j = 0; j < i; ++j) {
                int des = id * i + j - 1;
                if (des >= s.size()) 
                    return res;
                if (cmp(s[res], s[des])) 
                    res = des;
            }
        }
        return res;
    }
    void TrickleDownMin(int id) {
        while ((id + 1) * 2 <= s.size()) {
            int m = get_min_descendant(id); //smallest (grand)children
            if (cmp(s[m], s[id])) {
                swap(s[m], s[id]);
                if (m <= (id + 1) * 2) 
                    return;
                int parent = (m + 1) / 2 - 1;
                if (cmp(s[parent], s[m])) 
                    swap(s[parent], s[m]);
                id = m;
            } 
            else 
                return;
        }
    }

    void TrickleDownMax(int id) {
        while ((id + 1) * 2 <= s.size()) {
            int m = get_max_descendant(id);
            if (cmp(s[id], s[m])) {
                swap(s[m], s[id]);
                if (m <= (id + 1) * 2) 
                    return;
                int parent = (m + 1) / 2 - 1;
                if (cmp(s[m], s[parent])) 
                    swap(s[parent], s[m]);
                id = m;
            } 
            else 
                return;
        }
    }

    void BubbleUp(int id) {
        if (!id) return;
        int parent = (id + 1) / 2 - 1;
        if (isMinLevel(id)) {
            if (cmp(s[parent], s[id])) {
                swap(s[parent], s[id]);
                BubbleUpMax(parent);
            } 
            else 
                BubbleUpMin(id);
        } 
        else {
            if (cmp(s[id], s[parent])) {
                swap(s[parent], s[id]);
                BubbleUpMin(parent);
            } 
            else 
                BubbleUpMax(id);
        }
    }

    void BubbleUpMin(int id) {
        while (id > 2) {
            int grandparent = (id + 1) / 4 - 1;
            if (cmp(s[id], s[grandparent])) {
                swap(s[id], s[grandparent]);
                id = grandparent;
            } 
            else 
                break;
        }
    }

    void BubbleUpMax(int id) {
        while (id > 2) {
            int grandparent = (id + 1) / 4 - 1;
            if (cmp(s[grandparent], s[id])) {
                swap(s[id], s[grandparent]);
                id = grandparent;
            } 
            else 
                break;
        }
    }

    int find_max_id() const {
        int res = 0;
        int n = min(s.size(), size_t(3));
        while (--n) { 
            if (cmp(s[res], s[n])) 
                res = n;
        }
        return res;
    }

    void erase_id(int id) {
        s[id] = s.back();
        s.pop_back();
        TrickleDown(id);
    }

public:
    bool empty() const {
        return s.empty();
    }

    int size() const {
        return s.size();
    }

    void insert(T d) {
        s.push_back(d);
        BubbleUp(s.size() - 1);
    }

    T getMax() const {
        if (empty()) throw runtime_error("Heap is empty");
        return s[find_max_id()];
    }

    T getMin() const {
        if (empty()) throw runtime_error("Heap is empty");
        return s[0];
    }

    void deleteMax() {
        erase_id(find_max_id());
    }

    void deleteMin() {
        erase_id(0);
    }
};

int main() {
    MinMaxHeap<int> mmHeap;
    srand(time(NULL));
    for (int j = 0; j < 10; j++)
        mmHeap.insert(rand() % 100);

    while (true) {
        try {
            cout << mmHeap.getMin() << " ";
            mmHeap.deleteMin();
        }
        catch(exception) {
            break;
        }
    }
    cout << endl;

    for (int j = 0; j < 10; j++)
        mmHeap.insert(rand() % 100);

    while (true) {
        try {
            cout << mmHeap.getMax() << " ";
            mmHeap.deleteMax();
        }
        catch(exception) {
            break;
        }
    }
    cout << endl;
}
