/*
   SetB Q.2 	Write the simulation program for preemptive scheduling algorithm
   		using Round Robin with time quantum of 2 units. The arrival time
   		and first CPU bursts of different jobs should be input to the
   		system. Assume the fixed I/O waiting time (2 units). The next CPU
   		burst should be generated using random function. The output
   		should give the Gantt Chart, Turnaround Time and Waiting time
   		for each process and average times. */

#include<stdio.h>
#include<string.h>
struct Input
{
	char pname[10];
	int  bt,at,ct,tbt;
}tab[5];

struct Sequence
{
	int start,end;
	char pname[10];
}seq[100],seq1[20];

int finish,time,n,k,prev,q;

void getinput()
{
	int i;
	printf("\nEnter No.Of Processes : ");
	scanf("%d",&n);
	printf("Enter Time Quantum : ");
	scanf("%d",&q);
	for(i=0;i<n;i++)
	{
		printf("Process Name : ");
		scanf("%s",tab[i].pname);
		printf("Burst Time : ");
		scanf("%d",&tab[i].bt);
		printf("Arrival Time : ");
		scanf("%d",&tab[i].at);
		tab[i].tbt = tab[i].bt;
	}
}

void printinput()
{
	int i;
	printf("\nProcess\tBT\tAT");
	for(i=0;i<n;i++)
	printf("\n%s\t%d\t%d",tab[i].pname,tab[i].tbt,tab[i].at);
}

void sort()
{ 
 	int i,j;
 	struct Input t;
 	for(i=0;i<n;i++)
 	{
   		for(j=i+1;j<n;j++)
   		{
    			if(tab[i].at>tab[j].at)
       			{
        			t=tab[i];
        			tab[i]=tab[j];
        			tab[j]=t;
       			}
  		}
 	}   
}

void printoutput()
{
	int i;
	float AvgTAT=0,AvgWT=0;
	printf("\nProcess\tAT\tBT\tCT\tTAT\tWT");
	for(i=0;i<n;i++)
	{
		printf("\n%s\t%d\t%d\t%d\t%d\t%d",tab[i].pname,
	  	tab[i].at,
		tab[i].bt,
		tab[i].ct,
		tab[i].ct-tab[i].at,
		tab[i].ct-tab[i].at-tab[i].bt);
		AvgTAT += tab[i].ct-tab[i].at;
		AvgWT += tab[i].ct-tab[i].at-tab[i].bt;
	}
	AvgTAT/=n;
	AvgWT/=n;
	printf("\n\nAverage TAT = %f",AvgTAT);
	printf("\nAverage WT = %f",AvgWT);
}

int arrived(int t)
{
	int i;
	for(i=0;i<n;i++)
	if(tab[i].at<=t && tab[i].tbt!=0)
	return 1;
	return 0;
}

void processinput()
{
	int i=0,j;
	finish = k = 0;
	while(finish!=n)
	{
		if(arrived(time))
		{
			if(tab[i].tbt!=0)
			{
				for(j=0;j<q;j++)
				{
					time++;
					tab[i].tbt--;
					seq[k].start=prev;
					seq[k].end = time;
					strcpy(seq[k++].pname,tab[i].pname);
					prev = time;
					tab[i].ct=time;
					if(tab[i].tbt==0)
					{
						finish++;
						break;
					}
				}
			}
		}
		else
		{
			time++;
			seq[k].start=prev;
			seq[k].end = time;
			strcpy(seq[k++].pname,"*");
			prev = time;
		}
		if(time < tab[(i+1)%n].at)
		{
			i=0;
			while(tab[i].tbt!=0 && finish!=n)
				i++;
		}
		else
		i = (i+1)%n;
	}
}

void ganttchart()
{
	int i,j=1;
	seq1[0] = seq[0];
	for(i=1;i<k;i++)
	{
		if(strcmp(seq1[j-1].pname,seq[i].pname)==0)
		seq1[j-1].end = seq[i].end;
		else
		seq1[j++] = seq[i];
	}
        printf("\n\nGanttchart\n\n|");
	for(i=0;i<j;i++)
	printf("%d  %s  %d|",seq1[i].start,seq1[i].pname,seq1[i].end);
}

void main()
{
	int i;
	getinput();
	sort();
        printinput();
	processinput();
	printoutput();
	ganttchart();
	for(i=0;i<n;i++)
	{
		tab[i].tbt = tab[i].bt=rand()%10+1;
		tab[i].at=tab[i].ct+2;
	}
	processinput();
	printoutput();
	ganttchart();
}

