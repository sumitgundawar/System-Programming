#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct dir_entry
{
	char fname[20];
	int start,end,flag;
	struct dir_entry *link;
}DIR;

DIR *first,*last;

int fat[200],d,free_blocks;

void print_dir()
{
	DIR *p;
	int i;
	printf("-------------------------------------------\n");
	printf("Name\tStart\tEnd\tBlocks\n");
	printf("-------------------------------------------\n");

	p = first;
	while(p!=NULL)
	{
		if(p->flag==0)
		{
			printf("%s\t%d\t%d\t",p->fname,p->start,p->end);
			i=p->start;
			do
			{
				printf("%d->",i);
				i=fat[i];
			}while(i!=-1);
			printf("NULL\n");
		}
		p=p->link;
	}
	printf("-------------------------------------------\n");
}


void print_free_list()
{
	int i;
	printf("Free List:");
	for(i=0;i<d;i++)
		if(fat[i]==-999) printf("%d->",i);
	printf("NULL\n");
}

void main()
{
	DIR *p;
	char fname[20];
	int bno,i,j,ch;

	system("clear");
	printf("Enter no.of disk blocks:");
	scanf("%d",&d);

	for(i=0;i<d;i++)
		fat[i]=-999;

	free_blocks = d;
	while(1)
	{
		printf("1.Create\n");
		printf("2.Delete\n");
		printf("3.Display Free/Dir list\n");
		printf("4.Exit\n");
		printf("Enter ur choice (1-4):");
		scanf("%d",&ch);

		switch(ch)
		{
		case 1:
			printf("Enter file name:");
			scanf("%s",fname);
			printf("Enter no.of blocks:");
			scanf("%d",&bno);

			if(free_blocks>=bno)
			{
				free_blocks-=bno;
				p=(DIR*)malloc(sizeof(DIR));
				strcpy(p->fname,fname);
				p->flag=0;
				p->link=NULL;
				for(i=0;i<d;i++)
				{
					if(fat[i]==-999)
					{
						bno--;
						break;
					}
				}
				p->start=i;
				j=i;
				i++;
				while(bno!=0)
				{
					if(fat[i]==-999)
					{
						fat[j]=i;
						j=i;
						bno--;
					}
					i++;
				}
				fat[j]=-1;
				p->end=j;
				
				if(first==NULL) first=p;
				else last->link=p;
				
				last=p;
				printf("File %s created successfully.\n",fname);
			}
			else
			{
				printf("Failed to create file %s\n",fname);
			}
			break;
		case 2:
			printf("Enter file name to delete:");
			scanf("%s",fname);
			p=first;
			while(p!=NULL)
			{
				if(strcmp(p->fname,fname)==0 && p->flag==0)
					break;
				p=p->link;
			}
			if(p==NULL)
			{
				printf("File %s not found.\n",fname);
			}
			else
			{
				p->flag=1;
				bno=0;
				i=p->start;
				do
				{
					j=fat[i];
					fat[i]=-999;
					i=j;
					bno++;
				}while(i!=-1);
				free_blocks+=bno;
				printf("File %s deleted successfully.\n",fname);
			}
			break;
		case 3:
			print_dir();
			print_free_list();
			break;
		case 4:
			exit(0);
		}//switch
	}//while
}//main
