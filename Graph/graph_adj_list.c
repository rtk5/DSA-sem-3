#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} NODE;

void create_adjList(NODE *l) {
    int v, from, to;
    NODE *t, *nn;

    printf("\nEnter the number of nodes: ");
    scanf("%d", &v);

    // Initialize the first node with number of vertices
    l[0].data = v;
    l[0].next = NULL;

    // Initialize each node in the adjacency list
    for (int i = 1; i <= v; i++) {
        l[i].data = i;
        l[i].next = NULL;
    }

    // Creating edges
    while (1) {
        printf("\nEnter the from and to node (or 0 0 to stop): ");
        scanf("%d %d", &from, &to);
        
        if (from == 0 && to == 0) {
            break;
        }
        
        if (from > 0 && from <= v && to > 0 && to <= v) {
            t = &l[from];
            
            // Traverse to the end of the list
            while (t->next != NULL) {
                t = t->next;
            }
            
            // Allocate a new node and add it to the adjacency list
            nn = (NODE *)malloc(sizeof(NODE));
            if (nn == NULL) {
                printf("Memory allocation failed\n");
                exit(1);
            }
            nn->data = to;
            nn->next = NULL;
            t->next = nn;
        } else {
            printf("Invalid nodes. Please enter nodes between 1 and %d.\n", v);
        }
    }
}

void ListDisplay(NODE *l) {
    NODE *t;
    for (int i = 1; i <= l[0].data; i++) {
        printf("\n%d -> ", l[i].data);
        t = &l[i];
        while (t->next != NULL) {
            t = t->next;
            printf("%d -> ", t->data);
        }
        printf("NULL");
    }
}

int main() {
    int num_nodes;
    printf("Enter the maximum number of nodes for the graph: ");
    scanf("%d", &num_nodes);

    // Allocate memory for the array of nodes
    NODE *adjList = (NODE *)malloc((num_nodes + 1) * sizeof(NODE));
    if (adjList == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    create_adjList(adjList);
    ListDisplay(adjList);

    // Free the allocated memory
    for (int i = 1; i <= adjList[0].data; i++) {
        NODE *current = adjList[i].next;
        while (current != NULL) {
            NODE *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(adjList);

    return 0;
}
