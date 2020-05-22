#include<stdio.h>
#include<stdlib.h>
void main()
{
	long int mem[100];
	int reg[4],cc[6]={0,0,0,0,0,1},opc,op1,op2,pc=0,i,count;
	char fname[20];
	FILE *fp;
	printf("Enter the file name: ");
	scanf("%s",fname);
	fp=fopen(fname,"r");
	if(fp==NULL)
	{
		printf("File does not exists\n");
		exit(0);
	}
	while(fscanf(fp,"%ld",&mem[pc++])!=EOF);
	fclose(fp);
	count=pc;
	pc=0;
	while(pc<=count)
	{
		opc=mem[pc]/10000;
		op1=(mem[pc]%10000)/1000;
		op2=mem[pc]%1000;
		switch(opc)
		{
			case 0: exit(0);
			case 1: reg[op1]+=mem[op2];
				pc++;
				break;
			case 2: reg[op1]-=mem[op2];
				pc++;
				break;
			case 3: reg[op1]*=mem[op2];
				pc++;
				break;
			case 4: reg[op1]=mem[op2];
				pc++;
				break;
			case 5: mem[op2]=reg[op1];
				pc++;
				break;
			case 6: if(reg[op1]<mem[op2])
				       cc[0]=1;
				if(reg[op1]<=mem[op2])
				       cc[1]=1;
				if(reg[op1]==mem[op2])
				       cc[2]=1;
				if(reg[op1]>mem[op2])
				       cc[3]=1;
				if(reg[op1]>=mem[op2])
				       cc[4]=1;
				pc++;
				break;
			case 7: if(cc[op1]==1)
				       pc=op2;
				else
					pc++;
				for(i=0;i<5;i++)
				       cc[i]=0;
				break;
			case 8: reg[op1]/=mem[op2];
				pc++;
				break;
			case 9: printf("\nEnter the value: ");
				scanf("%ld",&mem[op2]);
				pc++;
				break;
			case 10: printf("Result: %ld\n",mem[op2]);
				 pc++;
				 break;
		}
	}
}
