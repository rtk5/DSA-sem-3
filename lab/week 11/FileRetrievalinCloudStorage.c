// Imagine you are managing a cloud storage system where files are organised in a binary search tree (BST) structure based on their sizes. Each node in the tree represents a file, and its value corresponds to the file size in megabytes (MB). The left subtree of a node contains files smaller than the node’s file, while the right subtree contains files larger than the node’s file.

// Given the root of the BST and an integer k, return the k-th smallest file size (1-indexed) in the BST.

// Input Format

// The first line contains an integer n, the number of files (nodes) in the BST.
// The next n lines each contain three space-separated integers:
// file_size left_child right_child, where:
// file_size is the size of the file in MB.
// left_child is the size of the left child file (-1 if it doesn't exist).
// right_child is the size of the right child file (-1 if it doesn't exist).
// The last line contains an integer k, representing the k-th smallest file size you want to find.
// Constraints

// 1≤ n ≤1000
// 1≤ file size ≤106
// 1≤ k ≤n
// Output Format

// An integer representing the k-th smallest file size in the BST.
// Sample Input 0

// 5
// 15 10 20
// 10 8 -1
// 20 -1 25
// 8 -1 -1
// 25 -1 -1
// 3
// Sample Output 0

// 15

#include <stdio.h>
#include <stdlib.h>

// Definition of a TreeNode
struct TreeNode {
    int file_size;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to create a new TreeNode
struct TreeNode* createNode(int file_size) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->file_size = file_size;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to find the k-th smallest file size in the BST using an in-order traversal
void inorderTraversal(struct TreeNode* root, int* k, int* result) {
    if (root == NULL || *k <= 0) return;

    // Traverse the left subtree
    inorderTraversal(root->left, k, result);

    // Decrement k and check if we reached the k-th smallest
    (*k)--;
    if (*k == 0) {
        *result = root->file_size;
        return;
    }

    // Traverse the right subtree
    inorderTraversal(root->right, k, result);
}

int kthSmallest(struct TreeNode* root, int k) {
    int result = -1;
    inorderTraversal(root, &k, &result);
    return result;
}

// Function to build the BST based on the input data
struct TreeNode* buildTree(int n, int data[][3]) {
    struct TreeNode* nodes[n];

    // Create all nodes first
    for (int i = 0; i < n; i++) {
        nodes[i] = createNode(data[i][0]);
    }

    // Link nodes according to the given data
    for (int i = 0; i < n; i++) {
        if (data[i][1] != -1) { // left child
            for (int j = 0; j < n; j++) {
                if (data[j][0] == data[i][1]) {
                    nodes[i]->left = nodes[j];
                    break;
                }
            }
        }
        if (data[i][2] != -1) { // right child
            for (int j = 0; j < n; j++) {
                if (data[j][0] == data[i][2]) {
                    nodes[i]->right = nodes[j];
                    break;
                }
            }
        }
    }

    // The root of the tree is the first node
    return nodes[0];
}

int main() {
    int n, k;
    scanf("%d", &n);
    int data[n][3];
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &data[i][0], &data[i][1], &data[i][2]);
    }
    scanf("%d", &k);

    struct TreeNode* root = buildTree(n, data);
    int result = kthSmallest(root, k);
    printf("%d\n", result);

    return 0;
}
