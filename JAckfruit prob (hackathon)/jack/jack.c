#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// User structure
typedef struct user {
    char id[50];
    char name[50];
    struct histNode *browsingHistory;
    struct histNode *purchaseHistory;
} user;

// Item structure
typedef struct item {
    char id[50];
    char name[50];
    double price;
    int stock;
    int viewCount;
} item;

// History node structure
typedef struct histNode {
    char itemId[50];
    struct histNode *next;
} histNode;

// Graph node structure
typedef struct Gnode {
    char id[50];
    struct Gnode *next;
} Gnode;

// Graph structure
typedef struct Graph {
    Gnode *adjacencyList[100];
} Graph;

// Hash tables
user *uTable[100];
item *iTable[100];
Graph graph = {0};

// Hash function
int hashing(char *id) {
    int hash = 0;
    for (int i = 0; id[i] != '\0'; i++) {
        hash = (hash + id[i]) % 100;
    }
    return hash;
}

// Add a user
void add_user() {
    char id[50], name[50];
    printf("Enter user ID: ");
    scanf("%s", id);
    printf("Enter user Name: ");
    scanf("%s", name);
    int index = hashing(id);
    if (uTable[index] != NULL) {
        printf("User ID already exists!\n");
        return;
    }
    user *newuser = (user *)malloc(sizeof(user));
    strcpy(newuser->id, id);
    strcpy(newuser->name, name);
    newuser->browsingHistory = NULL;
    newuser->purchaseHistory = NULL;
    uTable[index] = newuser;
    printf("User added successfully.\n");
}

// Delete a user
void deleteuser() {
    char id[50];
    printf("Enter user ID to delete: ");
    scanf("%s", id);
    int index = hashing(id);
    if (uTable[index] == NULL) {
        printf("User not found!\n");
        return;
    }
    free(uTable[index]);
    uTable[index] = NULL;
    printf("User deleted successfully.\n");
}

// Show users
void showusers() {
    printf("\nAll users:\n");
    int anyuser = 0;
    for (int i = 0; i < 100; i++) {
        if (uTable[i] != NULL) {
            anyuser = 1;
            printf("User ID: %s, Name: %s\n", uTable[i]->id, uTable[i]->name);
        }
    }
    if (!anyuser) {
        printf("No users available.\n");
    }
}

// Add an item
void additem() {
    char id[50], name[50];
    double price;
    int stock;
    printf("Enter item ID: ");
    scanf("%s", id);
    printf("Enter item Name: ");
    scanf("%s", name);
    printf("Enter item Price: ");
    scanf("%lf", &price);
    printf("Enter item Stock: ");
    scanf("%d", &stock);
    int index = hashing(id);
    if (iTable[index] != NULL) {
        printf("Item ID already exists!\n");
        return;
    }
    item *newitem = (item *)malloc(sizeof(item));
    strcpy(newitem->id, id);
    strcpy(newitem->name, name);
    newitem->price = price;
    newitem->stock = stock;
    newitem->viewCount = 0;
    iTable[index] = newitem;
    printf("Item added successfully.\n");
}

// Delete an item
void deleteitem() {
    char id[50];
    printf("Enter item ID to delete: ");
    scanf("%s", id);
    int index = hashing(id);
    if (iTable[index] == NULL) {
        printf("Item not found!\n");
        return;
    }
    free(iTable[index]);
    iTable[index] = NULL;
    printf("Item deleted successfully.\n");
}

// Show items
void showitems() {
    printf("\nAll items:\n");
    int anyitem = 0;
    for (int i = 0; i < 100; i++) {
        if (iTable[i] != NULL) {
            anyitem = 1;
            printf("Item ID: %s, Name: %s, Price: $%.2f, Stock: %d, Views: %d\n", 
                   iTable[i]->id, iTable[i]->name, 
                   iTable[i]->price, iTable[i]->stock, 
                   iTable[i]->viewCount);
        }
    }
    if (!anyitem) {
        printf("No items available.\n");
    }
}

// Add history node if not present
void addhistNode(histNode **history, char *itemId) {
    histNode *current = *history;
    while (current != NULL) {
        if (strcmp(current->itemId, itemId) == 0) return;
        current = current->next;
    }
    histNode *newNode = (histNode *)malloc(sizeof(histNode));
    strcpy(newNode->itemId, itemId);
    newNode->next = *history;
    *history = newNode;
}

// Add an edge (item-user)
void addEdge(Graph *graph, char *fromID, char *toID) {
    int fromIndex = hashing(fromID);
    Gnode *newNode = (Gnode *)malloc(sizeof(Gnode));
    strcpy(newNode->id, toID);
    newNode->next = graph->adjacencyList[fromIndex];
    graph->adjacencyList[fromIndex] = newNode;
}

