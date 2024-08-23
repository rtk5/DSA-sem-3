#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int info;
    struct node *rlink;
    struct node *llink;
} *NODE;

NODE getNode()
{
    NODE temp = (NODE)malloc(sizeof(struct node));
    if (temp == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    return temp;
}

NODE insert_front(int item, NODE head)
{
    NODE temp = getNode();
    temp->info = item;

    if (head == NULL)
    {
        temp->llink = temp->rlink = NULL;
        head = temp;
    }
    else
    {
        temp->llink = NULL;
        temp->rlink = head;
        head->llink = temp;
        head = temp;
    }
    return head;
}

NODE insert_rear(int item, NODE head)
{
    NODE temp = getNode();
    temp->info = item;
    temp->rlink = NULL;

    if (head == NULL)
    {
        temp->llink = NULL;
        head = temp;
    }
    else
    {
        NODE cur = head;
        while (cur->rlink != NULL)
        {
            cur = cur->rlink;
        }
        cur->rlink = temp;
        temp->llink = cur;
    }
    return head;
}

NODE insert_pos(int item, int pos, NODE head)
{
    if (head == NULL && pos != 1)
    {
        printf("Invalid position\n");
        return head;
    }
    if (pos == 1)
    {
        return insert_front(item, head);
    }

    int count = 1;
    NODE prev = NULL, cur = head;

    while (cur != NULL && count != pos)
    {
        prev = cur;
        cur = cur->rlink;
        count++;
    }

    if (count == pos)
    {
        NODE temp = getNode();
        temp->info = item;
        temp->rlink = cur;
        temp->llink = prev;

        if (prev != NULL)
        {
            prev->rlink = temp;
        }
        if (cur != NULL)
        {
            cur->llink = temp;
        }
    }
    else
    {
        printf("Position out of bounds\n");
    }

    return head;
}

void display(NODE head)
{
    NODE current = head;
    if (current == NULL)
    {
        printf("List is empty.\n");
        return;
    }
    printf("Linked List: ");
    while (current != NULL)
    {
        printf("%d -> ", current->info);
        current = current->rlink;
    }
    printf("NULL\n");
}

NODE delete_front(NODE head) {
    if (head == NULL) {
        printf("List is empty\n");
        return NULL;
    }
    NODE next = head->rlink;
    free(head);
    if (next != NULL) {
        next->llink = NULL;
    }
    return next;
}

NODE delete_rear(NODE head) {
    if (head == NULL) {
        printf("List is empty\n");
        return NULL;
    }
    NODE cur = head;
    if (cur->rlink == NULL) {
        free(head);
        return NULL; 
    }
    while (cur->rlink != NULL) {
        cur = cur->rlink;
    }
    NODE prev = cur->llink;
    free(cur);
    prev->rlink = NULL;

    return head;
}



int main()
{
    NODE head = NULL;
    int choice, item, pos;

    while (1)
    {
        printf("\n1. Insert at Front\n");
        printf("2. Insert at Rear\n");
        printf("3. Insert at Position\n");
        printf("6. Detete at front end\n");
        printf("7. Detete at rear end\n");
        printf("4. Display List\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter the item to insert at front: ");
            scanf("%d", &item);
            head = insert_front(item, head);
            break;
        case 2:
            printf("Enter the item to insert at rear: ");
            scanf("%d", &item);
            head = insert_rear(item, head);
            break;
        case 3:
            printf("Enter the item and position it has to be inserted at: ");
            scanf("%d %d", &item, &pos);
            head = insert_pos(item, pos, head);
            break;
        case 6:
            head = delete_front(head);
            break;
        case 7:
            head = delete_rear(head);
            break;
        case 4:
            display(head);
            break;
        case 5:
            exit(0);
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}
