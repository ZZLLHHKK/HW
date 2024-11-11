#include <bits/stdc++.h>
using namespace std;

template<class T>
class MaxHeap {
public:
  //Constructing a empty heap.
    MaxHeap() {
        pq = new MaxHeap();
    }
  //To add an element to the heap.
    void insert(T val) {
        if (_size + 1 > vect.size())
            vect.push_back(0);
        vect[++_size] = val;
        shiftUp(_size);
    }
  //To remove the root element in the heap and return it.
    T extract() {
        T mx = vect[1];
        swap(vect[1], vect[--_size]);
        shiftUp(1);
        return mx;
    }
  //Return the number of element int the heap.
    int count() {
        return this -> _size;
    }
    void shiftUp(int i) {
        if (i > _size) return;
        if (i == 1) return;
        if (vect[i] < vect[p(i)]) {
            swap(vect[i], vect[p(i)]); 
            shiftUp(p(i));
        }
    }
    void shiftDown(int i) {
        if (i > _size) return;
        int swapId = i;
        if (l(i) <= _size && vect[swapId] < vect[l(i)])
            swapId = l(i);
        if (r(i) <= _size && vect[swapId] < vect[r(i)])
            swapId = r(i);
        if (swapId != i) {
            swap(vect[i], vect[swapId]);
            shiftDown(swapId);
        }
    }
private:
    int _size = 0;
    vector<T> vect = {-1};
    MaxHeap *pq;

    int p(int i) {return i >> 1;}
    int l(int i) {return i << 1;}
    int r(int i) {return (i << 1) + 1;}
};
