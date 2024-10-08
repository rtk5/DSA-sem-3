// Write a C program to construct a binary search tree(BST), perform level order traversal and print the elements in the same order.

// Input Format

// First line has number of elements to be inserted in the BST(n)
// Next ‘n’ lines have the elements to be inserted
// Constraints

// The input should always represent a valid binary search tree.
// Output Format

// Print the elements of the BST in level order traversal, with each element separated by a space
// Sample Input 0

// 6
// 4
// 3
// 6
// 1
// 2
// 5
// Sample Output 0

// 4 3 6 1 5 2


#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Node structure for the binary tree
typedef struct node {
    int info;
    struct node* left;
    struct node* right;
} NODE;

// Tree structure containing the root of the tree
typedef struct tree {
    NODE *root;
} TREE;

// Initializes the Binary Search Tree to be empty
void initTree(TREE *pt) {
    pt->root = NULL;
}

// Creates a new node with the given value
NODE* createNode(int ele) {
    NODE *newNode = (NODE*)malloc(sizeof(NODE));
    newNode->info = ele;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Inserts elements into the BST
void constructTree(TREE *pt, int ele) {
    NODE *newNode = createNode(ele);
    if (pt->root == NULL) {
        pt->root = newNode;
        return;
    }
    
    NODE *current = pt->root, *parent = NULL;
    while (current != NULL) {
        parent = current;
        if (ele < current->info) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    
    if (ele < parent->info) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
}

// Function to perform level order traversal
void levelOrder(TREE *pt) {
    if (pt->root == NULL) {
        return;
    }

    NODE *queue[MAX]; // Queue to hold the nodes
    int front = 0, rear = 0;

    queue[rear++] = pt->root;

    while (front < rear) {
        NODE *current = queue[front++];

        printf("%d ", current->info); // Print the current node's data

        if (current->left != NULL) {
            queue[rear++] = current->left; // Add left child to the queue
        }
        if (current->right != NULL) {
            queue[rear++] = current->right; // Add right child to the queue
        }
    }
}

// Destroys all nodes in the BST and frees memory
void destroyTree(TREE *pt) {
    NODE *current = pt->root;
    if (current == NULL) {
        return;
    }

    NODE *stack[MAX];
    int top = -1;

    // Post-order traversal to destroy the tree
    while (current != NULL || top != -1) {
        while (current != NULL) {
            if (current->right) {
                stack[++top] = current->right;
            }
            stack[++top] = current;
            current = current->left;
        }

        current = stack[top--];

        if (current->right && top != -1 && stack[top] == current->right) {
            top--;
            stack[++top] = current;
            current = current->right;
        } else {
            free(current);
            current = NULL;
        }
    }

    pt->root = NULL;
}

int main() {
    TREE tobj;
    initTree(&tobj);

    int n, ele;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &ele);
        constructTree(&tobj, ele);
    }

    levelOrder(&tobj);
    printf("\n");

    destroyTree(&tobj);

    return 0;
}
