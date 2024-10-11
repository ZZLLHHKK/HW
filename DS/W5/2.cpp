#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;

class quadraticEq {
public :
    quadraticEq() : a(0), b(0), c(0) {}
    quadraticEq(int _a, int _b, int _c) : a(_a), b(_b), c(_c) {}
    quadraticEq operator+(const quadraticEq &other) {
        return quadraticEq(a + other.a, b + other.b, c + other.c);
    }
    quadraticEq operator-(const quadraticEq &other) {
        return quadraticEq(a - other.a, b - other.b, c - other.c);
    }
    bool operator==(const quadraticEq &other) {
        return (a == other.a && b == other.b && c == other.c);
    }
    bool operator!=(const quadraticEq &other) {
        return !(*this == other);
    }
    friend ostream& operator<<(ostream& o, const quadraticEq &eq) {
        int flag = 0;
        if (eq.a != 0) {
            if (eq.a == 1)
                o << "x^2";
            else
                o << eq.a << "x^2";
            flag = 1;
        }
        if (eq.b != 0 && flag == 1) {
            if (eq.b == 1)
                o << "x";
            else if (eq.b > 0)
                o << "+" << eq.b << "x";
            else 
                o << eq.b << "x";
        }
        if (eq.c != 0 && eq.c > 0)
            o << "+" << eq.c;
        else if (eq.c != 0 && eq.c < 0)
            o << eq.c;
        return o;
    }
    friend istream& operator>>(istream& i, quadraticEq &eq) {
        i >> eq.a >> eq.b >> eq.c;
        return i;
    }
    void calculate() const {
        double dis = (b * b) - (4 * a * c);
        double r1 = (-b + sqrt(dis)) / (2 * a);
        double r2 = (-b - sqrt(dis)) / (2 * a);
        if (dis < 0)
            cout << "no real solution" << endl;
        else if (dis > 0) {
            cout << "two different root :" << endl;
            cout << "root1 : " << r1 << endl;
            cout << "root1 : " << r2 << endl;
        }
        else {
            cout << "two same root :" << endl;
            cout << "root1 : " << r1 << endl;
        }
    }
private :
    int a, b, c;
};

int main() {
    srand(time(NULL));
    int a1 = rand() % 10 + 1, b1 = rand() % 10, c1 = rand() % 10;
    int a2 = rand() % 10 + 1, b2 = rand() % 10, c2 = rand() % 10;
    quadraticEq eq1(a1, b1, c1), eq2(a2, b2, c2);
    cout << "eq1 : " << eq1 << endl;
    cout << "eq2 : " << eq2 << endl;
    cout << endl;
    cout << "two eq add(eq1 + eq2) : " << (eq1 + eq2) << endl;
    cout << "two eq sub(eq1 - eq2) : " << (eq1 - eq2) << endl;
    cout << endl;
    cout << "eq1 equal to eq2 ? : " << ((eq1 == eq2) ? "true" : "false") << endl;
    cout << "eq1 not equal to eq2 ? : " << ((eq1 != eq2) ? "true" : "false") << endl;
    cout << endl;
    cout << "eq1 roots : " << endl;
    eq1.calculate();
    cout << endl;
    cout << "eq2 roots : " << endl;
    eq2.calculate();
}
