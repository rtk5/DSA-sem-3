#include<stdio.h>
#include<stdlib.h>

struct node {
    int info;
    struct node * link;
};

typedef struct node * NODE;
NODE first = NULL;

void push() {           // insert_front
    NODE temp;
    int item;
    temp = (NODE)malloc(sizeof(struct node));
    if(temp == NULL) {
        printf("No memory");
        exit(0);
    }
    printf("Enter the item to be inserted: ");
    scanf("%d",&item);
    temp -> info = item;
    temp -> link = first;
    first = temp;
}

void pop() {            // delete_front
    NODE temp;
    if(first == NULL) {
        printf("List is empty\n");
        return;
    }
    temp = first;
    printf("Item that got deleted is: %d\n", temp -> info);
    first = temp -> link;
    free(temp);
}

void display() {
    NODE temp;
    if(first == NULL) {
        printf("List is empty\n");
        return;
    }
    printf("The contents of the list:    ");
    temp = first;
    while(temp != NULL) {
        printf("%d ", temp -> info);
        temp = temp -> link;
    }
    printf("\n");
}

void main() {
    int ch;
    for(;;) {
        printf("1:push\n");
        printf("2:pop\n");
        printf("3:display\n");
        printf("4:exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        switch(ch) {
            case 1: push();
                    break;
            case 2: pop();
                    break;
            case 3: display();
                    break;
            case 4: exit(0);
                    break;
            default: printf("Invalid choice\n");
        }
    }
}
