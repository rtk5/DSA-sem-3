#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 10

typedef struct treeNode {
    int utype; // 1 for operand, 2 for operator
    union {
        char operater; // operator
        float operand; // operand
    } u;
    struct treeNode *left;
    struct treeNode *right;
} NODE;

static int top = -1;

void push(NODE* nn, NODE *stack[]) {
    if (top < MAX - 1) {
        stack[++top] = nn;
    } else {
        printf("STACK FULL\n");
    }
}

NODE* pop(NODE *stack[]) {
    if (top == -1) {
        printf("STACK EMPTY\n");
        return NULL;
    }
    return stack[top--];
}

NODE* construct(char exp[]) {
    NODE *nn, *stack[MAX];
    int i = 0;

    while (exp[i]) {
        if (isdigit(exp[i])) {
            nn = (NODE*)malloc(sizeof(NODE));
            nn->utype = 1; // operand
            nn->u.operand = exp[i] - '0'; // Convert char to float
            nn->left = NULL;
            nn->right = NULL;
            push(nn, stack);
        } else {
            nn = (NODE*)malloc(sizeof(NODE));
            nn->utype = 2; // operator
            nn->u.operater = exp[i];
            nn->right = pop(stack);
            nn->left = pop(stack);
            if (nn->right == NULL || nn->left == NULL) {
                printf("Invalid expression\n");
                free(nn);
                return NULL;
            }
            push(nn, stack);
        }
        i++;
    }
    return pop(stack);
}

void inorder(NODE *bst) {
    if (bst != NULL) {
        inorder(bst->left);
        if (bst->utype == 1) 
            printf("%g ", bst->u.operand);
        else
            printf("%c ", bst->u.operater);
        inorder(bst->right);
    }
}

float calculate(float x, char op, float y) {
    float res;
    switch (op) {
        case '+':
            res = x + y;
            break;
        case '-':
            res = x - y;
            break;
        case '*':
            res = x * y;
            break;
        case '/':
            if (y != 0)
                res = x / y;
            else {
                printf("Division by zero error\n");
                exit(1);
            }
            break;
        default:
            printf("Invalid operator \n");
            exit(1);
    }
    return res; // Correctly return the result
}

float evaluate(NODE *bst) {
    if (bst->utype == 1)
        return bst->u.operand;

    float x = evaluate(bst->left);
    float y = evaluate(bst->right);
    return calculate(x, bst->u.operater, y); // Correct operand order
}

void freeTree(NODE *node) {
    if (node) {
        freeTree(node->left);
        freeTree(node->right);
        free(node);
    }
}

int main() {
    NODE *bst;
    char exp[MAX] = "567*+8-"; // Postfix expression
    bst = construct(exp);

    if (bst == NULL) {
        printf("Failed to construct tree\n");
        return 1;
    }

    printf("In-order traversal: ");
    inorder(bst);
    printf("\n");

    printf("Evaluation result: %g\n", evaluate(bst));

    // Free allocated memory
    freeTree(bst);

    return 0;
}
