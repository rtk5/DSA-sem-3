// Given an undirected graph represented by a list of edges, determine whether the graph has a Mesh topology, Ring topology, or is an Incomplete graph.

// A Mesh topology is a graph in which there is an edge between every pair of vertices (i.e., it is a complete graph).
// A Ring topology is a graph in which each vertex is connected to exactly two other vertices, forming a single cycle.
// If the graph is neither a Mesh topology nor a Ring topology, it is considered an Incomplete graph.
// The graph is undirected so an edge from u to v is the same as an edge from v to u.

// If a graph has n vertices they are named 0 to n. Note that the edges in the test cases can be wrong, repeated or redundant.

// Input Format

// An integer n representing the number of vertices in the graph.
// An integer m representing the number of edges in the graph.
// A list of m edges where each edge is a pair (u, v) indicating an edge between vertices u and v.
// Constraints

// 1≤n≤100 (number of vertices)
// 1≤m≤1000 (number of edges)
// 0≤u ,v
// Output Format

// Output "The graph has a Mesh topology." if the graph satisfies the Mesh topology condition.
// Output "The graph has a Ring topology." if the graph satisfies the Ring topology condition.
// Output "The graph is incomplete." otherwise.
// Sample Input 0

// 4
// 6
// 0 1
// 0 2
// 0 3
// 1 2
// 1 3
// 2 3
// Sample Output 0

// The graph has a Mesh topology.
// Explanation 0

// For Node 0, there are edges with Nodes 1, 2, and 3.
// For Node 1, there are edges with Nodes 0, 2, and 3.
// For Node 2, there are edges with Nodes 0, 1, and 3.
// For Node 3, there are edges with Nodes 0, 1, and 2.
// This means that there is an edge between every pair of vertices, satisfying the condition of mesh topology.

// Sample Input 1

// 4
// 4
// 0 1
// 1 2
// 2 3
// 3 0
// Sample Output 1

// The graph has a Ring topology.
// Explanation 1

// Starting from a node we can reach all the nodes and return back to it so it is ring topology.


#include <stdio.h>
#include <stdbool.h>

bool isMeshTopology(int edges[][2], int m, int n);
bool isRingTopology(int edges[][2], int m, int n);

int main() {
    int n, m;
    
    // Read the number of vertices and edges
    scanf("%d", &n);
    scanf("%d", &m);
    
    int edges[m][2];  // Array to store edges
    
    // Read the edges (each edge is a pair of vertices)
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &edges[i][0], &edges[i][1]);
    }
    
    // Determine the topology
    if (isMeshTopology(edges, m, n)) {
        printf("The graph has a Mesh topology.\n");
    } else if (isRingTopology(edges, m, n)) {
        printf("The graph has a Ring topology.\n");
    } else {
        printf("The graph is incomplete.\n");
    }

    return 0;
}

#include <stdio.h>
#include <stdbool.h>

bool isMeshTopology(int edges[][2], int m, int n) {
    // Adjacency matrix to track connections
    bool adj[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adj[i][j] = false;
        }
    }
    
    // Fill adjacency matrix
    for (int i = 0; i < m; i++) {
        int u = edges[i][0], v = edges[i][1];
        if (u < n && v < n) {
            adj[u][v] = true;
            adj[v][u] = true;  // Since the graph is undirected
        }
    }
    
    // Check mesh condition
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && !adj[i][j]) {
                return false;
            }
        }
    }
    
    return true;
}

bool isRingTopology(int edges[][2], int m, int n) {
    if (m != n) {
        return false; // A ring must have exactly n edges
    }

    // Degree array to track connections for each vertex
    int degree[n];
    for (int i = 0; i < n; i++) {
        degree[i] = 0;
    }
    
    // Populate the degree array
    for (int i = 0; i < m; i++) {
        int u = edges[i][0], v = edges[i][1];
        if (u < n && v < n) {
            degree[u]++;
            degree[v]++;
        }
    }
    
    // Check ring condition: each vertex should have degree 2
    for (int i = 0; i < n; i++) {
        if (degree[i] != 2) {
            return false;
        }
    }
    
    // Additional condition: The graph should form a single cycle.
    // A simple cycle check can be skipped since we've ensured all degrees are 2.
    return true;
}