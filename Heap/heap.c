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
    int t = *a;
    *a = *b;
    *b = t;
}

void insert_TopDown(NODE *h, int data) {
    int c, p;
    h->heap[++(h->heapsize)] = data;
    c = h->heapsize;
    p = c / 2;
    while (h->heap[p] < h->heap[c]) {
        swap(&h->heap[p], &h->heap[c]);
        c = p;
        p = c / 2;
    }
}

void insert_BottomUp(NODE *h) {
    int p, c;
    for (int i = h->heapsize / 2; i >= 1; i--) {
        p = i;
        c = 2 * p;
        while (c <= h->heapsize) {
            if (c + 1 <= h->heapsize && h->heap[c + 1] > h->heap[c])
                c++;
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

int deleteElement(NODE *h) {
    if (h->heapsize == 0) {
        printf("Heap is empty!\n");
        return -1;
    }
    int deletedValue = h->heap[1];
    h->heap[1] = h->heap[h->heapsize--];
    
    int p = 1, c = 2 * p;
    while (c <= h->heapsize) {
        if (c + 1 <= h->heapsize && h->heap[c + 1] > h->heap[c])
            c++;
        if (h->heap[p] < h->heap[c]) {
            swap(&h->heap[p], &h->heap[c]);
            p = c;
            c = 2 * p;
        } else {
            break;
        }
    }
    return deletedValue;
}

int main() {
    NODE heap;
    init(&heap);

    insert_TopDown(&heap, 20);
    insert_TopDown(&heap, 15);
    insert_TopDown(&heap, 30);
    insert_TopDown(&heap, 40);

    display(&heap);

    printf("Deleted Element: %d\n", deleteElement(&heap));
    display(&heap);

    insert_BottomUp(&heap);
    display(&heap);

    return 0;
}
