/*You are a robot navigating through a maze represented as a 2D grid. The maze consists of open cells and walls. You start at the top-left corner and need to reach the bottom-right corner.

Write a recursive function to find if there is a path from the start to the destination.

Open cells are denoted by 0.

Walls are denoted by 1.

You can move up, down, left, or right, but not diagonally.

Sample Input 1

3 3

0 0 0

1 1 0

0 0 0

Sample Output 1

YES

Sample Input 2

3 3

0 1 0

1 1 0

0 1 0

Sample Output 2

NO

Input Format

A string s

Constraints

Print them in lexical order

Output Format

Print all permutations of the string, each on a new line.*/




#include <stdio.h>
#define N 100
#define M 100

int solveMaze(int maze[N][M], int x, int y, int n, int m, int visited[N][M]) {
    if (x < 0 || y < 0 || x >= n || y >= m || maze[x][y] == 1 || visited[x][y] == 1) {
        return 0;
    }
    
    if (x == n-1 && y == m-1) {
        return 1;
    }
    
    visited[x][y] = 1;
    
    if (solveMaze(maze, x, y+1, n, m, visited)) {
        return 1;
    }
    if (solveMaze(maze, x+1, y, n, m, visited)) {
        return 1;
    }
    if (solveMaze(maze, x, y-1, n, m, visited)) {
        return 1;
    }
    if (solveMaze(maze, x-1, y, n, m, visited)) {
        return 1;
    }
    
    visited[x][y] = 0;
    
    return 0;
}

int main() {
    int n, m;
    
    scanf("%d %d", &n, &m);
    
    int maze[N][M];
    int visited[N][M] = {0};
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &maze[i][j]);
        }
    }
    
    if (solveMaze(maze, 0, 0, n, m, visited)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
    
    return 0;
}