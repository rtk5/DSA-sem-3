#include<stdio.h>
#define SIZE 10
typedef struct node{
 int data;
 int flag;
}NODE;
void insert(NODE *bst,int data,int index)
{
    if(bst[index].flag==0 && index<SIZE)//exit criteria
    {
       bst[index].data=data;
       bst[index].flag=1;
    }
    else if(data<=bst[index].data && index<SIZE)
    {
    index=2*index+1;
    insert(bst,data,index);
    }
    else if(data>bst[index].data   && index<SIZE)
    {
      index=2*index+2;
      insert(bst,data,index);
    }
    else
        printf("Insertion not possible");
}
void inorder(NODE *bst,int i)
{
    if(bst[i].flag && i<SIZE)
    {
        inorder(bst,2*i+1);
        printf("%d ",bst[i].data);
        inorder(bst,2*i+2);
    }
}
// Function to print the tree in the requested format
void print_tree(NODE *bst) {
	int i;
    printf("Index:\t");
    for (i = 0; i < SIZE; i++) {
        printf("%d\t", i);         // Print the indices
    }
    printf("\nData:\t");
    for ( i = 0; i < SIZE; i++) {
        if (bst[i].flag)           // If the node is occupied, print data
            printf("%d\t", bst[i].data);
        else                       // If the node is empty, print a dash
            printf("-\t");
    }
    printf("\nFlag:\t");
    for (i = 0; i < SIZE; i++) {
        printf("%d\t", bst[i].flag); // Print the flag values
    }
    printf("\n");
}
int main()
{
    int d,ch=0;
    NODE bst[SIZE]={};//initialize the flag with 0
    do{
    printf("Enter the data:");
    scanf("%d",&d);
    insert(bst,d,0);
    printf("To Continue press 1");
    scanf("%d",&ch);
    }while(ch);
    inorder(bst,0);
    
    printf("\nBinary Search Tree Array Representation:\n");
    print_tree(bst);
    return 0;
}
