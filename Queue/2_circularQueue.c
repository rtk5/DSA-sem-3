#include <stdio.h>
#include <stdlib.h>

#define QUE_SIZE 5

int q[QUE_SIZE];
int rear = -1, front = 0, count = 0;

void InsertQ(int item)
{
    if (count == QUE_SIZE)
    {
        printf("Overflow\n");
        return;
    }
    rear = (rear + 1) % QUE_SIZE;
    q[rear] = item;
    count++;
}

int DeleteQ()
{
    int item;
    if (count == 0)
        return -1;
    item = q[front];
    front = (front + 1) % QUE_SIZE;
    count--;
    return item;
}

void Display()
{
    if(count == 0) {
        printf("Empty queue\n");
        return;
    }
    printf("Contents of queue:\n");
    int i, tempFront = front;
    for (i = 0; i < count; i++) {
        printf("%d\n", q[tempFront]);
        tempFront = (tempFront + 1) % QUE_SIZE;
    }
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