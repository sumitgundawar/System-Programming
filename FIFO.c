#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int pno;
	struct node *link;
}NODE;

NODE *first,*last;

int n,m,frames[10],mem[10][20],sp,faults;

void accept_info()
{
	int i;
	NODE *p;

	printf("Enter no.of references:");
	scanf("%d",&m);

	for(i=0;i<m;i++)
	{
		printf("ref[%d]=",i);
	
		p=(NODE*)malloc(sizeof(NODE));
		scanf("%d",&p->pno);
		p->link=NULL;

		if(first==NULL) first=p;
		else last->link=p;

		last=p;
	}

	printf("Enter no.of frames:");
	scanf("%d",&n);
}

int search(int pno)
{
	int i;
	for(i=0;i<n;i++)
		if(frames[i]==pno) return i;

	return -1;
}


void fifo()
{
	NODE *p;
	int i=0,j=0;

	p=first;
	while(p!=NULL)
	{
		if(search(p->pno)==-1)
		{
			frames[sp]=p->pno;
			sp=(sp+1)%n;
			faults++;

			for(j=0;j<n;j++)
				mem[j][i]=frames[j];
		}
		i++;
		p=p->link;
	}

	for(p=first;p!=NULL;p=p->link)
		printf("%4d",p->pno);

	printf("\n\n");

	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			if(mem[i][j]!=0) printf("%4d",mem[i][j]);
			else printf("    ");
		}
		printf("\n");
	}

	printf("\nTotal Page Faults=%d\n",faults);
}

void main()
{
	system("clear");
	accept_info();
	fifo();
}
