/*Complete the function 'concat'. It takes the head pointers of two lists as parameters. Concatenate the nodes in both the lists in an alternate manner to form a new list. Return the new list. The first element is from the list with head1.

Note that if any one of the lists runs out of elements, the remaining elements of the other list must be appended. Make use of the pre-coded functions to finish the code. If both lists are empty, return NULL from the function.

Input Format

Number_of_elements_in_list1 Elements in list1 (if number of elements not 0) Number_of_elements_in_list2 Elements in list2 (if number of elements not 0)

Constraints

The lists have at most 50 elements.

Output Format

Elements in the new list (space separated)*/

#include <stdio.h>
#include <stdlib.h>

struct node {
    int info;
    struct node *link;
};  

typedef struct node *NODE;

NODE getNode() {
    NODE temp;
    temp = (NODE)malloc(sizeof(struct node));
    if (temp == NULL) {
        // printf("No memory allocated");
        exit(0);
    }
    return temp;
}

NODE insert_rear(int item, NODE first) {
    NODE temp = getNode();
    temp -> info = item;
    temp -> link = NULL;
    if(first == NULL) {
        return temp;
    }
    NODE current;
    current = first;
    while( current -> link != NULL) {
        current = current -> link;
    }
    current -> link = temp;
    return first;
}

void display(NODE first) {
    NODE current = first;
    if (current == NULL) {
        printf("0");
        return;
    }
    while (current != NULL) {
        printf("%d ", current->info);
        current = current->link;
    }
}

int main() {
    NODE h1 = NULL;  
    NODE h2 = NULL;  
    NODE l3 = NULL;  
    int n, m, a, b;

    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a);
        h1 = insert_rear(a, h1);
    }

    scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        scanf("%d", &b);
        h2 = insert_rear(b, h2);
    }

    NODE cur1 = h1;
    NODE cur2 = h2;

    while(cur1 != NULL && cur2 != NULL) {
        l3 = insert_rear(cur1->info, l3);
        cur1 = cur1->link;
        l3 = insert_rear(cur2->info, l3);
        cur2 = cur2->link;
    }

    while(cur1 != NULL) {
        l3 = insert_rear(cur1->info, l3);
        cur1 = cur1->link;
    }

    while(cur2 != NULL) {
        l3 = insert_rear(cur2->info, l3);
        cur2 = cur2->link;
    }
    if(l3!=NULL)
    display(l3);
    else
        printf("empty list");

    return 0;
}
