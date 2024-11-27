// DFS traversal - Connectivity of the graph using Adjacency Matrix

void traverse(int u, int visited[])
{

    visited[u] = 1; // mark u as visited

    for (int v = 0; v < n; v++)
    {

        if (graph[u][v] && !visited[v])
        {

            traverse(v, visited);
        }
    }
}

// BFS traversal - Connectivity of the graph using Adjacency Matrix

void traverse(int s, int visited[], int n, int graph[][])
{

    int f = 0, r = -1, q[10];

    q[++r] = s;

    visited[s] = 1; // mark s as visited

    while (f <= r)
    {

        s = q[f++];

        for (int v = 0; v < n; v++)
        {

            if (graph[s][v] == 1 && visited[v] == 0)
            { // adjacent and unvisited

                visited[v] = 1; // mark as visited

                q[++r] = v;
            }
        }
    }
}

// HASH TABLE  -- seperate chaining

// Define the structure for each node

typedef struct element
{

    int rNo; // Roll number (key)

    char name[30]; // Associated name (data)

    struct element *next; // Pointer to the next node in the chain

} NODE;

#define SIZE 10 // Define the size of the hash table

// Function to initialize the hash table

void initTable(NODE *ht[SIZE])
{

    for (int i = 0; i < SIZE; i++)

        ht[i] = NULL;
}

// Function to insert a node into the hash table

void insert(NODE *ht[SIZE], int rNo, char name[30])
{

    int index = rNo % SIZE; // Hash function

    NODE *newNode = malloc(sizeof(NODE)); // Allocate memory for the new node

    newNode->rNo = rNo;

    strcpy(newNode->name, name);

    newNode->next = ht[index]; // Insert at the beginning of the chain

    ht[index] = newNode; // Update the head of the list
}

// Function to delete a node from the hash table

int delete(NODE *ht[SIZE], int rNo)
{

    int index = rNo % SIZE; // Hash function

    NODE *p = ht[index]; // Pointer to traverse the list

    NODE *q = NULL; // Pointer to track the previous node

    while (p != NULL && p->rNo != rNo)
    { // Search for the node

        q = p;

        p = p->next;
    }

    if (p != NULL)
    { // Node found

        if (q == NULL) // Node is the first in the chain

            ht[index] = p->next;

        else // Node is in the middle or end of the chain

            q->next = p->next;

        free(p); // Free memory

        return 1; // Successful deletion
    }

    return 0; // Node not found
}

// Function to search for a node in the hash table

int search(NODE *ht[SIZE], int rNo, char name[30])
{

    int index = rNo % SIZE; // Hash function

    NODE *p = ht[index]; // Start at the head of the chain

    while (p != NULL)
    { // Traverse the chain

        if (p->rNo == rNo)
        { // Key matches

            strcpy(name, p->name); // Copy the name

            return 1; // Found
        }

        p = p->next; // Move to the next node
    }

    return 0; // Not found
}

// Function to display the hash table

void displayTable(NODE *ht[SIZE])
{

    for (int i = 0; i < SIZE; i++)
    {

        printf("Bucket %d: ", i);

        NODE *p = ht[i];

        while (p != NULL)
        {

            printf("[rNo: %d, Name: %s] -> ", p->rNo, p->name);

            p = p->next;
        }

        printf("NULL\n");
    }
}

// LINEAR PROBING

typedef struct
{

    int rNo; // Roll number (key)

    char name[30]; // Associated name (data)

    int mark; // Status marker: -1 (empty), 1 (occupied)

} NODE;

void initTable(NODE ht[], int *n)
{

    for (int i = 0; i < SIZE; i++)

        ht[i].mark = -1; // Mark all slots as empty

    *n = 0; // Set the current number of elements to 0
}

int insertRecord(NODE ht[], int rNo, char name[], int *n)
{

    if (SIZE == *n) // If the table is full, insertion fails

        return 0;

    int index = rNo % SIZE; // Hash function to calculate index

    while (ht[index].mark != -1) // Find the next free slot

        index = (index + 1) % SIZE;

    ht[index].rNo = rNo; // Store the roll number

    strcpy(ht[index].name, name); // Store the name

    ht[index].mark = 1; // Mark the slot as occupied

    (*n)++; // Increment the count of elements

    return 1; // Successful insertion
}

int deleteRecord(NODE ht[], int rNo, int *n)
{

    if (*n == 0) // If the table is empty, deletion fails

        return 0;

    int index = rNo % SIZE; // Hash function to calculate index

    int i = 0;

    while (ht[index].rNo != rNo && i < *n)
    { // Search for the record

        index = (index + 1) % SIZE; // Linear probing

        if (ht[index].mark == 1)

            i++;
    }

    if (ht[index].rNo == rNo && ht[index].mark == 1)
    { // Record found

        ht[index].mark = -1; // Mark the slot as empty

        (*n)--; // Decrement the count of elements

        return 1; // Successful deletion
    }

    return 0; // Record not found
}

int searchRecord(NODE ht[], int rNo, int n)
{

    if (n == 0) // If the table is empty, search fails

        return 0;

    int index = rNo % SIZE; // Hash function to calculate index

    int i = 0;

    while (ht[index].rNo != rNo && i < n)
    { // Search for the record

        index = (index + 1) % SIZE; // Linear probing

        if (ht[index].mark == 1)

            i++;
    }

    if (ht[index].rNo == rNo && ht[index].mark == 1)
    { // Record found

        strcpy(name, ht[index].name); // Copy the name

        return 1; // Found
    }

    return 0; // Not found
}

// ITERATIVE TRAVERSAL

iterativeInorder(root)

    s = emptyStack // Stack to store nodes for backtracking

    current = root // Start from the root

    do
{

    // Step 1: Traverse the left subtree as far as possible

    while (current != null)
    {

        push(s, current) // Save the current node on the stack

            current = current->left // Move to the left child
    }

    // Step 2: Process the leftmost node (or backtrack to the parent)

    poppedNode = pop(s) // Get the most recent node saved on the stack

                 print poppedNode->info // Visit the node (process its data)

                     // Step 3: Move to the right subtree

                     current = poppedNode->right
}
while (!isEmpty(s) or current != null) // Continue until the stack and current are empty

    // Minimum Element in Binary Search Tree

    int minimum(struct tnode *t)

    {

        while (t->left != NULL)

            t = t->left; // Keep moving to the left child until you reach the leftmost node

        return (t->data); // The leftmost node contains the minimum value in BST
    }

// Maximum Element in Binary Search Tree

int maximum(struct tnode *t)

{

    while (t->right != NULL)

        t = t->right; // Keep moving to the right child until you reach the rightmost node

    return (t->data); // The rightmost node contains the maximum value in BST
}

// Height of a Binary Tree

int height(struct tnode *t)

{

    if (t == NULL)

        return -1; // Base case: An empty tree has a height of -1

    if ((t->left == NULL) && (t->right == NULL))

        return 0; // A leaf node has a height of 0

    return (1 + max(height(t->left), height(t->right))); // Recursively calculate the height of left and right subtrees and add 1 for the current node
}

// Count the Number of Leaf Nodes

int leafcount(struct tnode *t)

{

    if (t == NULL)

        return 0; // Base case: An empty tree has no leaves

    if ((t->left == NULL) && (t->right == NULL))

        return 1; // A leaf node has no children, so return 1

    int l = leafcount(t->left); // Recursively count the leaf nodes in the left subtree

    int r = leafcount(t->right); // Recursively count the leaf nodes in the right subtree

    return (l + r); // The total number of leaf nodes is the sum of the left and right leaf counts
}
