/* Roll no-301

   SetB Q.1	Write the simulation program for preemptive scheduling algorithm using
		Pre-emptive SJF. The arrival time and first CPU bursts of different jobs should be
		input to the system. Assume the fixed I/O waiting time (2 units).
		The next CPU burst should be generated using random function.
		The output should give the Gantt Chart, Turnaround Time and Waiting
		time for each process and average times. */

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

int finish,time,n,k,prev;

void getinput()
{
	int i;
	system("Clear");
	printf("\nEnter No.Of Processes : ");
	scanf("%d",&n);
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

int arrived()
{
	int i;
	for(i=0;i<n;i++)
	if(tab[i].at<=time && tab[i].tbt!=0)
	return 1;
	return 0;
}

int getmin(int t)
{
	int i,mini,min=99;
	for(i=0;i<n;i++)
	if(tab[i].at<=t && tab[i].tbt!=0 && tab[i].tbt<min)
	{
		min = tab[i].tbt;
		mini = i;
	}
	return mini;
}

void sort()
{
	struct Input t;
	int i,j;
	for(i=0;i<n;i++)
	for(j=0;j<n-i-1;j++)
	if(tab[j].at > tab[j+1].at)
	{
		t = tab[j];
		tab[j] = tab[j+1];
		tab[j+1] = t;
	}
}

void processinput()
{
	int i;
	finish=k=0;
	while(finish!=n)
	{
		if(arrived(time))
		{
			i = getmin(time);
			time++;
			tab[i].tbt--;
			tab[i].ct=time;
			seq[k].start=prev;
			seq[k].end = time;
			strcpy(seq[k++].pname,tab[i].pname);
			prev = time;
			if(tab[i].tbt==0)
			{
				finish++;
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
	}

}

void printoutput()
{
	int i;
	float AvgTAT=0,AvgWT=0;
	printf("\nProcess\tAT\tBT\tCT\tWT\tTAT");
	for(i=0;i<n;i++)
	{
		printf("\n%s\t%d\t%d\t%d\t%d\t%d",tab[i].pname,
	  	tab[i].at,
		tab[i].bt,
		tab[i].ct,
		tab[i].ct-tab[i].at-tab[i].bt,
                
		tab[i].ct-tab[i].at);
		AvgTAT += tab[i].ct-tab[i].at;
		AvgWT += tab[i].ct-tab[i].at-tab[i].bt;
	}
	AvgTAT/=n;
	AvgWT/=n;
	printf("\nAverage TAT = %f",AvgTAT);
	printf("\nAverage WT = %f",AvgWT);
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
        printf("\n\nGantt Chart\n|");
	for(i=0;i<j;i++)
	printf("%d\t%s\t%d|",seq1[i].start,seq1[i].pname,seq1[i].end);
}

void main()
{
	int i;
 	getinput();
	sort();
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

/*output:

Enter No.Of Processes : 4
Process Name : 1
Burst Time : 5
Arrival Time : 1
Process Name : 2
Burst Time : 1
Arrival Time : 0
Process Name : 3
Burst Time : 2
Arrival Time : 2
Process Name : 4
Burst Time : 4
Arrival Time : 3

Process AT      BT      CT      WT      TAT
2       0       1       1       0       1
1       1       5       8       2       7
3       2       2       4       0       2
4       3       4       12      5       9
Average TAT = 4.750000
Average WT = 1.750000

Gantt Chart
|0      2       1|1     1       2|2     3       4|4     1       8|8     4      12|

*/
