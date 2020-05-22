#include<stdio.h>
#include<stdlib.h>

struct node
{
	int data,freq;
	struct node *next;
}*H=NULL;

int cnt;

#define newnode (struct node *)malloc(sizeof(struct node))

void create(int n)
{
	int i;
	struct node *A,*B;
	A=newnode;
	A->next=NULL;
	A->data=-1;
	A->freq=0;
	B=A;
	for(i=1;i<n;i++)
	{
		B->next=newnode;
		B=B->next;
		B->data=-1;
		B->freq=0;
	}
	B->next=NULL;
	H=A;
}

void display()
{
	struct node *F=H;
	while(F!=NULL)
	{
		printf("%d %d\t",F->data,F->freq);
		F=F->next;
	}
}

void sort()
{
	struct node *F,*S;
	int temp1,temp2;
	
	for(F=H;F!=NULL;F=F->next)
	{
		for(S=F->next;S!=NULL;S=S->next)
		{
			if(F->freq > S->freq)
			{
				temp1=F->data;
				temp2=F->freq;
				
				F->data=S->data;
				F->freq=S->freq;
				
				S->data=temp1;
				S->freq=temp2;
			}
		}
	}
}
				

void process(int no)
{
	struct node *F=H,*S;
	int flag=0;
	
	while(F!=NULL)
	{
		if(F->data == -1)
		{
			F->data=no;
			F->freq=1;
			cnt++;
			flag=1;
			break;
		}
		F=F->next;
	}

	if(flag == 0)
	{
		F=H;
		while(F!=NULL)
		{
			if(F->data == no)
			{
				F->freq++;
				sort();
				break;
			}
			F=F->next;
		}
		
		if(F == NULL)
		{
			F=H;
			S=F->next;
			
			while(S!=NULL)
			{
				F->data=S->data;
				F->freq=S->freq;
				F=F->next;
				S=S->next;
			}
			F->data=no;
			F->freq=1;
			cnt++;
			sort();
		}
	}
}


main()
{
	int n,no,num;
	printf("\nEnter total number of frames required:");
	scanf("%d",&n);
	printf("\nEnter total number of pages:");
	scanf("%d",&num);
	create(n);
	
	do
	{
		printf("\n\nEnter Page number:");
		scanf("%d",&no);
		if(no != -1)
		{
			process(no);
			display();
			printf("\tPage Fault:%d",cnt);
		}
	}while(no!= -1);
}
