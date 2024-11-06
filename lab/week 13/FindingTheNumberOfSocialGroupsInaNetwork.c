// Imagine a social network where people are represented as nodes, and friendships are represented as directed edges between nodes. Your task is to find the number of distinct social groups in the network. A social group is defined as a set of people who are either directly or indirectly connected through friendships.

// Given a directed graph where each node represents a person and each directed edge u → v represents a friendship from person u to person v, determine the number of distinct social groups.

// Input Format

// The input consists of pairs of integers representing directed edges between nodes in the format u v, where u and v are node numbers.
// The input stops when a pair containing any negative integer is entered.
// The nodes are labeled from 1 to N, where N is the maximum node number provided in the input.
// Constraints

// 1 <= N <= 100 (Maximum number of nodes)
// 1 <= E <= 1000 (Maximum number of edges)
// Nodes are labeled from 1 to N.
// Input is terminated by a pair of negative integers.
// It is guaranteed that the input will contain at least one edge.
// Output Format

// Print the number of distinct social groups in the network.
// Sample Input 0

// 1 2
// 2 3
// 4 5
// -1 -1
// Sample Output 0

// 2
// Explanation 0

// The input represents friendships between people:

// 1 → 2
// 2 → 3
// 4 → 5
// There are two distinct social groups: {1, 2, 3} and {4, 5}.

#include <stdio.h>
#include <stdbool.h>

#define MAX_NODES 100

// Adjacency matrix representation
int adj[MAX_NODES][MAX_NODES];
bool visited[MAX_NODES];

// Function to add an edge in the graph (both directions to handle undirected components)
void addEdge(int u, int v) {
    adj[u][v] = 1;
    adj[v][u] = 1; // Treat the graph as undirected for social groups
}

// Depth-First Search (DFS) to visit nodes
void dfs(int node, int numNodes) {
    visited[node] = true;
    for (int i = 0; i < numNodes; i++) {
        if (adj[node][i] == 1 && !visited[i]) {
            dfs(i, numNodes);
        }
    }
}

// Function to find the number of social groups (connected components) using DFS 
int findSocialGroups(int numNodes) {
    int count = 0;
    for (int i = 0; i < numNodes; i++) {
        if (!visited[i]) {
            dfs(i, numNodes);  // Start a DFS if this node hasn't been visited
            count++;            // Each DFS call corresponds to one social group
        }
    }
    return count;
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
    while (1) {
        scanf("%d %d", &u, &v);
        if (u < 0 || v < 0) {
            break;  // Stop input if negative number is entered
        }
        addEdge(u - 1, v - 1);  // Convert to 0-based index

        // Update the number of nodes (maximum node number seen so far)
        if (u > numNodes) numNodes = u;
        if (v > numNodes) numNodes = v;
    }

    // Find and print the number of social groups
    int socialGroups = findSocialGroups(numNodes);
    printf("%d\n", socialGroups);

    return 0;
}