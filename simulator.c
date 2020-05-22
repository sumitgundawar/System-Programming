#include<stdio.h>
#include<stdlib.h>
long int mem[500];
FILE *fp,*fp1;
char fname[20];
int opcode,op1,op2,pc=0,i,j,temp,n1;
int cc[6]={0,0,0,0,0,1},reg[4];
void load()
{
    printf("Enter the file name:");
    scanf("%s",fname);
    fp=fopen(fname,"r");
    if(fp==NULL)
    {
        printf("Error in Opening File:\n");
        exit(0);
    }
    while(fscanf(fp,"%d",&mem[pc++])!=EOF);
    fclose(fp);
    printf("Total Number of lines: %d:\n",(pc-1));
}
void trace()
{
    printf("Value Of Register is %d\n",reg[op1]);
}
void execute()
{
    for(i=0;i<pc;i++)
    {
        opcode=mem[i]/10000;
        op1=(mem[i]%10000)/1000;
        op2=(mem[i]%10000)%1000;
        switch(opcode)
        {
            case 0: exit(0);
            break;
            case 1: reg[op1]=reg[op1]+mem[op2];
            break;
            case 2: reg[op1]=reg[op1]-mem[op2];
            break;
            case 3: reg[op1]=reg[op1]*mem[op2];
            break;
            case 4: reg[op1]=mem[op2];
            break;
            case 5: mem[op2]=reg[op1];
            break;
            case 6: if(reg[op1]<mem[op2])
                    cc[0]=1;
                else
                    cc[0]=0;
                if(reg[op1]<=mem[op2])
                    cc[1]=1;
                else
                    cc[1]=0;
                if(reg[op1]==mem[op2])
                    cc[2]=1;
                else
                    cc[2]=0;
                if(reg[op1]>mem[op2])
                    cc[3]=1;
                else
                    cc[3]=0;
                if(reg[op1]>=mem[op2])
                    cc[4]=1;
                else
                    cc[4]=0;
            break;
            case 7: if(cc[op1]==0)
                    i=op2-1;//Jump on label.
                for(j=0;j<5;j++)
                    cc[i]=0;
            break;
            case 8: reg[op1]=reg[op1]/mem[op2];
            break;
            case 9: printf("Enter the value:");
                scanf("%d",&mem[op2]);
            break;
            case 10: printf("Result is: %d.\n",mem[op2]);
            break;
            case 11:temp=reg[op1];
                reg[op1]=mem[op2];
                mem[op2]=temp;
                break;
            case 12:reg[op1]=reg[op1]+1;
                break;
            case 13: reg[op1]=reg[op1]-1;
                 break;
            case 14:mem[op2]=mem[op2]+1;
                break;
            case 15:mem[op2]=mem[op2]-1;
                break;
            case 16:mem[op2]=mem[op2]+reg[op1];
                break;
            case 17:mem[op2]=reg[op1]-mem[op2];
                break;
            case 18:mem[op2]=mem[op2]*reg[op1];
                break;
            case 19:mem[op2]=reg[op1]/mem[op2];
                break;
            case 20:printf("%d",reg[op1]);
                break;
            case 21: printf("Enter the value:\n");
                 break;
            case 22:reg[op1]=0;
                break;
            case 23:reg[op1]=1;
                break;
            default: printf("You Entered Wrong Code:\n");
        }
        trace();
    }
}
void print()
{
    for(i=0;i<pc;i++)
        printf("%ld\n",mem[i]);
}
void accept()
{
    /*
        NOTE:
        After accepting and Saving the value into a file exit the program,
        If Not, then we cant load that file (accepted) as a result the execution does not occur.
    */
    long int rom[900];
    printf("Enter how many number lines of code:");
    scanf("%d",&n1);
    printf("Enter the code:\n");
    for(i=0;i<n1;i++)
        scanf("%ld",&rom[i]);
    char fname1[20];
    printf("\nEnter file name to write sorted list: ");
    scanf("%s",fname1);
    fp1=fopen(fname1,"w");
    for(i=0;i<n1;i++)
        fprintf(fp1,"%ld\n",rom[i]);

}
int main()
{
    int op;
    while(1)
    {
        printf(" 1:ACCEPT.\n 2:LOAD.\n 3:PRINT.\n 4:EXECUTE.\n 5:EXIT.\n Enter your option:\n");
        scanf("%d",&op);
        switch(op)
        {
            case 1: accept();
                break;
            case 2: load();
                break;
            case 3: print();
                break;
            case 4: execute();
                break;
            case 5:exit(0);
                break;
            default: printf("You entered Wrong Option:\n");
        }
    }
}
