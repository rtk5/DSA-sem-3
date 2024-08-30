#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

char s[20];
int top = -1;

void push(char ch) {
    s[++top] = ch;
}

char pop() {
    return s[top--];
}

int precedence(char ch) {
    switch(ch) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '^': return 3;
        case '(': return 0;
        default: return -1; // Default case added for safety
    }
}

void main() {
    char infix[20], postfix[20], ch;
    int i = 0, j = 0;
    printf("Enter the infix expression\n");
    scanf("%s", infix);
    push('(');
    strcat(infix, ")");  // Add closing parenthesis to the infix expression
    
    for (i = 0; i < strlen(infix); i++) {
        ch = infix[i];
        
        if (isalnum(ch)) 
            postfix[j++] = ch;
        else if (ch == '(')
            push(ch);
        else if (ch == ')') {
            while (s[top] != '(') {
                postfix[j++] = pop();
            }
            pop();  // Remove the '(' from the stack
        } else {
            while (precedence(s[top]) >= precedence(ch)) {
                postfix[j++] = pop();
            }
            push(ch);
        }
    }

    postfix[j] = '\0';  // Null-terminate the postfix expression
    printf("Postfix expression is = %s\n", postfix);
}
