/*You are the lead architect for the city of Stackopolis, known for its unique skyline composed of buildings that resemble a histogram. The city council has tasked you with finding the largest rectangular billboard that can be placed within the city's skyline without altering any buildings.

Input Format

The first line contains an integer n (1 ≤ n ≤ 100,000), representing the number of buildings in Stackopolis.
The second line contains n space-separated integers h[i] (0 ≤ h[i] ≤ 1,000,000,000), where h[i] represents the height of the i-th building.
Constraints

_

Output Format

A single integer representing the area of the largest rectangular billboard that can be placed within the skyline.
Sample Input 0

6
2 1 5 6 2 3
Sample Output 0

10*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

typedef struct {
    int *array;
    int top;
    int capacity;
} Stack;

Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

void push(Stack* stack, int item) {
    stack->array[++stack->top] = item;
}

int pop(Stack* stack) {
    return stack->array[stack->top--];
}

int peek(Stack* stack) {
    return stack->array[stack->top];
}

long long largestRectangleArea(int* heights, int n) {
    Stack* stack = createStack(n);
    long long maxArea = 0;
    int i = 0;

    while (i < n) {
        // If this bar is higher than the bar at stack top, push it to the stack
        if (isEmpty(stack) || heights[i] >= heights[peek(stack)]) {
            push(stack, i++);
        } else {
            // Pop the top
            int top = pop(stack);
            // Calculate the area with heights[top] as the smallest (or minimum height) bar 'h'
            long long area = (long long)heights[top] * (isEmpty(stack) ? i : i - peek(stack) - 1);
            // Update max area, if needed
            if (area > maxArea) {
                maxArea = area;
            }
        }
    }

    // Now pop the remaining bars from the stack and calculate area with every popped bar
    while (!isEmpty(stack)) {
        int top = pop(stack);
        long long area = (long long)heights[top] * (isEmpty(stack) ? i : i - peek(stack) - 1);
        if (area > maxArea) {
            maxArea = area;
        }
    }

    free(stack->array);
    free(stack);
    return maxArea;
}

int main() {
    int n;
    scanf("%d", &n);

    int* heights = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &heights[i]);
    }

    printf("%lld\n", largestRectangleArea(heights, n));

    free(heights);
    return 0;
}
