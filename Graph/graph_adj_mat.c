#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int vertex;
    int **adjMatrix;
} GRAPH;

void create_adjMatrix(GRAPH *g) {
    int from, to;

    printf("Enter the number of vertices: ");
    scanf("%d", &g->vertex);

    // Allocate memory for the adjacency matrix
    g->adjMatrix = (int **)malloc((g->vertex + 1) * sizeof(int *));
    for (int i = 0; i <= g->vertex; i++) {
        g->adjMatrix[i] = (int *)malloc((g->vertex + 1) * sizeof(int));
    }

    // Initialize the adjacency matrix
    for (int i = 1; i <= g->vertex; i++) {
        g->adjMatrix[0][i] = i;
        g->adjMatrix[i][0] = i;
        for (int j = 1; j <= g->vertex; j++) {
            g->adjMatrix[i][j] = 0;
        }
    }

    // Accept edges from user
    while (1) {
        printf("Enter the from and to vertices (enter 0 0 to stop): ");
        scanf("%d %d", &from, &to);
        
        if (from == 0 && to == 0) {
            break;
        }
        
        if (from > 0 && from <= g->vertex && to > 0 && to <= g->vertex) {
            g->adjMatrix[from][to] = 1;
        } else {
            printf("Invalid vertices!\n");
        }
    }
}

void print_adjMatrix(GRAPH *g) {
    printf("\nAdjacency Matrix:\n");
    for (int i = 1; i <= g->vertex; i++) {
        for (int j = 1; j <= g->vertex; j++) {
            printf("%d ", g->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

void free_adjMatrix(GRAPH *g) {
    for (int i = 0; i <= g->vertex; i++) {
        free(g->adjMatrix[i]);
    }
    free(g->adjMatrix);
}

int main() {
    GRAPH g;
    create_adjMatrix(&g);
    print_adjMatrix(&g);
    free_adjMatrix(&g);
    return 0;
}
