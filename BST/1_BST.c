#include <stdio.h>
#include <stdlib.h>

// define structure
struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
};

// function to create a new BST node
struct Node *newNode(int item)
{
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

// function to insert a new node with the given key
struct Node *insert(struct Node *node, int key)
{
    // if tree is empty, return a new node
    if (node == NULL)
        return newNode(key);

    // if key is already present, return the node
    if (node->key == key)
        return node;

    // otherwise recur down the tree
    // if the key to be inserted is greater than the node's key, insert it in the right subtree
    if (node->key < key)
        node->right = insert(node->right, key);

    // if key to be inserted is smaller than the node's key
    else
        node->left = insert(node->left, key);

    return node;
}

// function to perform inorder traversal of the BST
void inorder(struct Node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

// function to count the total number of nodes in the BST
int count(struct Node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    return count(root->left) + count(root->right) + 1;
}

// function to count the total number of leaf nodes in the BST
int leaf(struct Node *root)
{
    if (root == NULL)
        return 0;
    if (root->left == NULL && root->right == NULL)
        return 1;
    else
        return leaf(root->left) + leaf(root->right);
}

int main()
{
    struct Node *root = newNode(50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    // perform inorder traversal
    printf("Inorder traversal: ");
    inorder(root);
    printf("\n");

    // count and print the total number of nodes
    int totalNodes = count(root);
    printf("Total number of nodes: %d\n", totalNodes);

    // count and print the total number of leaf nodes
    int leafNodes = leaf(root);
    printf("Total number of leaf nodes: %d\n", leafNodes);

    return 0;
}
