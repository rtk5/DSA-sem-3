// You are given a directed graph with N nodes and E edges. Your task is to determine if the graph contains a cycle. A cycle exists if there is a path in the graph that starts and ends at the same node.

// Input Format

// The input consists of pairs of integers representing directed edges between nodes in the format u v, where u and v are node numbers.
// The input stops when a pair containing any negative integer is entered.
// The nodes are numbered from 1 to N, where N is the maximum node number provided in the input.
// Constraints

// 1 <= N <= 100 (Maximum number of nodes)
// 1 <= E <= 1000 (Maximum number of edges)
// Nodes are labeled from 1 to N.
// Input is terminated by a pair of negative integers.
// It is guaranteed that the input will contain at least one edge.
// Output Format

// Print "The graph contains a cycle." if a cycle is found in the graph.
// Print "The graph does not contain a cycle." if there is no cycle.
// Sample Input 0

// 1 2
// 2 3
// 3 4
// 4 1
// -1 -1
// Sample Output 0

// The graph contains a cycle.
// Explanation 0

// The input represents a directed graph with edges:

// 1 → 2
// 2 → 3
// 3 → 4
// 4 → 1
// This forms a cycle as there is a path from 1 to 4 that returns to 1, making it a cycle.


#include <stdio.h>
#include <stdbool.h>


#define MAX_NODES 100


// Adjacency matrix representation
int adj[MAX_NODES][MAX_NODES];




// Function to add an edge in the graph
void addEdge(int u, int v) {
   adj[u][v] = 1;

}


// Function to check if the graph contains a cycle
bool isCyclic(int numNodes) {
   int inDegree[MAX_NODES] = {0};

    
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            if (adj[i][j]) {
                inDegree[j]++;
            }
        }
    }

    
    int queue[MAX_NODES];
    int front = 0, back = 0;

    // Enqueue nodes with 0 in-degree
    for (int i = 0; i < numNodes; i++) {
        if (inDegree[i] == 0) {
            queue[back++] = i;
        }
    }

    int count = 0; // Count of processed nodes

    // Process the nodes in topological order
    while (front < back) {
        int node = queue[front++];
        count++;

        // Decrease in-degree of all adjacent nodes
        for (int i = 0; i < numNodes; i++) {
            if (adj[node][i]) {
                inDegree[i]--;
                if (inDegree[i] == 0) {
                    queue[back++] = i;
                }
            }
        }
    }

    // If count of processed nodes is less than numNodes, a cycle exists
    return count != numNodes;
}


int main() {
   int u, v, numNodes = 0;


   // Initialize the adjacency matrix
   for (int i = 0; i < MAX_NODES; i++) {
       for (int j = 0; j < MAX_NODES; j++) {
           adj[i][j] = 0;
          
           
       }
   }


   // Read edges until a negative integer is entered
   // printf("Enter edges (e.g., '1 2'). Enter a negative number to stop:\n");
   while (1) {
       scanf("%d %d", &u, &v);
       if (u < 0 || v < 0) {
           break; // Stop input if negative number is entered
       }
       addEdge(u - 1, v - 1); // Convert to 0-based index


       // Update the number of nodes
       if (u > numNodes) numNodes = u;
       if (v > numNodes) numNodes = v;
   }


   // Check for cycle in the graph
   if (isCyclic(numNodes)) {
       printf("The graph contains a cycle.\n");
   } else {
       printf("The graph does not contain a cycle.\n");
   }


   return 0;
}