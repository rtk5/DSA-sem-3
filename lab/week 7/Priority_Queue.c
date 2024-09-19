/*Story:

Imagine a scenario where you are managing a system that schedules tasks for processing. You have a circular queue of tasks, and you want to determine which task remains in the queue after repeatedly processing every k-th task. The tasks are processed in a circular manner where after the last task, the queue wraps around to the first task.

Given a circular queue of n tasks, each represented by a unique position number from 1 to n, and a number k, representing the step count to process every k-th task, determine the position of the last remaining task in the queue after all others have been processed.

Sample Input 1

5 3

Sample Output:

4

Input Format

Two integers n and k separated by a space.

n (1 ≤ n ≤ 500): The total number of tasks in the circular queue.

k (1 ≤ k ≤ n): The step count for processing tasks.

Constraints

Dont change the boiler code.

Output Format

A single integer representing the position of the last remaining task.*/




#include <stdio.h>
#include <stdlib.h>

#define MAX 500

// Circular Queue structure
typedef struct {
   int data[MAX];
   int front;
   int rear;
   int size;
} CircularQueue;

// Function to initialize the circular queue
void initializeQueue(CircularQueue* q) {
   q->front = 0;
   q->rear = -1;
   q->size = 0;
}

// Function to check if the queue is empty
int isEmpty(CircularQueue* q) {
   return q->size == 0;
}

// Function to check if the queue is full
int isFull(CircularQueue* q) {
   return q->size == MAX;
}

// Function to enqueue an element
void enqueue(CircularQueue* q, int value) {
   if (isFull(q)) {
      
       return;
   }
   q->rear = (q->rear + 1) % MAX;
   q->data[q->rear] = value;
   q->size++;
}

// Function to dequeue an element
int dequeue(CircularQueue* q) {
   if (isEmpty(q)) {
      
       return -1;
   }
   int value = q->data[q->front];
   q->front = (q->front + 1) % MAX;
   q->size--;
   return value;
}

// Function to find the position of the last remaining task

int findLastTask(CircularQueue* q, int k) {
while (q->size > 1) {
        // Rotate the first (k-1) elements to the back of the queue
        for (int i = 1; i < k; i++) {
            int temp = dequeue(q); // Remove front element
            enqueue(q, temp); // Add it to the rear
        }
        // Remove the k-th task (dequeue it)
        dequeue(q);
    }
    // Return the last remaining task
    return dequeue(q);
}

int main() {
   int n, k;
  
   // Input number of tasks and step count
   scanf("%d %d", &n, &k);
  
   // Create and initialize the circular queue
   CircularQueue queue;
   initializeQueue(&queue);

   // Enqueue all tasks
   for (int i = 1; i <= n; i++) {
       enqueue(&queue, i);
   }

   // Find the last remaining task
   int result = findLastTask(&queue, k);
  
   // Output the result
   printf("%d\n", result);
  
   return 0;
}