// View items
void viewitems() {
    printf("\nAvailable items:\n");
    int anyitem = 0;
    for (int i = 0; i < 100; i++) {
        if (iTable[i] != NULL) {
            anyitem = 1;
            printf("Item ID: %s, Name: %s, Price: $%.2f, Stock: %d, Views: %d\n", 
                   iTable[i]->id, iTable[i]->name, 
                   iTable[i]->price, iTable[i]->stock, 
                   iTable[i]->viewCount);
        }
    }
    if (!anyitem) {
        printf("No items available.\n");
        return;
    }

    char itemId[50], userId[50];
    printf("\nEnter item ID to view details (or type 'exit' to return): ");
    scanf("%s", itemId);

    if (strcmp(itemId, "exit") == 0) return;

    int index = hashing(itemId);
    item *item = iTable[index];
    if (item == NULL) {
        printf("Item not found!\n");
        return;
    }

    printf("Item Details:\n");
    printf("ID: %s, Name: %s, Price: $%.2f, Stock: %d\n", 
           item->id, item->name, item->price, item->stock);
    item->viewCount++;

    printf("\nEnter your user ID to log this view: ");
    scanf("%s", userId);

    int userIndex = hashing(userId);
    user *user = uTable[userIndex];
    if (user == NULL) {
        printf("User not found!\n");
        return;
    }

    addhistNode(&user->browsingHistory, itemId);
    addEdge(&graph, userId, itemId);

    printf("\nDo you want to buy this item? (yes/no): ");
    char response[10];
    scanf("%s", response);

    if (strcmp(response, "yes") == 0) {
        if (item->stock > 0) {
            addhistNode(&user->purchaseHistory, itemId);
            addEdge(&graph, itemId, userId);
            printf("Purchase successful!\n");
            item->stock--;
        } else {
            printf("Out of stock.\n");
        }
    }
}

// View browsing history
void browseHistory() {
    char userId[50];
    printf("Enter user ID to view browsing history: ");
    scanf("%s", userId);
    int index = hashing(userId);
    user *user = uTable[index];
    if (user == NULL) {
        printf("User not found!\n");
        return;
    }
    printf("Browsing History for %s:\n", user->name);
    histNode *current = user->browsingHistory;
    while (current != NULL) {
        printf("%s -> ", current->itemId);
        current = current->next;
    }
    printf("END\n");
}

// View purchase history
void purchaseHistory() {
    char userId[50];
    printf("Enter user ID to view purchase history: ");
    scanf("%s", userId);
    int index = hashing(userId);
    user *user = uTable[index];
    if (user == NULL) {
        printf("User not found!\n");
        return;
    }
    printf("Purchase History for %s:\n", user->name);
    histNode *current = user->purchaseHistory;
    while (current != NULL) {
        printf("%s -> ", current->itemId);
        current = current->next;
    }
    printf("END\n");
}

// Recommend items
void recommenditems(user *user) {
    if (!user->browsingHistory) {
        printf("No browsing history to recommend from.\n");
        return;
    }

    histNode *browsed = user->browsingHistory;
    printf("Recommendations:\n");
    while (browsed) {
        int index = hashing(browsed->itemId);
        item *current = iTable[index];
        if (current) printf("Item: %s | Name: %s\n", current->id, current->name);
        browsed = browsed->next;
    }
    printf("End of recommendations.\n");
}
// Main menu
void mainMenu() {
    int choice;
    do {
        printf("\n==== Main Menu ====\n");
        printf("1. User Management\n");
        printf("2. Item Management\n");
        printf("3. Purchase items\n");
        printf("4. View Browsing History\n");
        printf("5. View Purchase History\n");
        printf("6. Recommend items\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nuser Management:\n");
                printf("1. Add user\n");
                printf("2. Delete user\n");
                printf("3. Show users\n");
                printf("Enter your choice: ");
                int userChoice;
                scanf("%d", &userChoice);
                switch (userChoice) {
                    case 1: add_user(); break;
                    case 2: deleteuser(); break;
                    case 3: showusers(); break;
                    default: printf("Invalid choice!\n"); break;
                }
                break;
            case 2:
                printf("\nitem Management:\n");
                printf("1. Add item\n");
                printf("2. Delete item\n");
                printf("3. Show items\n");
                printf("Enter your choice: ");
                int itemChoice;
                scanf("%d", &itemChoice);
                switch (itemChoice) {
                    case 1: additem(); break;
                    case 2: deleteitem(); break;
                    case 3: showitems(); break;
                    default: printf("Invalid choice!\n"); break;
                }
                break;
            case 3: viewitems(); break;
            case 4: browseHistory(); break;
            case 5: purchaseHistory(); break;
            case 6:
                printf("\nEnter user ID for recommendations: ");
                char userId[50];
                scanf("%s", userId);
                int userIndex = hashing(userId);
                user *user = uTable[userIndex];
                if (user != NULL) {
                    recommenditems(user);
                } else {
                    printf("user not found!\n");
                }
                break;
            case 7: printf("Exiting...\n"); break;
            default: printf("Invalid choice! Please try again.\n"); break;
        }
    } while (choice != 7);
}

int main() {
    mainMenu();
    return 0;
}
