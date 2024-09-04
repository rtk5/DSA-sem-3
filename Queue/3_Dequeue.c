#include <stdio.h>

#define MAX 5

int deque[MAX];
int front = -1, rear = -1;

int isFull() {
    return ((front == 0 && rear == MAX - 1) || (front == rear + 1));
}

int isEmpty() {
    return (front == -1);
}

void insertFront(int key) {
    if (isFull()) {
        printf("Overflow\n");
        return;
    }
    if (front == -1) {
        front = 0;
        rear = 0;
    } else if (front == 0) {
        front = MAX - 1;
    } else {
        front = front - 1;
    }
    deque[front] = key;
    printf("Inserted %d at the front\n", key);
}

void insertRear(int key) {
    if (isFull()) {
        printf("Overflow\n");
        return;
    }
    if (front == -1) {
        front = 0;
        rear = 0;
    } else if (rear == MAX - 1) {
        rear = 0;
    } else {
        rear = rear + 1;
    }
    deque[rear] = key;
    printf("Inserted %d at the rear\n", key);
}

void deleteFront() {
    if (isEmpty()) {
        printf("Queue Underflow\n");
        return;
    }
    printf("Deleted %d from the front\n", deque[front]);
    if (front == rear) {
        front = -1;
        rear = -1;
    } else if (front == MAX - 1) {
        front = 0;
    } else {
        front = front + 1;
    }
}

void deleteRear() {
    if (isEmpty()) {
        printf("Queue Underflow\n");
        return;
    }
    printf("Deleted %d from the rear\n", deque[rear]);
    if (front == rear) {
        front = -1;
        rear = -1;
    } else if (rear == 0) {
        rear = MAX - 1;
    } else {
        rear = rear - 1;
    }
}

void display() {
    if (isEmpty()) {
        printf("Deque is empty\n");
        return;
    }
    printf("Deque elements are: ");
    int i = front;
    if (front <= rear) {
        while (i <= rear) {
            printf("%d ", deque[i++]);
        }
    } else {
        while (i <= MAX - 1) {
            printf("%d ", deque[i++]);
        }
        i = 0;
        while (i <= rear) {
            printf("%d ", deque[i++]);
        }
    }
    printf("\n");
}

int main() {
    int choice, key;

    while (1) {
        printf("\n1) Insert at front\n2) Insert at rear\n3) Delete from front\n4) Delete from rear\n5) Display\n6) Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter the element to insert at front: ");
            scanf("%d", &key);
            insertFront(key);
            break;
        case 2:
            printf("Enter the element to insert at rear: ");
            scanf("%d", &key);
            insertRear(key);
            break;
        case 3:
            deleteFront();
            break;
        case 4:
            deleteRear();
            break;
        case 5:
            display();
            break;
        case 6:
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
