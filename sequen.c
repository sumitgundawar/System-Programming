

//contiguous File allocation technique using linked 

#include<stdio.h>
#include<stdlib.h> 

struct node
{
int file_name;
int data;
int is_free;
int size;
struct node* link;
};

struct node* defaultFile() 
{
struct node* temp = (struct node*)malloc( sizeof(struct node) );
temp->link = NULL;
temp->is_free=0;
temp->data='a';
temp->file_name=99;
return temp;
}

struct node* insert(struct node *rt, int size, int fname)
{
struct node* temp = rt,*tt= rt;
struct node* new_node = defaultFile();
int flag=0,act_size=0;
while( flag==0 && temp ) 
{
if( size && temp->is_free==0 ) 
{
flag=1; 
act_size = temp->size;
temp->size=size;
temp->is_free=1;
temp->file_name = fname;
new_node->link = temp->link;
new_node->size = act_size-temp->size;
temp->link = new_node;
}
temp = temp->link;
}
if( flag==0 )
{
printf("There is not partition available to allocation\n. Kindly do fragment to allocate memory\n");
}
return rt;
}

struct node* combine(struct node *rt,int fname) 
{
struct node *temp=rt,*nt=NULL,*temp1=temp->link;
int fname1=0,fname2=0;
while( temp1 ) 
{
if( temp->is_free==0 && temp1->is_free==0 ) 
{
fname1 = temp->file_name;
fname2 = temp1->file_name;
temp->file_name= fname1!=fname ? fname1 : fname2;
temp->size = temp->size+temp1->size;
temp->link = temp1->link;
//delete temp1;
temp1 = temp->link;
}
else
{
temp = temp->link;
temp1 = temp1->link;
}
}
return rt;
}

void printFiles(struct node* rt) 
{
struct node *temp = rt;
printf("Files name\tsize \n");
while( temp ) 
{
printf("  F%d\t\t%d\t\n",temp->file_name, temp->size); 
temp = temp->link;
}
}

struct node* deleteFiles(struct node* rt, int fname) 
{
struct node *temp = rt,*nt=NULL;
int flag=0;
while( temp && flag==0 ) 
{
if (temp->file_name==fname) 
{
temp->is_free=0;
flag=1;
}
temp = temp->link;
}
if( flag==0 )
{
printf("There doesnt exist any file with that name\n");
}
return combine(rt,fname); 
}

int main()
{
int flag,no,size,data;
struct node *root;
system("clear");
printf("Sequential File Allocation Method using linked list.\n");
root = defaultFile();
root->size=1000;
data=100;
flag=no=size=0;
while( flag==0 ) 
{
printf("\n 1.insert\n 2.Delete\n 3.Print files \n 4.Exit\n");
printf("Enter your choice no: ");
scanf("%d",&no);
//printf(" no is %d\n",no);
switch(no)
{
case 1:
printf("Enter file size\n");
scanf("%d",&size);
root = insert(root, size, data);
data = data+1;
break;
case 2:
printf("Enter file name to delete\n");
scanf("%d",&size);
root = deleteFiles(root, size);
printf("Deleted........\n");
break;
case 3:
printFiles(root);
break;
case 4:
flag=1;
printf("Quitting .......\n");
break;
default:
printf("Enter your choice no: ");
break;
}
} 
} 
