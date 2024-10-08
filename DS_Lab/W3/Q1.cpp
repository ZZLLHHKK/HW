#include <iostream>
#include <cstring>
#define SIZE 100
using namespace std;

class Stack {
public:
    Stack() : top(-1) {}
    int push(int data) {
        if (top < SIZE - 1) {
            da[++top] = data;
            return 1;
        } 
        else 
            return -1;
    }
    int *pop() {
        if (top >= 0) 
            return &da[top--];
        else
            return NULL;
    }
private:
    int da[SIZE];
    int top;
};

int main() {
    int data, *temp;
    char command[50];
    Stack *stack = new Stack();
    while(1) {
        cin >> command;
        if (strcmp(command, "exit") == 0) 
            break;
        else if (strcmp(command, "push") == 0) {
            cout << "Please input a integer data:";
            cin >> data;
            if (stack -> push(data) == 1) 
                cout << "Successfully push data " << data << " into stack.\n";
            else
                cout << "Failed to push data into stack.\n";
        }
        else if (strcmp(command, "pop") == 0) {
            temp = stack -> pop();
            if (temp == NULL) 
                cout << "Failed to pop a data from stack.\n";
            else
                cout << "Pop data " << *temp << " from stack.\n" << endl;
        }
    }
}


/*another solution
class Stack {
public:
    Stack() : top(0) {}
    int push(int data) {
        if (top > SIZE - 1) 
            return -1;
        else {
            top++;
            da[top-1] = data;
            return 1;
        }
    }
    int *pop() {
        if (top == 0) 
            return NULL;
        else {
            int *res = &da[top-1];
            top--;
            return res;
        }
    }
private:
    int da[SIZE];
    int top;
};
*/
