/*In a sophisticated multi-core processor system, multiple tasks arrive at the scheduler, each with a set of attributes such as Task ID (TID), Priority, and Execution Time. The system's architecture requires scheduling tasks across different cores based on their priority and specific time constraints.

The task scheduler must handle the following complexities:

Task Preemption: A lower priority task can be interrupted and paused if a higher priority task arrives.

Dynamic Priority Changes: The priority of certain tasks can dynamically change based on system requirements.

Task Dependencies: Some tasks can only be executed after a specific set of tasks are completed.

Your task is to simulate this multi-core task scheduler using a priority queue. Tasks must be managed efficiently to minimize idle time across cores while respecting all constraints.

The following operations must be performed by the scheduler:

Task Insertion: Add a new task to the scheduler, specifying the task ID, priority, and execution time.

Execute Task: Execute the highest priority task available. The task should run on the available core with the lowest ID. If multiple cores are available, the one with the lowest ID should be selected. Print the core ID and the TID of the executed task.

Change Task Priority: If a task's priority changes dynamically due to system requirements, the new priority must be updated in the scheduler.

Task Dependency: Some tasks can only be executed after certain other tasks are completed. If a dependent task is added to the queue, it should not be executed until its dependency is fulfilled.

Example Input:

2 # Number of cores

4 # Number of initial tasks

1 4 10 # Task 1: TID = 1, Priority = 4, Execution Time = 10

2 5 5 # Task 2: TID = 2, Priority = 5, Execution Time = 5

3 3 8 # Task 3: TID = 3, Priority = 3, Execution Time = 8

4 6 6 # Task 4: TID = 4, Priority = 6, Execution Time = 6

Expected Output: //print in the same format

Core 1: Executing Task 4

Core 2: Executing Task 2

Input Format

The first line contains the number of cores N.

The next line contains M tasks, each with a format TID Priority Execution Time, where:

TID is the task identifier.

Priority is the task's priority.

Execution Time is the task’s required execution time in time units.

Constraints

If a task is paused due to preemption (by a higher priority task), it must resume its execution from where it left off once the higher priority task completes.

If a task’s priority changes dynamically and it becomes the highest priority, the scheduler must preempt the currently running task and execute the new task.

The task with the highest priority should always be executed first on the core with the lowest ID.

Output Format

For each Execute Task operation, print the core ID and the task ID being executed.*/


#include <stdio.h>  
#include <stdlib.h>  
#include <stdbool.h>  

typedef struct Task {  
    int tid;  
    int priority;  
    int executionTime;  
    struct Task* next;  
} Task;  

typedef struct Core {  
    int coreId;  
    Task* currentTask;  
    bool isFree;  
} Core;  

typedef struct TaskQueue {  
    Task* head;  
} TaskQueue;  

TaskQueue* createTaskQueue() {  
    TaskQueue* queue = (TaskQueue*)malloc(sizeof(TaskQueue));  
    queue->head = NULL;  
    return queue;  
}  

Task* createTask(int tid, int priority, int executionTime) {  
    Task* newTask = (Task*)malloc(sizeof(Task));  
    newTask->tid = tid;  
    newTask->priority = priority;  
    newTask->executionTime = executionTime;  
    newTask->next = NULL;  
    return newTask;  
}  

Core* createCore(int coreId) {  
    Core* core = (Core*)malloc(sizeof(Core));  
    core->coreId = coreId;  
    core->currentTask = NULL;  
    core->isFree = true;  
    return core;  
}  

// Function to insert a task into the priority queue based on priority  
void insertTask(TaskQueue* queue, Task* newTask) {  
    if (queue->head == NULL || queue->head->priority < newTask->priority) {  
        newTask->next = queue->head;  
        queue->head = newTask;  
    } else {  
        Task* current = queue->head;  
        while (current->next != NULL && current->next->priority >= newTask->priority) {  
            current = current->next;  
        }  
        newTask->next = current->next;  
        current->next = newTask;  
    }  
}  

// Function to execute the highest priority task  
Task* executeTask(TaskQueue* queue) {  
    if (queue->head == NULL) {  
        return NULL;  
    }  
    Task* taskToExecute = queue->head;  
    queue->head = queue->head->next;  
    return taskToExecute;  
}  

// Function to simulate task scheduling  
void simulateTaskScheduler(TaskQueue* queue, Core** cores, int numCores) {  
    for (int i = 0; i < numCores; i++) {  
        if (queue->head != NULL) {  
            Task* task = executeTask(queue);  
            cores[i]->currentTask = task;  
            cores[i]->isFree = false;  
            printf("Core %d: Executing Task %d\n", cores[i]->coreId, task->tid);  
            free(task);  
            cores[i]->isFree = true;  
        }  
    }  
}  

// Main function  
int main() {  
    int numCores;  
    scanf("%d", &numCores);  
    
    Core** cores = (Core*)malloc(numCores * sizeof(Core));  
    for (int i = 0; i < numCores; i++) {  
        cores[i] = createCore(i + 1);  
    }  
    
    TaskQueue* queue = createTaskQueue();  
    
    int numTasks;  
    scanf("%d", &numTasks);  
    
    for (int i = 0; i < numTasks; i++) {  
        int tid, priority, executionTime;  
        scanf("%d %d %d", &tid, &priority, &executionTime);  
        Task* newTask = createTask(tid, priority, executionTime);  
        insertTask(queue, newTask);  
    }  
    
    simulateTaskScheduler(queue, cores, numCores);  
    
    free(queue);  
    for (int i = 0; i < numCores; i++) {  
        free(cores[i]);  
    }  
    free(cores);  
    
    return 0;  
}