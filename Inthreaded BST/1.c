#include<stdio.h>
#include<stdlib.h>

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
    int lthread;
    int rthread;
} NODE;

NODE* createNode(int data) {
    NODE * nn = (NODE*)malloc(sizeof(NODE));
    nn->data = data;
    nn->lthread = 1;
    nn->rthread = 1;
    nn->left = NULL;
    nn->right = NULL;
    return nn;
}

NODE* insertNode( NODE * root, int data) {
    NODE *t = root, *parent = NULL, *nn;
    nn = createNode(data);

    if(root == NULL ) {
        root = nn;
        return root;
    }

    while (t != NULL ) {
        parent = t;
        if ( data < t-> data) {
            if( t-> lthread == 0)
            t = t-> left;
        else
            break;
        }
        else if (data > t-> data) {
            if(t->rthread == 0)
                t = t->right;
            else
                break;
        }
        
        
    }
}