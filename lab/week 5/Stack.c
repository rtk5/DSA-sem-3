/*You are given a row of plants, where each plant has a certain level of pesticide. Every day, any plant that has more pesticide than the plant directly to its left dies. This process continues until no plant dies. Your task is to determine the number of days after which no plant dies.

Sample input-1

7

6 5 8 4 7 10 9

Output:

2

Explanation:

Day 1: Plants 8, 7, and 10 die. Remaining: [6, 5, 4, 9]

Day 2: Plant 9 dies. Remaining: [6, 5, 4]

Plants stop dying after 2 days.

Input Format

The first line contains an integer n, the number of plants in the garden.

The second line contains n space-separated integers representing the pesticide levels in each of the plants.

Constraints

1 <= n <=100,000

0 <= p[i] <=10^9 where p[i] is the pesticide level of the i th plant.

Output Format

Return an integer representing the number of days after which no plant dies.*/


#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

typedef struct {
    int pesticide;
    int days;
} Plant;

int main() {
    int n;
    scanf("%d", &n);

    int pesticides[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d", &pesticides[i]);
    }

    Plant stack[MAX_N];
    int top = -1;
    int maxDays = 0;

    for (int i = 0; i < n; i++) {
        int days = 0;

        while (top >= 0 && pesticides[i] <= stack[top].pesticide) {
            if (stack[top].days > days) {
                days = stack[top].days;
            }
            top--;
        }

        if (top >= 0) {
            days++;
        } else {
            days = 0;
        }

        stack[++top] = (Plant){pesticides[i], days};

        if (days > maxDays) {
            maxDays = days;
        }
    }

    printf("%d\n", maxDays);
    return 0;
}