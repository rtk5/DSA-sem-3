/*The Computer Science Club is hosting a coding marathon where each participant is assigned a challenging problem to solve. However, to ensure fairness, the students work in rounds, with each student getting a fixed time slice to work on their problem before the next participant gets a turn. If a student cannot finish solving their problem within their time slice, they save their progress and return to the queue to resume in the next round. This continues until all students have finished their problems.

Your task is to simulate the coding marathon by implementing a Round Robin Scheduler. Each student has a specific time requirement to complete their problem, and each round provides a fixed time slice for every student to make progress. The process repeats until all students finish solving their problems.

Input Format

The first line contains two integers N (the number of students) and T (the fixed time slice each student gets per round).
The second line contains N space-separated integers, where each integer represents the total time a student needs to solve their assigned problem.
Constraints

1 <= N <= 100
1 <= T <= 100
Output Format

Print the order in which students finish their problems
Sample Input 0

5 3 
7 2 6 5 9
Sample Output 0

2 3 4 1 5 */


#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;                 // Student ID
    int remaining_time;     // Remaining time for the student to finish
} Student;

typedef struct {
    Student *students;     // Array of students
    int front, rear, size; // Front and rear indices, and the size of the queue
    unsigned capacity;     // Maximum capacity of the queue
} Queue;

// Function to create a queue of given capacity
Queue* createQueue(unsigned capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->students = (Student*)malloc(queue->capacity * sizeof(Student));
    return queue;
}

// Function to check if the queue is empty
int isEmpty(Queue* queue) {
    return (queue->size == 0);
}

// Function to check if the queue is full
int isFull(Queue* queue) {
    return (queue->size == queue->capacity);
}

// Function to add a student to the queue
void enqueue(Queue* queue, Student item) {
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->students[queue->rear] = item;
    queue->size = queue->size + 1;
}

// Function to remove and return a student from the queue
Student dequeue(Queue* queue) {
    Student item = queue->students[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

// Function to simulate the Round Robin scheduling
void roundRobinScheduling(Queue* queue, int T) {
    int finished[queue->capacity]; // Array to track finished students
    for (int i = 0; i < queue->size; i++) {
        finished[i] = 0; // Initialize to 0 (not finished)
    }
    int finishOrder[queue->capacity]; // To store the order of finishing
    int index = 0; // To keep track of the finish order

    while (!isEmpty(queue)) {
        Student current = dequeue(queue);

        if (current.remaining_time <= T) {
            // Student finishes their problem
            finishOrder[index++] = current.id; // Store finish order
        } else {
            // Reduce remaining time and enqueue again
            current.remaining_time -= T;
            enqueue(queue, current);
        }
    }

    // Print the order in which students finish
    for (int i = 0; i < index; i++) {
        printf("%d ", finishOrder[i]);
    }
    printf("\n");
}

int main() {
    int N, T;
    scanf("%d %d", &N, &T);

    int times[N]; // Array to hold the times required by each student
    for (int i = 0; i < N; i++) {
        scanf("%d", &times[i]);
    }

    // Create a queue with capacity N
    Queue* queue = createQueue(N);

    // Enqueue students with their respective times
    for (int i = 0; i < N; i++) {
        Student student = {i + 1, times[i]};
        enqueue(queue, student);
    }

    // Call the round robin scheduler
    roundRobinScheduling(queue, T);

    // Free allocated memory
    free(queue->students);
    free(queue);
    
    return 0;
}
