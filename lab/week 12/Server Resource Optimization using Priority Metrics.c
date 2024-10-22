// In a high-performance computing environment, a server processes a large number of tasks with different priority levels and completion times. The system administrator needs to optimise the server's task management by sorting the task logs based on a combination of priority metrics and processing time. This sorting mechanism helps in identifying bottlenecks and optimising the server's response to critical tasks.

// Each task has two associated metrics:

// Priority Level (P): An integer value where a lower value indicates higher priority.
// Processing Time (T): The time taken (in milliseconds) to complete the task.
// The server must first sort the tasks based on priority level (P), the server should process tasks with higher priority first. If two tasks have the same priority, they should be sorted based on their processing time (T), The task with a lesser processing time will be processed first..

// Given an array of N tasks where each task is represented as a pair (P, T), implement the HeapSort algorithm to sort the array based on priority. If two tasks have the same priority, sort them by processing time.

// Input Format

// The first line contains an integer N which is the number of tasks logged.
// The next N lines contain two integers each, P[i] and T[i] where P[i] is the priority level and T[i] is the processing time of the i-th task.
// Constraints

// The array may contain up to 100,000 tasks.
// Tasks with the same priority level must be sorted by processing time.
// You must implement the HeapSort algorithm directly without using any built-in sorting functions.
// Output Format

// Output N lines, each containing the sorted (P, T) pairs.
// Sample Input 0

// 5
// 2 1000
// 1 300
// 3 400
// 2 600
// 1 200
// Sample Output 0

// (1, 200)
// (1, 300)
// (2, 600)
// (2, 1000)
// (3, 400)

#include <stdio.h>
#include <stdlib.h>

// Structure to store priority and processing time
typedef struct {
    int priority;
    int time;
} Task;

// Function to swap two tasks
void swap(Task* a, Task* b) {
    Task temp = *a;
    *a = *b;
    *b = temp;
}

// Function to heapify a subtree rooted at node i
// n is size of heap
void heapify(Task arr[], int n, int i) {
    int smallest = i; // Initialize smallest as root
    int left = 2 * i + 1; // left child
    int right = 2 * i + 2; // right child

    // If left child is smaller than root
    if (left < n && (arr[left].priority < arr[smallest].priority || 
        (arr[left].priority == arr[smallest].priority && arr[left].time < arr[smallest].time))) {
        smallest = left;
    }

    // If right child is smaller than smallest so far
    if (right < n && (arr[right].priority < arr[smallest].priority || 
        (arr[right].priority == arr[smallest].priority && arr[right].time < arr[smallest].time))) {
        smallest = right;
    }

    // If smallest is not root
    if (smallest != i) {
        swap(&arr[i], &arr[smallest]);

        // Recursively heapify the affected subtree
        heapify(arr, n, smallest);
    }
}

// Function to implement heap sort
void heapSort(Task arr[], int n) {
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // One by one extract an element from heap
    for (int i = n - 1; i >= 0; i--) {
        // Move current root to end
        swap(&arr[0], &arr[i]);

        // Call min heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

// Main function
int main() {
    int n;
    scanf("%d", &n); // Input number of tasks

    Task *arr = (Task *)malloc(n * sizeof(Task)); // Allocate memory for tasks

    // Input tasks
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &arr[i].priority, &arr[i].time);
    }

    // Sort the tasks using heap sort
    heapSort(arr, n);

    // Output the sorted tasks
    for (int i = n-1; i >= 0; i--) {
        printf("(%d, %d)\n", arr[i].priority, arr[i].time);
    }

    free(arr); // Free allocated memory
    return 0;
}
