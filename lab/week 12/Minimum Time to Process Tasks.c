// In a data center, there are N tasks that need to be processed, where each task i takes tasks[i] units of time to complete. You have P identical processors available to process these tasks. Each processor can only process one task at a time, and once it starts processing a task, it must complete it before starting another task. Tasks can be assigned to processors in any order. Write a function that returns the minimum possible time needed to process all tasks, assuming optimal task assignment to processors.

// Input Format

// tasksSize: Size of the tasks array
// processors: Number of available processors
// tasks[]: Array of integers where tasks[i] represents the time taken by task i
// Constraints

// 1 ≤ tasksSize ≤ 10^5
// 1 ≤ processors ≤ 10^4
// 1 ≤ tasks[i] ≤ 10^4
// Output Format

// Return an integer representing the minimum time needed to process all tasks
// Sample Input 0

// 5
// 2
// 3 1 4 1 5
// Sample Output 0

// 7

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Min heap implementation
typedef struct {
    int* arr;
    int size;
    int capacity;
} MinHeap;

// Create new min heap
MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->arr = (int*)malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

// Helper functions for heap operations
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(MinHeap* heap, int idx) {
    while (idx > 0 && heap->arr[idx] < heap->arr[(idx - 1) / 2]) {
        swap(&heap->arr[idx], &heap->arr[(idx - 1) / 2]);
        idx = (idx - 1) / 2;
    }
}

void heapifyDown(MinHeap* heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->arr[left] < heap->arr[smallest]) {
        smallest = left;
    }

    if (right < heap->size && heap->arr[right] < heap->arr[smallest]) {
        smallest = right;
    }

    if (smallest != idx) {
        swap(&heap->arr[idx], &heap->arr[smallest]);
        heapifyDown(heap, smallest);
    }
}

// Insert element into heap
void insert(MinHeap* heap, int val) {
    if (heap->size == heap->capacity) {
        printf("Heap is full \n");
        return;
    }
    heap->arr[heap->size] = val;
    heap->size++;
    heapifyUp(heap, heap->size - 1);
}

// Extract minimum element
int extractMin(MinHeap* heap) {
    if (heap->size == 0) {
        return INT_MAX;
    }
    int minVal = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;
    heapifyDown(heap, 0);
    return minVal;
}

// Main logic to compute minimum processing time
int minProcessingTime(int* tasks, int tasksSize, int processors) {
    MinHeap* heap = createMinHeap(processors);
    
    // Initialize each processor to zero
    for (int i = 0; i < processors; i++) {
        insert(heap, 0);
    }

    // Sort tasks in descending order
    for (int i = 0; i < tasksSize - 1; i++) {
        for (int j = i + 1; j < tasksSize; j++) {
            if (tasks[i] < tasks[j]) {
                int temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }
        }
    }

    // Assign tasks to processors
    for (int i = 0; i < tasksSize; i++) {
        int minTime = extractMin(heap);  // Get the processor with the minimum load
        insert(heap, minTime + tasks[i]);  // Assign task to that processor
    }

    // Find the maximum load after all tasks are assigned
    int result = 0;
    for (int i = 0; i < processors; i++) {
        int time = extractMin(heap);  // Extract final load for each processor
        if (time > result) {
            result = time;  // Track the max time across all processors
        }
    }

    // Free heap resources
    free(heap->arr);
    free(heap);
    return result;
}


// Main function with user input
int main() {
    int tasksSize, processors;

    // Get number of tasks
    scanf("%d", &tasksSize);

    // Get number of processors
    scanf("%d", &processors);

    // Dynamically allocate array for tasks
    int* tasks = (int*)malloc(tasksSize * sizeof(int));
    if (tasks == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    for (int i = 0; i < tasksSize; i++) {
        scanf("%d", &tasks[i]);
    }

    // Calculate and display result
    int result = minProcessingTime(tasks, tasksSize, processors);
    printf("%d\n", result);

    // Clean up
    free(tasks);
    return 0;
}