/*Write a C code to evaluate a postfix expression using stacks. You are expected to fill in the code for the following functions.

‘pop’ for popping the elements from the stack.

‘push’ for pushing elements into the stack.

‘eval’ for evaluating the given postfix expression.

‘disp’ for printing the result after evaluating the postfix expression.

Sample Input:

231*+9-

Sample Output:

-4

Explanation:

3*1 is evaluated and gives 3.

2+3 is evaluated and gives 5.

5-9 is evaluated and gives -4.

Input Format

Postfix expression

Constraints

Each character in the string should either be numbers from 0-9 or ‘+’ or ‘-’, ‘*’, ‘/’.

0<= strlen(postfix_expression)<=30.

sizeof(stack) = 30.

It is assumed that the size of the expression is always less than the size of the stack.

Output Format

Resultant value after evaluating the postfix expression.

Print “Stack is empty” when you try to pop from an empty stack.

Print “Stack is full” when you try to push into a stack which is full.

Sample Input 0

231*+9-
Sample Output 0

-4
*/



#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 30

int top = -1;
int stack[MAX];

void push(int item);
int pop();
void eval(char postfix[MAX]);
void disp();

int main() {
    char postfix[30];
    scanf("%s", postfix);
    eval(postfix);
    disp();
    return 0;
}

void push(int item) {
    if (top == MAX - 1) {
        printf("Stack is full\n");
        exit(0);
    }
    stack[++top] = item;
}

int pop() {
    if (top == -1) {
        printf("Stack is empty\n");
        exit(0);
    }
    return stack[top--];
}

void eval(char postfix[MAX]) {
    for (int i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];
        if (isdigit(c)) {
            push(c - '0');  
        } else {
            int a = pop();
            int b = pop();
            int result;

            switch (c) {
                case '+': result = b + a; break;
                case '-': result = b - a; break;
                case '*': result = b * a; break;
                case '/': result = b / a; break;
                case '$': result = b ^ a; break;  
                default: printf("Invalid operator: %c\n", c); return;
            }
            push(result);
        }
    }
}

void disp() {
    if (top == -1) {
        printf("Stack is empty\n");
        exit(0);
    }
    for (int i = top; i >= 0; i--) {
        printf("%d\n", stack[i]);
    }
}
