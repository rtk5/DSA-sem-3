#include <stdio.h>
#include<stdlib.h>
#include<string.h>
struct student
{
  char name[20];
  int id;
  int sem;
  struct student *link;
};

typedef struct student * STUDENT;

STUDENT getnode()
{
  STUDENT x;
  x=(STUDENT)malloc(sizeof(struct student));
  if(x==NULL)
  {
    printf("no memory");
    exit(0);
  }
  return x;
}

STUDENT insert_front(char *name,int id,int sem, STUDENT first)
{
  STUDENT temp;
  temp=getnode();
  strcpy(temp->name,name);
  temp->id=id;
  temp->sem=sem;
  temp->link=first;
  first=temp;
  return first;
}

STUDENT insert_rear(char *name,int id,int sem, STUDENT first)
{
  STUDENT temp;
  STUDENT cur;
  temp=getnode();
  strcpy(temp->name,name);
  temp->id=id;
  temp->sem=sem;
  temp->link=NULL;
  if(first==NULL)
  {//first=temp;return first;
    return temp;
  }
  cur=first;
  while(cur->link!=NULL)
  {
    cur=cur->link;
  }
  cur->link=temp;
  return first;
  }

STUDENT insert_pos(char *name,int id,int sem,int pos, STUDENT first)
{
  STUDENT temp;
  STUDENT prev,cur;
  int count;
  temp=getnode();
  strcpy(temp->name,name);
  temp->id=id;
  temp->sem=sem;
  temp->link=NULL;
  if(first==NULL && pos==1)
  return temp;
  if(first==NULL)
  {
  printf("invalid position/list is empty");
  return first;
  }
  if(pos==1)
  {
  temp->link=first;
  return temp;
  }
  count=1;
  prev=NULL;
  cur=first;
  while(cur!=NULL && count!=pos)
  {
    prev=cur;
    cur=cur->link;
    count++;
  }
  if(count==pos)
  {
    prev->link=temp;
    temp->link=cur;
    return first;
  }
  printf("invalid position\n");
  return first;
}
void display(STUDENT first)
{
  STUDENT temp;
  if(first==NULL);
  {
  printf("NO record");
  return;
  }
  for (temp=first;temp!=NULL;temp=temp->link)
  {
    printf("%s%d%d\n",temp->name,temp->id,temp->sem);
  }
}
void main()
{
  STUDENT first=NULL;
  int choice, id,sem,pos;
  char name[20];
  for(;;)
  {
    printf("1:insert_front\n");
    printf("2:insert_rare\n");
    printf("3:insert_pos\n");
    printf("4:display\n");
    printf("5:exit\n");
    printf("enter your choice\n");
    scanf("%d",&choice);
    if(choice==1||choice==2||choice==3);
    {
      printf("enter student information");
      printf("Name:");
      scanf("%s",name);
      printf("ID:");
      scanf("%d",&id);
      printf("Sem:");
      scanf("%d",&sem);
    }
    switch(choice)
    {
      case 1: first=insert_front(name,id,sem,first);
                break;
      case 2: first=insert_rear(name,id,sem,first);
                break;
      case 3: printf("enter the position\n");
              scanf("%d",&pos);
              first=insert_pos(name,id,sem,pos,first);
      case 4: display(first);
              break;
      case 5: exit(0);
              break;
    }
  }
}