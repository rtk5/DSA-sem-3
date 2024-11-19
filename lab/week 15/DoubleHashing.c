// Write a C program to implement double hashing. The 2 hash functions are defined as follows:

// h1(k) = (2k+3) mod m

// h2(k) = (3k+1) mod m

// Print the elements of the hash table. If no element has been inserted at that particular index then print -1 else print the element inserted.

// Note: It is not mandatory for all elements to be successfully inserted into the hash table. If repeated collisions occur and the probing cycle leads back to an already-visited index (indicating that all possible positions have been checked without finding an empty slot), the insertion process for that element should be stopped.

// Input Format

// m (Hash table size)
// n (Number of elements)
// Element 1
// Element 2
// .
// .
// .
// Element n
// Constraints

// Elements >=0
// Output Format

// Element in index 0
// Element in index 1
// .
// .
// .
// Element in index (n-1)
// Sample Input 0

// 10
// 8
// 3
// 2
// 9
// 6
// 11
// 13
// 7
// 12
// Sample Output 0

// -1
// 9
// -1
// 11
// 12
// 6
// -1
// 2
// -1
// 3


#include<stdio.h>
#include<stdlib.h>

// Function to perform double hashing
void doubleHashing(int m, int n, int *table, int h1_1, int h1_2, int h2_1, int h2_2) {
    int element;
    for (int i = 0; i < n; i++) {
        scanf("%d", &element); // Read the element to insert

        int h1 = (h1_1 * element + h1_2) % m; // First hash function
        int h2 = (h2_1 * element + h2_2) % m; // Second hash function

        int index = h1;
        int j = 0; // Probing counter

        // Try to insert the element into the table
        while (table[index] != -1 && j < m) {
            j++; // Increment probing counter
            index = (h1 + j * h2) % m; // Double hashing formula
        }

        // If a suitable position is found, insert the element
        if (table[index] == -1) {
            table[index] = element;
        }
        // Otherwise, we stop trying for this element
    }
}

int main() {
    int m; // Hash table size
    int n; // Number of elements to insert

    scanf("%d", &m);
    scanf("%d", &n);

    int *table = malloc(m * sizeof(int)); // Allocate memory for the hash table
    for (int i = 0; i < m; i++) {
        table[i] = -1; // Initialize all slots as empty
    }

    // Perform double hashing with the given hash functions
    doubleHashing(m, n, table, 2, 3, 3, 1);

    // Print the hash table
    for (int i = 0; i < m; i++) {
        printf("%d\n", table[i]);
    }

    free(table); // Free the allocated memory
    return 0;
}