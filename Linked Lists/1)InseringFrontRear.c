#include<stdio.h>
#include<stdlib.h>

struct node {
    int info;
    struct node * link;
};
typedef struct node * NODE;

NODE getNode() {
    NODE temp;
    temp = (NODE)malloc(sizeof(struct node));
    if( temp == NULL) {
        printf("Memory allotment failed");
        exit(0);
    }
    return temp;
}

NODE in_front(int item, NODE first) {
    NODE temp = getNode();
    temp -> info = item;
    temp -> link = first;
    if(first == NULL) {
        temp -> link = NULL;
        first = temp;
    }
    first = temp;
    return first;
}

NODE in_rear(int item, NODE first) {
    NODE temp = getNode();
    temp -> info = item;
    temp -> link = NULL;
    if(first == NULL) {
        return temp;
    }
    NODE current;
    current = first;
    while( current -> link != NULL) {
        current = current -> link;
    }
    current -> link = temp;
    return first;
}

void display(NODE first) {
    NODE current = first;
    if (current == NULL) {
        printf("List is empty.\n");
        return;
    }
    printf("Linked List: ");
    while (current != NULL) {
        printf("%d -> ", current->info);
        current = current->link;
    }
    printf("NULL\n");
}
NODE in_pos(int item, int pos, NODE first) {
    NODE temp = getNode();
    NODE prev,cur;
    temp -> info = item;
    if(first==NULL)
    {
    printf("invalid position/list is empty");
    return first;
    }
    if(pos==1) {
        temp -> link = first;
        return temp;
    }
    int count = 1;
    count =1;
    prev = NULL;
    cur = first;
}
// int main() {
//      NODE first = NULL;  

//     first = in_front(10, first);
//     first = in_front(20, first);
//     first = in_front(30, first);

//     printf("After inserting elements at the front:\n");
//     display(first);

//     first = in_rear(40, first);
//     first = in_rear(50, first);
//     first = in_rear(60, first);

//     // Display the list
//     printf("After inserting elements at the rear:\n");
//     display(first);

//     return 0;
// }

void main() {
    NODE first = NULL;
    int choice, item;

    while(1) {
        printf("\n1. Insert at Front\n");
        printf("2. Insert at Rear\n");
        printf("3. Display List\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter the item to insert at front: ");
                scanf("%d", &item);
                first = in_front(item, first);
                break;
            case 2:
                printf("Enter the item to insert at rear: ");
                scanf("%d", &item);
                first = in_rear(item, first);
                break;
            case 3:
                display(first);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}