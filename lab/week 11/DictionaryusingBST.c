// You are tasked with implementing a dictionary using a Binary Search Tree (BST) in C. The dictionary will store key-value pairs where both keys and values are integers. The program must support several operations including inserting new key-value pairs, finding the minimum key, removing a key-value pair, retrieving the value associated with a key, updating the value for a key, and displaying the dictionary in sorted order.

// Input Format

// The first input is an integer n, representing the number of operations to perform.

// The next n lines represent the operations:

// 1 key value: Insert a key-value pair.
// 2: Find and print the minimum key in the BST.
// 3 key: Remove the node with the given key.
// 4 key: Get the value of the key.
// 5 key newValue: Update the value of the key.
// 6: Display the key-value pairs in sorted order.
// Constraints

// Key and Value Range:

// The keys and values are non-negative integers.
// 0≤key,value≤10000.
// Number of Operations:

// 1≤n≤1000.
// Output Format

// Insert: Do not print anything.
// Get: Print the value corresponding to the key, or break dont print anything if the key does not exist.
// Remove: Do not print anything.
// Update: Do not print anything.
// Find Minimum: Print the minimum key, or BST is empty if the tree is empty.
// Display: Print key-value pairs in sorted order key,value format, or BST is empty if the tree is empty.
// Sample Input 0

// 8
// 1 20 200
// 1 10 100
// 1 30 300
// 4 10
// 2
// 3 20
// 4 20
// 6
// Sample Output 0

// 100
// 10
// Key not found
// 10,100
// 30,300
// Explanation 0

// Insert 20 with value 200 (1 20 200):
// Inserts key 20 with value 200. Nothing is printed.
// Insert 10 with value 100 (1 10 100):
// Inserts key 10 with value 100. Nothing is printed.
// Insert 30 with value 300 (1 30 300):
// Inserts key 30 with value 300. Nothing is printed.
// Get the value for key 10 (4 10):
// The value for key 10 is 100, so it prints 100.
// Find the minimum key (2):
// The minimum key in the BST is 10, so it prints 10.
// Remove key 20 (3 20):
// Removes the node with key 20. Nothing is printed.
// Get the value for key 20 (4 20):
// Key 20 has been removed, so it prints Key not found.
// Display the BST in sorted order (6):
// The remaining key-value pairs are 10:100 and 30:300.


#include <stdio.h>
#include <stdlib.h>

// Structure for a BST node
struct Node {
    int key;
    int value;
    struct Node* left;
    struct Node* right;
};

// Create a new node
struct Node* createNode(int key, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->value = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Insert a new key-value pair into the BST
struct Node* insert(struct Node* root, int key, int value) {
    if (root == NULL) return createNode(key, value);
    if (key < root->key) {
        root->left = insert(root->left, key, value);
    } else if (key > root->key) {
        root->right = insert(root->right, key, value);
    }
    return root;
}

// Find the node with the minimum key value
struct Node* findMinNode(struct Node* root) {
    struct Node* current = root;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

// Remove a key-value pair from the BST
struct Node* removeNode(struct Node* root, int key) {
    if (root == NULL) return root;
    if (key < root->key) {
        root->left = removeNode(root->left, key);
    } else if (key > root->key) {
        root->right = removeNode(root->right, key);
    } else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        struct Node* temp = findMinNode(root->right);
        root->key = temp->key;
        root->value = temp->value;
        root->right = removeNode(root->right, temp->key);
    }
    return root;
}

// Search for a key in the BST and return its value
int* get(struct Node* root, int key) {
    if (root == NULL) return NULL;
    if (key == root->key) return &root->value;
    if (key < root->key) return get(root->left, key);
    return get(root->right, key);
}

// Update the value for a given key
void update(struct Node* root, int key, int newValue) {
    int* value = get(root, key);
    if (value != NULL) *value = newValue;
}

// In-order traversal to print the dictionary in sorted order
void inOrderTraversal(struct Node* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("%d,%d\n", root->key, root->value);
        inOrderTraversal(root->right);
    }
}

// Free all nodes in the BST
void freeBST(struct Node* root) {
    if (root != NULL) {
        freeBST(root->left);
        freeBST(root->right);
        free(root);
    }
}

int main() {
    struct Node* root = NULL;
    int n;

    // Read the number of operations
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input for number of operations\n");
        exit(EXIT_FAILURE);
    }

    // Process n operations
    for (int i = 0; i < n; i++) {
        int operation;
        if (scanf("%d", &operation) != 1) {
            fprintf(stderr, "Invalid operation code\n");
            exit(EXIT_FAILURE);
        }

        switch (operation) {
            case 1: {
                // Insert operation
                int key, value;
                if (scanf("%d %d", &key, &value) != 2) {
                    fprintf(stderr, "Invalid input for insert operation\n");
                    exit(EXIT_FAILURE);
                }
                root = insert(root, key, value);
                break;
            }
            case 2: {
                // Find minimum key
                struct Node* minNode = findMinNode(root);
                if (minNode != NULL) {
                    printf("%d\n", minNode->key);
                } else {
                    printf("BST is empty\n");
                }
                break;
            }
            case 3: {
                // Remove operation
                int key;
                if (scanf("%d", &key) != 1) {
                    fprintf(stderr, "Invalid input for remove operation\n");
                    exit(EXIT_FAILURE);
                }
                root = removeNode(root, key);
                break;
            }
            case 4: {
                // Get value
                int key;
                if (scanf("%d", &key) != 1) {
                    fprintf(stderr, "Invalid input for get operation\n");
                    exit(EXIT_FAILURE);
                }
                int* value = get(root, key);
                if (value != NULL) {
                    printf("%d\n", *value);
                } else {
                    printf("Key not found\n");
                }
                break;
            }
            case 5: {
                // Update value
                int key, newValue;
                if (scanf("%d %d", &key, &newValue) != 2) {
                    fprintf(stderr, "Invalid input\n");
                    exit(EXIT_FAILURE);
                }
                update(root, key, newValue);
                break;
            }
            case 6: {
                // Display BST
                if (root != NULL) {
                    inOrderTraversal(root);
                } else {
                    printf("BST is empty\n");
                }
                break;
            }
            default:
                fprintf(stderr, "Invalid operation code: %d\n", operation);
                exit(EXIT_FAILURE);
        }
    }

    // Free allocated memory
    freeBST(root);

    return 0;
}
