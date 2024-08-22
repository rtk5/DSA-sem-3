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

void insert_front(int item, NODE head)
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
        NODE cur;
        cur = head;
        temp->llink = NULL;
        temp->rlink = cur;
        cur->llink = temp;
        head = temp;
    }
}

void insert_rear(int item, NODE head)
{
    NODE temp = getNode();
    temp->info = item;
    temp->rlink = NULL;
    temp->llink = NULL;

    if (head == NULL)
    {
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
}

void insert_pos(int item, int pos, NODE head)
{
    if (head == NULL && pos != 1)
    {
        printf("Invalid position\n");
        return;
    }
    if (pos == 1)
    {
        insert_front(item, head);
    }
    int count = 1;
    NODE prev, cur;
    prev = NULL;
    cur = head;
    while (cur != NULL && count != pos)
    {
        prev = cur;
        cur = cur->rlink;
        count++;
    }
    NODE temp = getNode();
    temp->info = item;
    if (count == pos)
    {
        prev->rlink = temp;
        temp->llink = prev;
        temp->rlink = cur;
        cur->llink = temp
    }
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

void main()
{
    NODE head = NULL;
    int choice, item, pos;

    while (1)
    {
        printf("\n1. Insert at Front\n");
        printf("2. Insert at Rear\n");
        printf("3. Insert at Position\n");
        printf("4. Display List\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter the item to insert at front: ");
            scanf("%d", &item);
            insert_front(item, head);
            break;
        case 2:
            printf("Enter the item to insert at rear: ");
            scanf("%d", &item);
            insert_rear(item, head);
            break;
        case 3:
            printf("Enter the item and position it has to be inserted at: ");
            scanf("%d %d", &item, &pos);
            insert_pos(item, pos, head);
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
}
