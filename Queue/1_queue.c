#include <stdio.h>
#include <stdlib.h>

#define QUE_SIZE 5

int q[QUE_SIZE]; 
int rear = -1;   
int front = 0;   

void InsertQ(int item)
{
    if (rear == QUE_SIZE - 1)
    {
        printf("Overflow\n");
        return;
    }
    q[++rear] = item;
}

int DeleteQ()
{
    if (front > rear)
    {
        return -1; 
    }
    return q[front++];
}

void Display()
{
    int i;
    if (front > rear)
    {
        printf("Queue empty\n");
        return;
    }

    printf("Contents of the queue:\n");
    for (i = front; i <= rear; i++)
    {
        printf("%d\t", q[i]);
    }
    printf("\n");
}

int main()
{
    int choice, item;

    for (;;)
    {
        printf("1) Insert\n2) Delete\n3) Display\n4) Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter item to be inserted: ");
            scanf("%d", &item);
            InsertQ(item);
            break;

        case 2:
            item = DeleteQ();
            if (item == -1)
                printf("Queue empty\n");
            else
                printf("Item deleted = %d\n", item);
            break;

        case 3:
            Display();
            break;

        case 4:
            exit(0);
            break;

        default:
            printf("Invalid choice\n");
        }
    }

    return 0;
}