
#include<stdio.h>
#include "Graph_Adj_mat.c"  // Using adjacency matrix for DFS

void dfs(int start, int destination, GRAPH *g, int *visited, int *path, int path_index) {
    visited[start] = 1;
    path[path_index] = start;
    path_index++;

    if (start == destination) {
        printf("Path found: ");
        for (int i = 0; i < path_index; i++) {
            printf("%d ", path[i]);
        }
        printf("\n");
    } else {
        for (int i = 1; i <= g->vertex; i++) {
            if (g->adjMatrix[start][i] && !visited[i]) {
                dfs(i, destination, g, visited, path, path_index);
            }
        }
    }

    path_index--;
    visited[start] = 0;
}

int main() {
    GRAPH g;
    int start, destination;
    create_adjMatrix(&g);  // Initialize graph
    int visited[MAX] = {0};
    int path[MAX];

    printf("Enter start and destination vertices: ");
    scanf("%d %d", &start, &destination);
    dfs(start, destination, &g, visited, path, 0);

    return 0;
}
