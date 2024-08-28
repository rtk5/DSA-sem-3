#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 4

int top = -1;
int s[STACK_SIZE];

int push(int item) {
    if (top == STACK_SIZE - 1) {
        printf("Stack is full\n");
        return -1;
    }
    s[++top] = item;
    return 0;
}

int pop() {
        if (top == -1) {
        printf("Stack is empty\n");
        return -1;
    }
    return s[top--];
}

void display() {
    if (top == -1) {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack elements are:\n");
    for (int i = top; i >= 0; i--) {
        printf("%d\n", s[i]);
    }
}

// int main() {
//     push(10);
//     push(20);
//     push(30);
//     push(40);
//     display();
//     printf("Popped item: %d\n", pop());
//     display();
//     return 0;
// }

void main() {
    int choice;
    int item;
    while(1) {
        printf("\n1. Push\n");
        printf("2. Pop\n");
        printf("3. Display List\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter the item to insert: ");
                scanf("%d", &item);
                push(item);
                break;
            case 2:
                printf("Popped item: %d\n", pop());
                break;
            case 3:
                display();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}
