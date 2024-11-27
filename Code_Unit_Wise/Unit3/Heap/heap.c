#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define SIZE 20

typedef struct heap {
    int heap[SIZE];
    int heapsize;
} NODE;

void init(NODE *h) {
    h->heapsize = 0;
    h->heap[0] = INT_MAX;
}

void swap(int *a, int *b) {
    int t;
    t = *a;
    *a = *b;
    *b = t;
}

// Top-down heap construction (insert element one by one)
void insert_TopDown(NODE *h, int data) {
    int c, p;
    h->heap[++(h->heapsize)] = data;  // Insert at the end
    c = h->heapsize;
    p = c / 2;

    // Heapify: Bubble up
    while (h->heap[p] < h->heap[c]) {
        swap(&h->heap[p], &h->heap[c]);
        c = p;
        p = c / 2;
    }
}

// Bottom-up heap construction (construct heap in one go)
void insert_BottomUp(NODE *h) {
    int p, c;
    p = (h->heapsize) / 2;  // Start from the last parent node

    for (int i = p; i >= 1; i--) {
        p = i;
        c = 2 * p;
        while (c <= h->heapsize) {
            if (c + 1 <= h->heapsize && h->heap[c + 1] > h->heap[c])
                c++;  // Find the larger child
            if (h->heap[p] < h->heap[c])
                swap(&h->heap[p], &h->heap[c]);
            else
                break;
            p = c;
            c = 2 * p;
        }
    }
}

void display(NODE *h) {
    if (h->heapsize > 0) {
        printf("\nHeap: ");
        for (int i = 1; i <= h->heapsize; i++)
            printf("%d ", h->heap[i]);
        printf("\n");
    }
}

// Deletion of the root element (max element in max heap)
int deleteElement(NODE *h) {
    int d, c, p;
    d = h->heap[1];  // Get the root (maximum)
    h->heap[1] = h->heap[h->heapsize--];  // Replace with last element
    p = 1;
    c = 2 * p;

    // Heapify: Bubble down
    while (c <= h->heapsize) {
        if (c + 1 <= h->heapsize && h->heap[c + 1] > h->heap[c])
            c++;  // Find the larger child
        if (h->heap[p] < h->heap[c])
            swap(&(h->heap[p]), &(h->heap[c]));
        else
            break;
        p = c;
        c = 2 * p;
    }
    return d;
}

int main() {
    int d, ch;
    NODE *h1, *h2;
    h1 = (NODE*)malloc(sizeof(NODE));
    init(h1);
    h2 = (NODE*)malloc(sizeof(NODE));
    init(h2);

    // Input loop for heap elements
    do {
        printf("\nEnter the data: ");
        scanf("%d", &d);
        h2->heap[++(h2->heapsize)] = d;  // Bottom-up - construct a BT
        insert_TopDown(h1, d);  // Top-down heap insertion
        printf("\nPress 1 to Continue: ");
        scanf("%d", &ch);
    } while (ch == 1);

    // Display top-down heap
    printf("\nTop-down Heap Construction:");
    display(h1);

    // Build and display bottom-up heap
    insert_BottomUp(h2);
    printf("\nBottom-up Heap Construction:");
    display(h2);

    // Priority Queue (Max Heap) using top-down heap
    printf("\nPRIORITY QUEUE - MAX HEAP:\n");
    if (h1->heapsize >= 1) {
        int n = h1->heapsize;
        for (int i = 1; i <= n; i++)
            printf("%d ", deleteElement(h1));
        printf("\n");
    }

    // Free allocated memory
    free(h1);
    free(h2);

    return 0;
}
