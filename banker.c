/*
   SetA	Q.2) Consider the following snapshot of a system: 
     Allocation               Max                        Available
      A      B    C      D     A       B    C     D       A      B       C D
P0    0      0    1      2     0       0    1     2       1      5       2 0
P1    1      0    0      0     1       7    5     0
P2    1      3    5      4     2       3    5     6
P3    0      6    3      2     0       6    5     2
P4    0      0    1      4     0       6    5     6
1) Display the contents of Need array.
2) Check whether the system is in safe state or not. If yes, give the safe
sequence. */

#include<stdio.h>
int A[10][10],M[10][10],N[10][10],Av[10],work[10],Safe[10],Finish[10],nor,nop;

void AcceptData(int X[][10])
{
	int i,j;
	for(i=0;i<nop;i++)
	{
		printf("P%d\n",i);
		for(j=0;j<nor;j++)
		{
			printf("%c: ",65+j);
			scanf("%d",&X[i][j]);
		}
	}
}

void AcceptAvailability()
{
	int i;
	for(i=0;i<nor;i++)
	{
		printf("%c: ",65+i);
		scanf("%d",&Av[i]);
                work[i]=Av[i];
	}
}

void DisplayData()
{
	int i,j;
	printf("\n\tAllocation\t\tMax\t\tNeed\n");
	printf("\t");
	for(i=0;i<3;i++)
	{
		for(j=0;j<nor;j++)
		printf("%4c",65+j);
		printf("\t");
	}
	for(i=0;i<nop;i++)
	{
		printf("\nP%d\t",i);
		for(j=0;j<nor;j++)
		printf("%4d",A[i][j]);
		printf("\t");
		for(j=0;j<nor;j++)
		printf("%4d",M[i][j]);
		printf("\t");
		for(j=0;j<nor;j++)
		printf("%4d",N[i][j]);
	}
	printf("\nAvailable\n");
	for(j=0;j<nor;j++)
	printf("%4d",Av[j]);
}

void CalcNeed()
{
	int i,j;
	for(i=0;i<nop;i++)
	for(j=0;j<nor;j++)
	N[i][j] = M[i][j] - A[i][j];
}

int checkNeed(int pno)
{
	int i;
	for(i=0;i<nor;i++)
	if(N[pno][i] > work[i])
	return(0);
	return(1);
}

void Banker()
{
	int i=0,j=0,k=0,flag=0;
	while(flag<2)
	{
		if(!Finish[i])
		{
			printf("\nNeed%d(",i);
			for(j=0;j<nor;j++)
			printf("%d,",N[i][j]);
			if(!checkNeed(i))
			{
				printf("\b)>Work(");
				for(j=0;j<nor;j++)
				printf("%d,",work[j]);
				printf("\b)");
				printf("\nNeed Cannot Be Satisfied, Consider Next Process.");
			}
			else
			{
				printf("\b)<=Work(");
				for(j=0;j<nor;j++)
					printf("%d,",work[j]);
				printf("\b)");
				printf("\nNeed Can Be Satisfied, So Allocate Aequired Resources.");
				for(j=0;j<nor;j++)
				{
                                  	work[j]+=A[i][j];
				}
				for(j=0;j<nor;j++)
				printf("%4d",work[j]);
				Safe[k++] = i;
				Finish[i]=1;
			}
		}
		if((i+1)%nop == 0)
		flag++;
		i=(i+1)%nop;
	}
	if(k==nop)
	{
		printf("\nSystem Is In Safe State...");
		printf("\nSafe Sequence: ");
		for(i=0;i<k;i++)
		printf("P%d->",Safe[i]);
		printf("\b\b  ");
	}
	else
	{
		printf("\nSystem Is In Not Safe State...");
	}
}

void main()
{
	printf("\nEnter No.Of Processes & No.Of Resources : ");
	scanf("%d %d",&nop,&nor);
	printf("Enter Allocation\n");
	AcceptData(A);
	printf("Enter Max Requirement\n");
	AcceptData(M);
	printf("Enter Availability\n");
	AcceptAvailability();
	CalcNeed();
	DisplayData();
	Banker();
}
