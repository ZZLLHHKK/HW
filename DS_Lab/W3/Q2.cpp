#include <iostream>
#include <cstring>
#define SIZE 100
using namespace std;

class Queue {
public:
    Queue() : front(-1), rear(-1), cnt(0) {}
    int isFull() {
        return (cnt == SIZE);
    }
    int isEmpty() {
        return (cnt == 0);
    }
    int enqueue(int data) {
        if (isFull())
            return -1;
        else {
            rear = (rear + 1) % SIZE;
            da[rear] = data;
            cnt++;
            return 1;
        }
    }
    int *dequeue() {
        if (isEmpty())
            return NULL;
        else {
            front = (front + 1) % SIZE;
            int *res = &da[front];  
            cnt--;
            return res;
        }
    }
private:
    int da[SIZE];
    int front, rear, cnt;
};

int main() {
    int data, *temp;
    char command[50];
    Queue *queue = new Queue();
    while (1) {
        cin >> command;
        if (strcmp(command, "exit") == 0)
            break;
        else if (strcmp(command, "enqueue") == 0) {
            cout << "Please input a integer data:";
            cin >> data;
            if (queue -> enqueue(data) == 1) 
                cout << "Successfully enqueue data " << data << " into queue." << endl;
            else
                cout << "Failed to enqueue data into queue." << endl;
        }
        else if (strcmp(command, "dequeue") == 0) {
            temp = queue -> dequeue();
            if (temp == NULL)
                cout << "Failed to dequeue a data from queue.\n";
            else
                cout << "Dequeue data " << *temp << " from queue." << endl;
        }
    }
}

/*another solution : normal queue
class Queue {
public:
    Queue() : front(0), rear(0), cnt(0) {}
    int isFull() {
        return (cnt == SIZE);
    }
    int isEmpty() {
        return (cnt == 0);
    }
    int enqueue(int data) {
        if (isFull())
            return -1;
        else {
            da[rear++] = data;
            cnt++;
            return 1;
        }
    }
    int *dequeue() {
        if (isEmpty())
            return NULL;
        else {
            int tmp = da[front];
            int *res = &tmp;
            for (int i = 0; i < rear - 1; ++i)
                da[i] = da[i+1];  
            cnt--, rear--;
            return res;
        }
    }
private:
    int da[SIZE];
    int front, rear, cnt;
};
*/
