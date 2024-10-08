/*You are developing a tool to analyse and visualise software dependencies in a large codebase. The project structure is represented as a binary tree, where each node represents a module, and the edges represent dependencies between them. A level-order traversal of this binary tree will help prioritise the modules' loading or updating order based on their dependencies. Your task is to perform a level-order traversal of the project dependency tree and return the nodes at each level in the correct order. This will allow developers to see which modules are dependent on others. Note: returnSize holds the size of the array returned by the Traversal function. The variable rootValue holds the integer value corresponding to the root module.

Input Format

The first line contains an integer N representing the number of nodes in the tree.
The next N lines describe each node in the format:
value left_child right_child, where:
value is the integer identifier of the node.
left_child is the value of the left child or -1 if there is no left child.
right_child is the value of the right child or -1 if there is no right child.
Constraints

_

Output Format

Return an array containing the nodes' values in level-order traversal.
Sample Input 0

7
0 1 2
1 3 4
2 5 6
3 -1 -1
4 -1 -1
5 -1 -1
6 -1 -1
Sample Output 0

0 1 2 3 4 5 6 */


#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

// Structure to represent a tree node
typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} Node;

// Function prototypes
Node* createNode(int value);
int* Traversal(Node* root, int* returnSize);

// Queue data structure for level-order traversal
typedef struct Queue {
    Node* data[MAX_NODES];
    int front;
    int rear;
} Queue;

// Initialize the queue
void initQueue(Queue* q) {
    q->front = 0;
    q->rear = 0;
}

// Check if queue is empty
int isEmpty(Queue* q) {
    return q->front == q->rear;
}

// Enqueue an element
void enqueue(Queue* q, Node* node) {
    q->data[q->rear++] = node;
}

// Dequeue an element
Node* dequeue(Queue* q) {
    return q->data[q->front++];
}

int main() {
    int N;
    scanf("%d", &N);

    Node* nodes[MAX_NODES] = {NULL};
    int rootValue; // Variable to store the root node value

    // Read input and construct the tree
    for (int i = 0; i < N; i++) {
        int value, left_child, right_child;
        scanf("%d %d %d", &value, &left_child, &right_child);

        // Set root value to the first node's value
        if (i == 0) {
            rootValue = value;
        }

        // Create node if it doesn't exist
        if (nodes[value] == NULL) {
            nodes[value] = createNode(value);
        }

        // Set left child
        if (left_child != -1) {
            if (nodes[left_child] == NULL) {
                nodes[left_child] = createNode(left_child);
            }
            nodes[value]->left = nodes[left_child];
        }

        // Set right child
        if (right_child != -1) {
            if (nodes[right_child] == NULL) {
                nodes[right_child] = createNode(right_child);
            }
            nodes[value]->right = nodes[right_child];
        }
    }

    int returnSize;
    int* result = Traversal(nodes[rootValue], &returnSize);

    // Print the resulting array
    for (int i = 0; i < returnSize; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    // Free the allocated memory for the result array
    free(result);

    return 0;
}

// Function to create a new tree node
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function for level-order traversal
int* Traversal(Node* root, int* returnSize) {
    if (root == NULL) {
        *returnSize = 0;
        return NULL;
    }

    // Allocate memory to store the result
    int* result = (int*)malloc(MAX_NODES * sizeof(int));
    int count = 0;

    // Create and initialize a queue for level-order traversal
    Queue q;
    initQueue(&q);

    // Start by enqueuing the root node
    enqueue(&q, root);

    while (!isEmpty(&q)) {
        // Dequeue the front node from the queue
        Node* current = dequeue(&q);
        result[count++] = current->value; // Store the node's value

        // Enqueue the left child if it exists
        if (current->left != NULL) {
            enqueue(&q, current->left);
        }

        // Enqueue the right child if it exists
        if (current->right != NULL) {
            enqueue(&q, current->right);
        }
    }

    *returnSize = count; // Set the return size
    return result; // Return the array containing level-order traversal
}
