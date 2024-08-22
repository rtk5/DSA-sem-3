/*Write a C program that takes 2 polynomials, adds them and evaluate it with an input value(x). If the resultant linked list is empty print -1.

You are required to fill in the code for the following functions:

The ‘input’ function that inputs the terms of the polynomials.

The ‘sum’ function that finds the sum of the polynomials and returns the resulting polynomial.

The ‘eval’ function that evaluates the polynomial with the value x.

The ‘destroy function’ that frees all the nodes in the linked list.

Note: Each node of a linked list for a polynomial stores each term of the polynomial(coefficient, degree). The terms in each polynomial are stored in decreasing order of their powers.

Sample Input:

2 2

2

2 1

3 0

3 1

4 0

Sample Output:

17

Input Format

Number of terms in polynomial 1(m) and polynomial 2(n) separated by a space.

x (value to evaluate the resulting polynomial with)

Coefficient 1 Degree 1

.

.

.

m times

Coefficient 2 Degree 2

.

.

.

n times

Constraints

degree of the polynomial>=0

number of elements>=0

Output Format

sum of the resulting polynomial (if the resulting polynomial is not empty) else -1*/



#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

typedef struct node
{
    int coeff;
    int pow;
    struct node* next;
} node;

void input(node** head, node** tail, int n);
node* sum(node* head1, node* head2);
int eval(node* head, int x);
void destroy(node **head);

int main()
{
    int m = 0;
    int n = 0;
    
    node* head1 = NULL;
    node* head2 = NULL;
    node* tail1 = NULL;
    node* tail2 = NULL;
    
    int x = 0; // value of the variable for evaluation
    
    scanf("%d %d", &m, &n);
    scanf("%d", &x);
    
    input(&head1, &tail1, m);
    input(&head2, &tail2, n);
    
    node *headres = sum(head1, head2);
    
    int res = eval(headres, x);
    
    printf("%d", res);
    destroy(&headres);
    
    return 0;
}

void input(node** head, node** tail, int n) {
    for(int i = 0; i < n; i++)  {
        int coeff, pow;
        scanf("%d %d", &coeff, &pow);
        node* temp = (node*)malloc(sizeof(node));
        temp->coeff = coeff;
        temp->pow = pow;
        temp->next = NULL;
        if(*head == NULL) {
            *head = temp;
            *tail = temp;
        }
        else {
            (*tail)->next = temp;
            *tail = temp;
        }
    }
}

node* sum(node* head1, node* head2) {
    node* headres = NULL;
    node* tailres = NULL;
    while (head1 != NULL && head2 != NULL) {
        int coeff, pow;
        if (head1->pow == head2->pow) {
            coeff = head1->coeff + head2->coeff;
            pow = head1->pow;
            head1 = head1->next;
            head2 = head2->next;
        }
        else if (head1->pow > head2->pow) {
            coeff = head1->coeff;
            pow = head1->pow;
            head1 = head1->next;
        }
        else {
            coeff = head2->coeff;
            pow = head2->pow;
            head2 = head2->next;
        }
        if (coeff != 0){
            node* temp = (node*)malloc(sizeof(node));
            temp->coeff = coeff;
            temp->pow = pow;
            temp->next = NULL;
            if (headres == NULL) {
                headres = temp;
                tailres = temp;
            }
            else {
                tailres->next = temp;
                tailres = temp;
            }
        }
    }

    while (head1 != NULL) {
        node* temp = (node*)malloc(sizeof(node));
        temp->coeff = head1->coeff;
        temp->pow = head1->pow;
        temp->next = NULL;
        if (headres == NULL) {
            headres = temp;
            tailres = temp;
        }
        else {
            tailres->next = temp;
            tailres = temp;
        }
        head1 = head1->next;
    }
    while (head2 != NULL) {
        node* temp = (node*)malloc(sizeof(node));
        temp->coeff = head2->coeff;
        temp->pow = head2->pow;
        temp->next = NULL;
        if (headres == NULL) {
            headres = temp;
            tailres = temp;
        }
        else {
            tailres->next = temp;
            tailres = temp;
        }
        head2 = head2->next;
    }
    if (headres == NULL)  {
        return NULL;
    }
    return headres;
}

int eval(node* head, int x) {
    int result = 0;
    while (head != NULL)
    {
        result += head->coeff * pow(x, head->pow);
        head = head->next;
    }
    return (result == 0 ? -1 : result);
}

void destroy(node **head) {
    while (*head != NULL)
    {
        node* temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}
