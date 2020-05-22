#include<stdio.h>
#include<string.h>
struct process
{
  	char pname[10];
  	float bt,at,st,ft,wt,tat;
}p[100];
int n,i,last;
void input()
{
 	printf("\n Enter How Many Processes : ");
 	scanf("%d",&n);
 	for(i=0;i<n;i++)
  	{
    		printf("\n Enter Process Name ");
    		scanf("%s",&p[i].pname);
		printf("\n Enter CPU Burst Time ");
    		scanf("%f",&p[i].bt);
		printf("\n Enter Arrival Time ");
    		scanf("%f",&p[i].at);
  	}
}
void display()
{
   	printf("\n----------------------------------------------------\n"); 
   	printf("\nPName\tBT\tAT\n");
   	printf("\n----------------------------------------------------\n");  
	for(i=0;i<n;i++)
   	{
  		printf("\n  %s \t %.2f \t%.2f",p[i].pname,p[i].bt,p[i].at); 

   	}
  	printf("\n----------------------------------------------------\n");
}
void display1()
{ 
float swt=0,awt,stat=0,astat;
   	printf("\n----------------------------------------------------\n"); 
   	printf("\nPName\tBT\tAT\tST\tWT\tFT\tTAT\n");

   	printf("\n----------------------------------------------------\n");  

	for(i=0;i<n;i++)

   	{
		swt+=p[i].wt;

    		stat+=p[i].tat;

  		printf("\n  %s\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f",p[i].pname,p[i].bt,p[i].at,p[i].st,p[i].wt,p[i].ft,p[i].tat); 

   	}

  	printf("\n----------------------------------------------------\n");

  	printf("\nAverage Wait Time=%.2f\n",swt/n);

	printf("\nAverage Turn Around Time=%.2f\n",stat/n);

}


void sort1(int a)

{

  	int k,j;

	struct process t1;

	for(j=a+1;j<n;j++)

	{

 		for(k=j+1;k<n;k++)

 		{

   			if(p[j].bt>p[k].bt)

                	{

                        	t1=p[j];

                        	p[j]=p[k];

                        	p[k]=t1;

                	}

 		}

	}
}


void sort()

{ 

 	int j;

 	struct process t1,t2;

 	for(i=0;i<n;i++)

 	{

   		for(j=i+1;j<n;j++)

   		{

    			if(p[i].at>p[j].at)

       			{

        			t2=p[i];

        			p[i]=p[j];

        			p[j]=t2;

       			}

			else  if(p[i].at==p[j].at)

        		{

                		if(p[i].bt>p[j].bt)

                		{

                        		t1=p[i];

                       	 		p[i]=p[j];

                        		p[j]=t1;

                		}

        		}

			else 
			{
			
			}

  

   		}

 	}   

  	last = p[n-1].at;

}


void npsjf()
{

 	int time;
 	sort();
 	printf("\nGanttchart\n");
 	printf("|");
 	last = p[n-1].at;
 	p[0].st=p[0].at;
 	p[0].ft=p[0].st+p[0].bt; 
 	for(i=0;i<n;i++)
  	{
   		time=p[i].ft;
   		printf("%.2f  %s  %.2f | ",p[i].st,p[i].pname,p[i].ft);
  		if(time>last)
  		{
   			sort1(i);
   		}
   		if(p[i].ft >= p[i+1].at)
   		{
    			p[i+1].st=p[i].ft;
   		}
   		else
   		{
     			printf("-----|");
     			p[i+1].st=p[i+1].at;
  		}
   		p[i].wt=p[i].st-p[i].at;
   		p[i].tat=p[i].ft-p[i].at;
 		p[i+1].ft=p[i+1].st+p[i+1].bt;
   	}
}
void main()
{
  	input();
  	display();
  	npsjf();
  	display1();
	for(i=0;i<n;i++)
	{

		p[i].bt=rand()%10+1;

		p[i].at=p[i].ft+2;

	}

    	npsjf();

  	display1();

}
