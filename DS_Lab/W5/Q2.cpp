#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
#define SIZE 10
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

class Grid {
public:
    Grid() {
        Grid(0);
    }
    Grid(int s) {
        state = s;
        dir[UP] = NULL;
        dir[DOWN] = NULL;
        dir[LEFT] = NULL;
        dir[RIGHT] = NULL;
    }
    Grid *getDir(int d) { return dir[d]; }
    int getState() { return state; }
    void setDir(int d, Grid *g) { dir[d] = g; }
    void setState(int s) { state = s;}
private:
    Grid *dir[4];
    int state;
};

struct List {
public:
    List() : top(0) {}
    /*
    Insert an element from top
    */
    void addElement(Grid *g) {
        if (top < SIZE * SIZE) {
            data[top] = g;
            top++;
        }
    }
    /*
    remove an element from top and return a pointer point to the element.
    If list is empty, return NULL.
    */
    Grid *removeElement() {
        if (top == 0)   
            return NULL;
        else {
            top--;
            return data[top];
        }
    }
    void printPath() {
        for (int j = 1; j < top; ++j) {
            if (data[j] == data[j - 1] -> getDir(UP))
                cout << "UP\n";
            else if (data[j] == data[j - 1] -> getDir(DOWN))
                cout << "DOWN\n";
            else if (data[j] == data[j - 1] -> getDir(LEFT))
                cout << "LEFT\n";
            else if (data[j] == data[j - 1] -> getDir(RIGHT))
                cout << "RIGHT\n";
        }
    }
private:
    Grid *data[SIZE * SIZE];
    int top;
};

class Maze {
public:
    Maze() {
        initMaze(SIZE);
    }
    /*
    function initMaze
    Alocate a 2-D link list with s * s sizes as the map of maze.
    Inside the maze enery gird with state 0 represent empty space and 1 represent wall.
    The gird in left top is start point and right bottom is finish point.
    Randomly generate 20% wall in the maze.
    Make sure start point and finish point are 0

    動態配置一個二維的鏈結串列，大小是 s * s，用這個鏈結串列表示迷宮的地圖
    節點中 0 的值表示可以移動的空間， 1 表示牆壁 
    左上角的位置表示起點，右下角的位置表示終點
    請在迷宮中加入 20% 的牆壁 
    然後確定起點跟終點都是可以移動的位置 
    */
    void initMaze(int s) {
        srand(time(NULL));
        maze = new Grid[s * s];
        int w = s * s * 0.2;
        for (int i = 0; i < s * s; ++i)
            maze[i].setState(0);
        while (w > 0) {
            int k = rand() % (s * s);
            if (k == 0 || k == SIZE * SIZE - 1) continue;
            if (maze -> getState() != 1) {
                maze[k].setState(1);
                w--;
            }
        }
        for (int i = 0; i < s * s; ++i) {
            if (i >= s)
                maze[i].setDir(UP, &maze[i - s]);
            if (i < s * s - s)
                maze[i].setDir(DOWN, &maze[i + s]);
            if (i % s != 0)
                maze[i].setDir(LEFT, &maze[i - 1]);
            if ((i + 1) % s != 0)
                maze[i].setDir(RIGHT, &maze[i + 1]);
        }
    }
    /*
    function getPath
    This function will find a path between start point and finish point.
    Return a list content the path information inside.
    If there is no path between two point then the list will be empty.

    這個函數會找到起點到終點間的一條路徑
    回傳一個 list 包含著路徑的資訊
    如果找不到路徑的話 list 就會是空的 
    */
    List *getPath() {
        if (maze[0].getState() == 1 || maze[(SIZE * SIZE) - 1].getState() == 1)
            return NULL;
        List *path = new List();
        bool vis[SIZE * SIZE];
        for (int i = 0; i < SIZE * SIZE; ++i) 
            vis[i] = false;
        if (dfs(0, vis, path))
            return path;
        else {
            delete path;
            return NULL;
        }
    }
    bool dfs(int p, bool vis[], List *path) {
        if (p < 0 || p >= SIZE * SIZE || maze[p].getState() == 1 || vis[p]) 
            return false;
        if (p == SIZE * SIZE - 1) {
            path -> addElement(&maze[p]);
            return true;
        }
        vis[p] = true;
        path -> addElement(&maze[p]);
        int dir[4] = {-SIZE, SIZE, -1, 1};
        for (int i = 0; i < 4; ++i) {
            int newP = p + dir[i];
            if (i == LEFT && p % SIZE == 0) continue;
            if (i == RIGHT && (p + 1) % SIZE == 0) continue;
            if (dfs(newP, vis, path))
                return true;
        }
        path -> removeElement();
        return false;
    }
    void printMaze() {
        Grid *j = maze, *k;
        while (j != NULL) {
            k = j;
            while (k != NULL) {
                cout << k -> getState();
                k = k -> getDir(RIGHT); 
            }
            cout << endl;
            j = j -> getDir(DOWN);
        }
    }
private:
    Grid *maze;
};

int main() {
    Maze *maze = new Maze();
    maze -> printMaze();
    List *p = maze -> getPath();
    if (p != NULL)
        p -> printPath();
    else
        return 0;
}
