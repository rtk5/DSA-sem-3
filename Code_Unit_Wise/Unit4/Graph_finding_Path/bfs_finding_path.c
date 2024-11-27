
#include<stdio.h>
#include "Graph_Adj_mat.c"  // Using adjacency matrix for BFS
#include<stdbool.h>

void bfs(int start, int destination, GRAPH *g) {
    int queue[MAX], front = 0, rear = 0;
    int visited[MAX] = {0};
    int parent[MAX];
    bool found = false;

    queue[rear++] = start;
    visited[start] = 1;
    parent[start] = -1;

    while (front < rear) {
        int current = queue[front++];
        if (current == destination) {
            found = true;
            break;
        }
        for (int i = 1; i <= g->vertex; i++) {
            if (g->adjMatrix[current][i] && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
                parent[i] = current;
            }
        }
    }

    if (found) {
        printf("Path found: ");
        int path[MAX], path_index = 0;
        int crawl = destination;

        // Trace the path from destination to start using parent array
        while (crawl != -1) {
            path[path_index++] = crawl;
            crawl = parent[crawl];
        }

        // Print the path in the correct order from start to destination
        for (int i = path_index - 1; i >= 0; i--) {
            printf("%d ", path[i]);
        }
        printf("\n");
    } else {
        printf("No path found from %d to %d\n", start, destination);
    }
}

int main() {
    GRAPH g;
    int start, destination;
    create_adjMatrix(&g);  // Initialize graph

    printf("Enter start and destination vertices: ");
    scanf("%d %d", &start, &destination);
    bfs(start, destination, &g);

    return 0;
}
