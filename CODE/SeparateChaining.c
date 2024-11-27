#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

typedef struct element {
    int rNo;
    char name[30];
    struct element *next;
} NODE;

// Initialize the hash table
void initTable(NODE* ht[SIZE]) {
    for (int i = 0; i < SIZE; i++)
        ht[i] = NULL;
}

// Insert function
void insert(NODE* ht[SIZE], int rNo, char name[30]) {
    int index = rNo % SIZE; // Hash function

    NODE *newNode = malloc(sizeof(NODE));
    newNode->rNo = rNo;
    strcpy(newNode->name, name);
    newNode->next = ht[index];

    ht[index] = newNode;
    printf("Inserted (Roll No: %d, Name: %s)\n", rNo, name);
}

// Delete function
int delete(NODE* ht[SIZE], int rNo) {
    int index = rNo % SIZE; // Hash function

    NODE *p = ht[index];
    NODE *q = NULL;

    while (p != NULL && p->rNo != rNo) {
        q = p;
        p = p->next;
    }
    if (p != NULL) {
        if (q == NULL)
            ht[index] = p->next;
        else
            q->next = p->next;

        free(p);
        printf("Deleted Roll No: %d\n", rNo);
        return 1;
    }
    printf("Roll No %d not found.\n", rNo);
    return 0;
}

// Search function
int search(NODE* ht[SIZE], int rNo, char name[30]) {
    int index = rNo % SIZE; // Hash function
    NODE *p = ht[index];
    while (p != NULL) {
        if (p->rNo == rNo) {
            strcpy(name, p->name);
            return 1;
        }
        p = p->next;
    }
    return 0;
}

// Display function
void display(NODE* ht[SIZE]) {
    printf("Hash Table Contents:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("Index %d: ", i);
        NODE *p = ht[i];
        while (p != NULL) {
            printf("(Roll No: %d, Name: %s) -> ", p->rNo, p->name);
            p = p->next;
        }
        printf("NULL\n");
    }
}

int main() {
    NODE* hashTable[SIZE];
    int choice, rNo;
    char name[30];

    initTable(hashTable);

    while (1) {
        printf("\n1. Insert\n2. Delete\n3. Search\n4. Display\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter roll number and name to insert: ");
                scanf("%d", &rNo);
                scanf("%s", name);
                insert(hashTable, rNo, name);
                break;
            case 2:
                printf("Enter roll number to delete: ");
                scanf("%d", &rNo);
                delete(hashTable, rNo);
                break;
            case 3:
                printf("Enter roll number to search: ");
                scanf("%d", &rNo);
                if (search(hashTable, rNo, name)) {
                    printf("Found: Roll No: %d, Name: %s\n", rNo, name);
                } else {
                    printf("Roll No %d not found.\n", rNo);
                }
                break;
            case 4:
                display(hashTable);
                break;
            case 5:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}
