
#include<stdio.h>
#include "Graph_Adj_mat.c"  // Using adjacency matrix for DFS
#include<stdbool.h>

// Helper function to perform DFS and count visited nodes
void dfs_visit(int vertex, GRAPH *g, int *visited, int *count) {
    visited[vertex] = 1;
    (*count)++;
    for (int i = 1; i <= g->vertex; i++) {
        if (g->adjMatrix[vertex][i] && !visited[i]) {
            dfs_visit(i, g, visited, count);
        }
    }
}

// Function to check if the graph is connected using DFS
bool dfs_is_connected(GRAPH *g) {
    int visited[MAX] = {0};
    int count = 0;

    dfs_visit(1, g, visited, &count);
    return count == g->vertex;
}

// Helper function for cycle detection using DFS
bool dfs_cycle_helper(int vertex, int parent, GRAPH *g, int *visited) {
    visited[vertex] = 1;

    for (int i = 1; i <= g->vertex; i++) {
        if (g->adjMatrix[vertex][i]) {  // Check for adjacent vertices
            if (!visited[i]) {
                if (dfs_cycle_helper(i, vertex, g, visited)) {
                    return true;
                }
            } else if (i != parent) {  // A back edge indicating a cycle
                return true;
            }
        }
    }
    return false;
}

// Function to detect cycles in the graph using DFS
bool dfs_contains_cycle(GRAPH *g) {
    int visited[MAX] = {0};
    for (int i = 1; i <= g->vertex; i++) {
        if (!visited[i]) {
            if (dfs_cycle_helper(i, -1, g, visited)) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    GRAPH g;
    create_adjMatrix(&g);  // Initialize graph

    if (dfs_is_connected(&g)) {
        printf("The graph is connected.\n");
    } else {
        printf("The graph is not connected.\n");
    }

    if (dfs_contains_cycle(&g)) {
        printf("The graph contains a cycle.\n");
    } else {
        printf("The graph does not contain any cycles.\n");
    }

    return 0;
}
