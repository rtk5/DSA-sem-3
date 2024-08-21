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

NODE insert_front(int item, NODE first) {
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

NODE insert_rear(int item, NODE first) {
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

NODE insert_pos(int item,int pos, NODE first) {
    NODE temp,prev,cur;
    int count;
    temp = getNode();
    temp -> info = item;
    temp -> link = NULL;
    if( first == NULL && (pos == 1)) {
        return temp;
    }
    if(first == NULL) {
        printf("List is empty");
        return first;
    }
    if(pos==1) {
    temp->link=first;
    return temp;
    }
    count=1;
    prev=NULL;
    cur=first;
    while( cur != NULL && count!=pos) {
        prev = cur;
        cur = cur-> link;
        count++;
    }
    if(count == pos) {
        prev -> link = temp;
        temp -> link = cur;
        return first;
    }
    printf("Invalid position\n");
    return first;
}

NODE delete_front(NODE first) {
    if (first == NULL) {
        printf("List is empty.\n");
        return first;
    }
    NODE temp = first;
    first = first->link;
    printf("Deleted item: %d\n", temp->info);
    free(temp);
    return first;
}

NODE delete_rear(NODE first) {
    if (first == NULL) {
        printf("List is empty.\n");
        return first;
    }
    if (first->link == NULL) {
        printf("Deleted item: %d\n", first->info);
        free(first);
        return NULL;
    }
    NODE prev = NULL, current = first;
    while (current->link != NULL) {
        prev = current;
        current = current->link;
    }
    prev->link = NULL;
    printf("Deleted item: %d\n", current->info);
    free(current);
    return first;
}

NODE delete_pos(int pos, NODE first) {
    if (first == NULL) {
        printf("List is empty.\n");
        return first;
    }
    if (pos == 1) {
        return delete_front(first);
    }
    NODE prev = NULL, current = first;
    int count = 1;
    while (current != NULL && count != pos) {
        prev = current;
        current = current->link;
        count++;
    }
    if (current == NULL) {
        printf("Invalid position\n");
        return first;
    }
    prev->link = current->link;
    printf("Deleted item: %d\n", current->info);
    free(current);
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

void main() {
    NODE first = NULL;
    int choice, item, pos;

    while(1) {
        printf("\n1. Insert at Front\n");
        printf("2. Insert at Rear\n");
        printf("3. Insert at Position\n");
        printf("4. Delete from Front\n");
        printf("5. Delete from Rear\n");
        printf("6. Delete from Position\n");
        printf("7. Display List\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter the item to insert at front: ");
                scanf("%d", &item);
                first = insert_front(item, first);
                break;
            case 2:
                printf("Enter the item to insert at rear: ");
                scanf("%d", &item);
                first = insert_rear(item, first);
                break;
            case 3:
                printf("Enter the item and position it has to be inserted at: ");
                scanf("%d %d",&item,&pos);
                first = insert_pos(item, pos, first);
                break;
            case 4:
                first = delete_front(first);
                break;
            case 5:
                first = delete_rear(first);
                break;
            case 6:
                printf("Enter the position to delete: ");
                scanf("%d", &pos);
                first = delete_pos(pos, first);
                break;
            case 7:
                display(first);
                break;
            case 8:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}
