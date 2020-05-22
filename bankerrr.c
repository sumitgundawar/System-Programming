/*------------------------------------------------------------
 Set B :
Q.1) Consider the following snapshot of a system:
      Allocation           Max                Available
      A      B    C        A      B    C      A      B        C
P0    0      1    0        7      5    3      3      3        2
P1    2      0    0        3      2    2
P2    3      0    2        9      0    2
P3    2      1    1        2      2    2
P4    0      0    2        4      3    3
1) Display the contents of Need array.
2) Check whether the system is in safe state or not. If yes, give the safe
sequence.
3)If a request from process P1 arrives for (1,0,2) can it be immediately
granted?
-------------------------------------------------------------*/

#include<stdio.h>
int n,m;//n for no of process and m is for no of resources
int alloc[10][10],max[10][10],need[10][10];
int available[10],total[10],work[10],finish[10],seq[10],req[10];
int pno;
void accept()
{
	int i,j;
	printf("Enter no of process:");
	scanf("%d",&n);
	printf("Enter the no of resource type:");
	scanf("%d",&m);
	printf("Enter total instances of each resource type\n");
	for(j=0;j<m;j++)
	{
		printf("%c:",65+j);
		scanf("%d",&total[j]);
	}
	printf("Enter the allocation\n");
	for(i=0;i<n;i++)
	{
		printf("p%d:\n",i);
		for(j=0;j<m;j++)
		{
			printf("%c:",65+j);
			scanf("%d",&alloc[i][j]);
		}
	}
	printf("Enter max need:\n");
	for(i=0;i<n;i++)
	{
		 printf("p%d:\n",i);
                for(j=0;j<m;j++)
                {
                        printf("%c:",65+j);
                        scanf("%d",&max[i][j]);
                }
	}
}
void calc_avail()
{
	int i,j,s;
	for(j=0;j<m;j++)
	{
		s=0;
		for(i=0;i<n;i++)
			s += alloc[i][j];
			available[j]=total[j]-s;
		
	}
}
void calc_need()
{
	int i,j;
	for(i=0;i<n;i++)
		for(j=0;j<m;j++)
		need[i][j]=max[i][j]-alloc[i][j];
}
void print()
{
	int i,j;
	printf("\n\tAllocation\t\tMax\t\tNeed\n\t");
	for(i=0;i<m;i++)
	{
		for(j=0;j<m;j++)
		printf("%3c",65+j);
		printf("\t");
	}
	for(i=0;i<n;i++)
	{
		printf("\np%d\t",i);
		for(j=0;j<m;j++)
			printf("%3d",alloc[i][j]);
			printf("\t");
		for(j=0;j<m;j++)
			printf("%3d",max[i][j]);
                        printf("\t");
                for(j=0;j<m;j++)
        		printf("%3d",need[i][j]);
                        printf("\t");
	}
	printf("\nAvailable\n");
	 for(j=0;j<m;j++){
                        printf("%3c",65+j);
                        printf("\t");
			}
			printf("\n");
	 for(j=0;j<m;j++)
                      {  printf("%3d",available[j]);
                        printf("\t");
			}
}
int find()
{
	int i,j;
        for(i=0;i<n;i++)
        {
		if(!finish[i])
		{
	       	        for(j=0;j<m;j++)
        	        if(need[i][j]>work[j])
                	break;
			if(j==m) return i;
		}
	}
	return -1;
}
void bankers()
{
	int i,j,k=0;
	 for(i=0;i<n;i++)
              finish[i]=0;
         for(j=0;j<m;j++)
               work[j]=available[j];
	 while((i=find())!=-1)
	{
		printf("\nNeed%d(",i);
		for(j=0;j<m;j++)
			printf("%d,",need[i][j]);
		printf("\b)<=work(");
		for(j=0;j<m;j++)
			printf("%d,",work[j]);
			printf("\b)");
			finish[i]=1;
		for(j=0;j<m;j++)
			work[j] +=alloc[i][j];
		printf("\nwork(");
		for(j=0;j<m;j++)
			printf("%d,",work[j]);
			printf("\b)\nFinish(");
		for(j=0;j<n;j++)
			printf("%d,",finish[j]);
			printf("\b)");
			seq[k++]=i;
	}
	if(k==n)
	{
		printf("\n System is in safe state:\nsafe sequence:");
		for(j=0;j<n;j++)
		printf("p%d-",seq[j]);
	}
	else
	{
		printf("\n System is in unsafe state");
	}
}
main()
{
	int i,j;
	system("clear");
	accept();
	calc_avail();
	calc_need();
	print();
	bankers();
	printf("\n Enter process no:");
	scanf("%d",&pno);
	printf("Enter request of process p%d\n",pno);
	for(j=0;j<m;j++)
	{
		printf("%c:",65+j);
		scanf("%d",&req[j]);
	}
	for(j=0;j<m;j++)
		if(req[j]>need[pno][j]) break;
		if(j==m)
		{
			for(j=0;j<m;j++)
			if(req[j]>available[j]) break;
			if(j==m)
			{
				for(j=0;j<m;j++)
				{
					available[j]-=req[j];
					alloc[pno][j]+=req[j];
					need[pno][j]-=req[j];
				}
				print();
				bankers();
			}
			else
			{
				printf("\n Process p%d has to wait",pno);
			}
		}
		else
		{
			printf("\n Request of process p%d cannot be generated",pno);
		}
}
