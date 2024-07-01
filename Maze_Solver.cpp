#include <iostream>
#include <ctime>
#include <algorithm>

using namespace std;

const int INF = 999999999;
const int MAX_SIZE = 100;

struct Point {
    int x, y;
};

struct Node {
    int dist;
    Point point;
};

bool comparePoints(const Point& a, const Point& b) {
    return a.x == b.x && a.y == b.y;
}

struct Direction {
    int x, y;
};

Direction directions[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

struct Maze {
    int grid[MAX_SIZE][MAX_SIZE];
    int rows, cols;
    Point start, goal;

    Maze(int g[MAX_SIZE][MAX_SIZE], int r, int c) : rows(r), cols(c) {
        copyGrid(g);
        placeStartAndGoal();
    }

    void copyGrid(int g[MAX_SIZE][MAX_SIZE]) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                grid[i][j] = g[i][j];
            }
        }
    }

    bool isValid(int r, int c) {
        return r >= 0 && r < rows && c >= 0 && c < cols && grid[r][c] != 1;
    }

    void placeStartAndGoal() {
        srand(time(0));
        Point borderPoints[MAX_SIZE * 4];
        int borderCount = 0;

        for (int r = 0; r < rows; ++r) {
            if (grid[r][0] == 0) borderPoints[borderCount++] = Point{r, 0};
            if (grid[r][cols - 1] == 0) borderPoints[borderCount++] = Point{r, cols - 1};
        }
        for (int c = 0; c < cols; ++c) {
            if (grid[0][c] == 0) borderPoints[borderCount++] = Point{0, c};
            if (grid[rows - 1][c] == 0) borderPoints[borderCount++] = Point{rows - 1, c};
        }

        do {
            start = borderPoints[rand() % borderCount];
            goal = borderPoints[rand() % borderCount];
        } while (comparePoints(start, goal));

        grid[start.x][start.y] = 2;
        grid[goal.x][goal.y] = 3;
    }

    void print() {
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == 1) {
                    cout << "# ";
                } else if (grid[r][c] == 2) {
                    cout << "S ";
                } else if (grid[r][c] == 3) {
                    cout << "G ";
                } else {
                    cout << ". ";
                }
            }
            cout << endl;
        }
    }

    void printPath(Point path[MAX_SIZE * MAX_SIZE], int pathLength) {
        for (int i = 0; i < pathLength; ++i) {
            if (grid[path[i].x][path[i].y] == 0) {
                grid[path[i].x][path[i].y] = 4;
            }
        }
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == 1) {
                    cout << "# ";
                } else if (grid[r][c] == 2) {
                    cout << "S ";
                } else if (grid[r][c] == 3) {
                    cout << "G ";
                } else if (grid[r][c] == 4) {
                    cout << "* ";
                } else {
                    cout << ". ";
                }
            }
            cout << endl;
        }
    }
};

struct SimpleQueue {
    Node data[MAX_SIZE * MAX_SIZE];
    int front, rear;

    SimpleQueue() : front(0), rear(0) {}

    bool empty() {
        return front == rear;
    }

    void push(Node n) {
        data[rear++] = n;
    }

    Node pop() {
        return data[front++];
    }
};

void dijkstra(Maze &maze, int dist[MAX_SIZE][MAX_SIZE], Point previous[MAX_SIZE][MAX_SIZE]) {
    SimpleQueue pq;

    for (int i = 0; i < maze.rows; ++i) {
        for (int j = 0; j < maze.cols; ++j) {
            dist[i][j] = INF;
            previous[i][j] = Point{-1, -1};
        }
    }

    dist[maze.start.x][maze.start.y] = 0;
    pq.push(Node{0, maze.start});

    while (!pq.empty()) {
        Node node = pq.pop();
        int d = node.dist;
        Point u = node.point;

        if (d > dist[u.x][u.y]) continue;

        for (int k = 0; k < 4; ++k) {
            int nr = u.x + directions[k].x;
            int nc = u.y + directions[k].y;
            if (maze.isValid(nr, nc)) {
                int newDist = d + 1;
                if (newDist < dist[nr][nc]) {
                    dist[nr][nc] = newDist;
                    previous[nr][nc] = u;
                    pq.push(Node{newDist, Point{nr, nc}});
                }
            }
        }
    }
}

int getShortestPath(Maze &maze, Point previous[MAX_SIZE][MAX_SIZE], Point path[MAX_SIZE * MAX_SIZE]) {
    int pathLength = 0;
    Point at = maze.goal;

    while (!(comparePoints(at, Point{-1, -1}))) {
        path[pathLength++] = at;
        if (comparePoints(at, maze.start)) break;
        at = previous[at.x][at.y];
    }

    if (!(comparePoints(path[--pathLength], maze.start))) {
        pathLength = 0;
    } else {
        reverse(path, path + pathLength);
    }
    return pathLength;
}

int main() {
    int grid[MAX_SIZE][MAX_SIZE] = {
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 1, 1, 0, 1, 0, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {1, 1, 0, 1, 0, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    int rows = 9, cols = 10;

    Maze maze(grid, rows, cols);
    maze.print();
    cout << "Solving the maze..." << endl;

    int dist[MAX_SIZE][MAX_SIZE];
    Point previous[MAX_SIZE][MAX_SIZE];
    dijkstra(maze, dist, previous);

    Point path[MAX_SIZE * MAX_SIZE];
    int pathLength = getShortestPath(maze, previous, path);

    if (pathLength == 0) {
        cout << "No path found from start to goal." << endl;
    } else {
        cout << "Path found:" << endl;
        maze.printPath(path, pathLength);
    }

    return 0;
}

