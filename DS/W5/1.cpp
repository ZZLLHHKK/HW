#include <iostream>
using namespace std;

class A {
public :
    int x;
    A() : x(0) {}
};

class B : public A {
public :
    int x;
    B() : x(1) {}
};

class C : public B {
public :
    int x;
    C() : x(2) {}
    void setX(int _x) {
        A::x = _x;
    }
    void display() {
        cout << "class A : x = " << A::x << endl;
        cout << "class B : x = " << B::x << endl;
        cout << "class C : x = " << C::x << endl;
    }
};

int main() {
    C c;
    c.display();
    c.setX(10);
    c.display();
}
