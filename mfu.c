/*Implementation of MFU */

#include<stdio.h>
#include<stdlib.h>
int *frame,no,pno;
int pagefault=0;
struct pro
{
 	int page,refcount,addtime;
};
struct pro *reptr;
void accept()
{
 	int *temp;
 	printf("\n Enter The Number Of Pages : ");
 	scanf("%d",&no);
 	frame=(int *)malloc(no * sizeof(int));
 	if(frame==NULL)
  	{
    		printf("No Space Available...");
    		exit(1);
  	}
  	printf("\n Enter the Pages : ");
  	for(temp=frame;temp<frame+no;temp++)
      	scanf("%d",temp);
  	printf("\n Enter The No Of Page Frames : ");
  	scanf("%d",&pno);
  	reptr=(struct pro *)malloc(pno * sizeof(struct pro));
	if(reptr==NULL)
  	{
   		printf("No Space Available....");
   		exit(1);
  	}
}

int notin(int p)
{
  	struct pro *ptr;
  	for(ptr=reptr;ptr<reptr+pno;ptr++)
   	{
     		if(ptr->page==p)
     		{
      			ptr->refcount++;
      			return 0;
     		}
   	}
 	return 1;
}

int frameisfull()
{
 	struct pro *ptr;
 	int i;
 	for(ptr=reptr,i=0;ptr<reptr+pno;ptr++,i++)
  	{
   		if(ptr->page==0)
    		{
      			return i; 
    		}
  	} 
 	return -1;
}

int removel()
{
  	struct pro *ptr;
  	int maxref=0,t=0,i,m=0;
 	for(i=0,ptr=reptr;i<no;i++)
  	{
   		if(ptr->refcount>=maxref)
   		{
    			if(ptr->refcount==maxref && ptr->addtime <=m)
     			{
      				t=i;
      				m=ptr->addtime;
     			}
    			else
      			if(ptr->refcount>maxref)
      			{
       				t=i;
       				m=ptr->addtime;
       				maxref=ptr->refcount;
      			}
   		}
   		ptr++;
  	} 
  	return t;
}

void addinto(int p,int pos)
{
  	struct pro *ptr;
  	int i;
  	static int time=0;
  	ptr=reptr;
  	for(i=0;i!=pos;i++)ptr++;
  	ptr->page=p;
  	ptr->refcount=1;
  	ptr->addtime=time;
  	time++;
}

void printframe()
{
  	struct pro *ptr;
  	int i;
  	ptr=reptr;
  	printf("\npa||ref||int|\n");
  	for(i=0;i<pno;i++)
   	{
     		printf("\n%d||%d||%d||\n",ptr->page,ptr->refcount,ptr->addtime);
     		ptr++;
   	}
}

void mfu()
{
  	int *p;
  	int i=0;
  	int pos=0;
  	p=frame;
  	while(i<no)
  	{
   		if(notin(p[i]))
   		{
      			if((pos=frameisfull())==-1)
        		pos=removel();
      			addinto(p[i],pos);
      			printf("\n Page Fault Occured.\nChanged Frame is : ");
      			printframe();
      			pagefault++;
   		}
   		else
   		printf("\nNo Page Fault Occured As %d Is Already There.",p[i]);
   		i++;
  	}
  	printf("\n Total Number Of Page Faults Are : %d",pagefault);
}

int main()
{
 	system("Clear");
  	accept();
  	mfu();
}
