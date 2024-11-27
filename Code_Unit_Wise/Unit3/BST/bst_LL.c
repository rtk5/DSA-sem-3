#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
}NODE;
NODE* createnode(int data)
{
    NODE *nn=(NODE*)malloc(sizeof(NODE));
    nn->data=data;
    nn->left=NULL;
    nn->right=NULL;
    return nn;
}
int isempty(NODE *t)
{
    return (t==NULL);
}

NODE* insertNode(NODE *root,int data)
{
    if(isempty(root))
        root=createnode(data);
    else if(data<=root->data)
        root->left=insertNode(root->left,data);
    else
        root->right=insertNode(root->right,data);
    return root;
}

void preorder(NODE *t)
{
    if(isempty(t))
        printf("Tree ie empty");
    else{
        printf("%d ",t->data); //v
        if(t->left!=NULL)
            preorder(t->left); //L
        if(t->right!=NULL)
            preorder(t->right);//R
    }

}
void inorder(NODE *t)
{
    if(isempty(t))
        printf("Tree ie empty");
    else{

        if(t->left!=NULL)
            inorder(t->left); //L
        printf("%d ",t->data); //v
        if(t->right!=NULL)
            inorder(t->right);//R
    }
}
void postorder(NODE *t)
{
    if(isempty(t))
        printf("Tree ie empty");
    else{

        if(t->left!=NULL)
            postorder(t->left); //L
        if(t->right!=NULL)
            postorder(t->right);//R
         printf("%d ",t->data); //v
    }
}
void searchNode(NODE **t,int data,NODE **parent)
{//t is pointer pointing to node searched;
 //parent pointing to t's parent
    while((*t)->data!=data && *t!=NULL)
    {
        *parent=*t;
        if(data<(*t)->data)
                *t=(*t)->left;
        else
            *t=(*t)->right;
    }
}
NODE* inordersuccessor(NODE* s)
{
    //NODE *s=t;
    //if(s->right!=NULL)//not required
        s=s->right;
    while(s->left!=NULL)
        s=s->left;
    return s;
}
NODE* deleteNode(NODE *root,int data)
{
    NODE *t=root, *parent=NULL;
    if(data!=t->data)
        searchNode(&t,data,&parent);
    if(t==NULL)
    {
        printf("Data not found");
        return root;
    }
    //case 1:Leaf Node
    if(t->left==NULL && t->right==NULL)
    {
        if(parent==NULL)//root node
            root=NULL;
        else if(parent->left==t)//left child
            parent->left=NULL;
        else                    //right child
            parent->right=NULL;
        free(t);
    }
    //case 2:One child Node
    else if(t->left==NULL || t->right==NULL)//one child condition
    {
        if(parent==NULL)//root
        {
            if(t->left!=NULL)//left child
            {
                root=root->left;
                t->left=NULL;//optional
            }
            else
            {
              root=root->right;
              t->right=NULL;//optional
            }
        }
        else//Non root element
        {
            if(parent->left==t)//left child of parent
            {
                if(t->left!=NULL)//has left subtree
                    parent->left=t->left;
                else             //has right subtree
                    parent->left=t->right;
            }
            else//right child of parent
            {
                if(t->left!=NULL)
                    parent->right=t->left;
                else
                    parent->right=t->right;
            }
        }
        free(t);
    }
    else //case 3:Two node condition
    {
        NODE *s;
        int val;
        s=inordersuccessor(t);
        val=s->data;
        root=deleteNode(root,s->data);
        t->data=val;
    }
return root;
}
int main()
{
    int n,d,ch;
    NODE *root=NULL;
    printf("\nEnter the no of nodes");
    scanf("%d",&n);
    printf("\nEnter the data");
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&d);
        root=insertNode(root,d);
    }
    printf("\n");
    preorder(root);
    printf("\n");
    inorder(root);
    printf("\n");
    postorder(root);
    //Deletion
    do{
    printf("\nEnter the data to be deleted");
    scanf("%d",&d);
    root=deleteNode(root,d);
    printf("\n");
    preorder(root);
    printf("\nTo Continue press 1");
    scanf("%d",&ch);
    }while(ch);

}
