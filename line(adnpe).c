#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node
{
	char line[80];
	struct node *link;
}NODE;

char  fname[20], buffer[80], ch, t1[5], t2[5], t3[5], t4[5],fname1[20];
FILE *fp;
int len,changed,m,n,i,o,j,flag,t;
NODE *first,*last,*q,*flag1,*last1,*first1,*first2,*last2,*r;

NODE* getNODE(char *s)
{	
	NODE *temp;
	temp = (NODE*)malloc(sizeof(NODE));
	strcpy(temp->line,s);
	temp->link=NULL;
	return(temp);
}

void create()
{
	len=0;
	first=NULL;
	while(fgets(buffer,80,fp))
	{
	q=getNODE(buffer);
	if(first==NULL)
	{
		first = q;
	}
	else
	{
		last->link = q;
	}
	last = q;
	len++;
	}
	fclose(fp);
}

void createNew()
{
	if(flag==0)
	{
		first = NULL;
		len=0;
	}
	printf("Enter text (. To stop)\n");
	fflush(stdin);
	gets(buffer);
	while(strcmp(buffer,".")!=0)
	{
		q=getNODE(strcat(buffer,"\n"));
		if(first==NULL)
		{
			first=q;
		}
		else
		{
			last->link = q;
		}
			last=q;		
			fflush(stdin);
			gets(buffer);
			len++;
	}
			changed=1;
}

NODE* findNODE(int pos)
{
	j=1;
	q=first;
	while(q && j<pos)
	{
	   q = q->link;
	   j++;
	}
	return(q);
}

//void insertNODE(int no)
{
	first1=last1=NULL;
	printf("Enter text (. to stop)\n");
	fflush(stdin);
	gets(buffer);
	i = 0;
	while (strcmp(buffer, ".")!=0)
	{
	q = getNODE(strcat(buffer,"\n"));
	if(first1==NULL)
	{
		first1=q;
	}
	   else
	{
		last1->link = q;
	}
	last1 = q;
	fflush(stdin);
	gets(buffer);
	i++;
	}
	q =findNODE(no-1);
	last1->link = q->link;
	q->link=first1;
	len+=i;
	changed = 1;
	first1 = last1 = NULL;
}

void pasteNODE(int z)
{
	i=0;
	first2=NULL;
	q=first1;
	while(q)
	{
		r = getNODE(q->line);
		if(first2==NULL)
		{
			first2=r;
		}
		else
		{
			last2->link = r;
		}
		last2 = r;
		q=q->link;
		i++;
	}
	q=findNODE(z);
	last2->link = q->link;
	q->link=first2;
	len+=i;
	changed = 1;
}

void copyNODE(int x,int y)
{
	q=findNODE(x);
	first1 = NULL;
	i=1;
	while(q && i<=y-x+1)
	{
		r= getNODE(q->line);
		if(first1==NULL)
		{
			first1 = r;
		}
		else
		{
	
			last1->link = r;
		}
		last1 = r;
		q=q->link;
		i++;
	}
}

void duplicateNODES(int x, int y, int z)
{
	copyNODE(x,y);
	pasteNODE(z-1);
}//

void deleteNODES (int m, int n)
{
	r = findNODE(m==1?m:m-1);
	i=1;
	t=m==1?n-m:n-m+1;
	while(i<=t && r)
	{
	q = r->link;
	r->link = q->link;
	free(q);
	i++;
	len--;
	}
	if ( m==1)
	{
	r = first;
	first = first->link;
	free(r);
	}
	changed = 1;
}
//void moveNODES(int x,int y,int z)
{
	copyNODE(x,y);
	deleteNODES(x,y);
	pasteNODE(z-1);
}//

void save()
{
	if((fp=fopen(fname,"w"))==NULL)
	{
		printf("Unable to save file %s", fname);
	}
	else
	{
		q = first;
		while(q)
		{
			fputs(q->line,fp);
			q = q->link;
		}
		printf(" %s Saved successfully........\n",fname);
		changed = 0;
		fclose(fp);
	}
}

void dispNODES( int m,int n)
{
	q = findNODE(m);
	i = 0;
	while(q && i<=n-m)
	{
		printf("%d :%s",i+m,q->line);
		i++;
		q = q->link;
	}
	printf("\n");
}

//void dispPAT(char *pat)
{
	q=first;
	i=1;
	while(q)
	{
		if(strstr(q->line,pat))
		{
		printf("%d :%s",i,q->line);
		}
		q=q->link;
		i++;
	}
	
}//
void dispHelp()
{
	printf("\n 1)\ta\t\t\t- to append\n");
	printf("\n 2)\tp\t\t\t- to print\n");
	printf("\n 3)\ts\t\t\t- to save\n");
	printf("\n 4)\tq\t\t\t- exit\n");
}
main(int argc, char *argv[])
{
  
   strcpy(fname,argv[1]);
   if ((fp=fopen(fname, "r")) == NULL || argc==1)
   {
	printf(" File does not exist \n");
  
	createNew();
   }
   else
   {
   create();
   dispNODES(1,len);
   }
    while(1)
   {
	printf("? ");
	fflush(stdin);
	gets(buffer);
	n=sscanf(buffer, "%s %s %s %s",t1,t2,t3,t4);
	switch(n)
	{
	case 1:
		if ( strcmp(t1, "s")==0)
		{
			if (changed)
			  save();
			else
			  printf("Nothing to Save.....\n");
		}
		else if (strcmp(t1,"p")==0)
			dispNODES(1,len);
		else if (strcmp(t1,"a")==0)
		{
			flag = 1;
			createNew();
		}
		else if (strcmp(t1,"e")==0)
		{
			if (changed)
			{
			char t;
			printf("\n %s not saved. Save y/n? ",fname);
			scanf("%c",&t);
			if (t=='y')
			save();
			}
			exit(0);
		 }
		 else if(strcmp(t1,"h")==0)
			 dispHelp();
		 else
			 printf("Invalid options.......\n");
		 break;


	//case 2:
			if (strcmp(t1, "d")==0)
			{
				m = atoi(t2);
				deleteNODES(m,n);
			}
			else if (strcmp(t1,"f")==0)
					dispPAT(t2);
			else if (strcmp(t1,"i")==0)
			{
				m = atoi(t2);
				insertNODE(m);
			}
			else
					printf("Invalid options.......\n");
			break;

   case 3:
		  if (strcmp(t1, "p")==0)
		  {
			  m = atoi(t2);
			  n = atoi(t3);
			  dispNODES(m,n);
		  }
		  else if (strcmp(t1,"d")==0)
		  {
				m = atoi(t2);
				n = atoi(t3);
			   deleteNODES(m,n);
		  }
		  else if (strcmp(t1,"m")==0)
		  {
			  m = atoi(t2);
			  n = atoi(t3);
			  moveNODES(m,m,n);
		  }
		  else if (strcmp(t1,"c")==0)
		  {
			  m = atoi(t2);
			  n  = atoi(t3);
			  duplicateNODES(m,m,n);
		  }
		  else
		  printf("Invalid options.......\n");
		  break;

	case 4:
		   if (strcmp(t1, "m")==0)
		   {
			   m = atoi(t2);
			   n = atoi(t3);
			   o = atoi(t4);
			   moveNODES(m,n,o);
		   }
		   else if (strcmp(t1,"c")==0)
		   {
				m = atoi(t2);
				n = atoi(t3);
				o = atoi(t4);
				duplicateNODES(m,n,o);
		   }
		   else
		   printf("Invalid options.......\n");
		   break;//
		}
	}
}

