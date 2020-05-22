/*	Rollno: 175		DAte: 10/09/2012
	Assignment 5 Set B que 1 and 2
	Program to Read a assembly language Program, generate following tables:
	1)PNT  2)MNT  3)KPDT  4)MDT	*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct MNT
{
	char MName[20];
	int PP,KP,MDTP,KPDTP;
}mnt[5];

struct KPDT
{
	char PName[15],Def[15];
}kpdt[15];

struct MDT
{
	char Opcode[15],Value[35];
}mdt[30];

char PNT[15][15];
int  MDT_Ptr,MNT_Ptr,KPDT_Ptr,PNT_Ptr;
int  i,m;
char FName[20];
char Buffer[80], tok1[35], tok2[35], tok3[35];
char temp[40], temp1[40], temp2[40], temp3[40];
FILE *fp;

int SearchPNT(char *s)
{
	for(m=0;m<PNT_Ptr;m++)
		if(strcmp(PNT[m],s)==0)
			return(m);
	return(-1);
}

void Print_PNT()
{
	printf("\n---PNT TABLE---");
	printf("\n#\tPName");
	printf("\n---------------------------");
	for(m=0;m<PNT_Ptr;m++)
		printf("\n(P,%d) \t %s",m+1,PNT[m]);
	printf("\n---------------------------");
	getchar();
}

void Print_MNT()
{
	printf("\n----------MACRO NAME TABLE---------------------");
	printf("\n#\tMName\t#PP\t#KP\t#MDTP\tKPDTP");
	printf("\n-----------------------------------------------");
	for(m=0;m<MNT_Ptr;m++)
	printf("\n%d\t%s\t%d\t%d\t%d\t%d",m,mnt[m].MName,mnt[m].PP,mnt[m].KP,mnt[i].MDTP,mnt[i].KPDTP);
	printf("\n-----------------------------------------------");
	getchar();
}

void Print_KPDT()
{
	printf("\n---KEYWORD PARAMETER DEFAULT TABLE---");
	printf("\n#\tPName\tDef");
	printf("\n-------------------------------------");
	for(m=0;m<KPDT_Ptr;m++)
		printf("\n%d\t%s\t%s",m,kpdt[m].PName,kpdt[m].Def);
	printf("\n-------------------------------------");
	getchar();
}

void Print_MDT()
{
	printf("\n-------MACRO DEFINITION TABLE----------");
	printf("\n#\tOpcode\tOperand");
	printf("\n---------------------------------------");
	for(m=0;m<MDT_Ptr;m++)
		printf("\n%d\t%s\t%s",m,mdt[m].Opcode,mdt[m].Value);
	printf("\n---------------------------------------");
	getchar();
}

void Make_KPDT_PNT(char *s)
{
	int i=0,j=0,k=0;
	strcat(s,",");
	while(*s && *s!='=')
	{
		if(*s==',')
		{   
			temp[i]='\0';
			j++;
			i=0;
			k = SearchPNT(temp);
			if(k==-1)
				strcpy(PNT[PNT_Ptr++],temp);
			else
			{
				printf("\nError: Multiple Declaration of Symbol %s in Argument List",temp);
				exit(0);
			}
		}
		else if(*s!='&')
			temp[i++]=*s;
		s++;
	}
	mnt[MNT_Ptr].PP = j;
	j=0;
	while(*s)
	{
		if(*s=='=')
		{
			temp[i]='\0';
			i=0;
			k = SearchPNT(temp);
			if(k==-1)
			{
				strcpy(PNT[PNT_Ptr++],temp);
				strcpy(kpdt[KPDT_Ptr].PName,temp);
			}
			else
			{
				printf("\nError: Multiple Declaration of Symbol %s in Argument List",temp);
				exit(0);
			}
		}
		else if(*s==',')
		{
			temp[i]='\0';
			j++;
			i=0;
			strcpy(kpdt[KPDT_Ptr++].Def,temp);
		}
		else if(*s!='&')
			temp[i++]=*s;
		s++;
	}
	mnt[MNT_Ptr].KP = j;
}

int main()
{
	int k=0,n;
	system("clear");
	printf("\nEnter Source File Name: ");
	scanf("%s",FName);
	fp=fopen(FName,"r");
	if(fp==NULL)
	{
		printf("FILE NOT FOUND!!!"); exit(0);
	}
	printf("Contents in %s:\n",FName);
	while(fgets(Buffer,80,fp))
		printf("%s",Buffer);
	rewind(fp);
	while(fgets(Buffer,80,fp))
	{
		n = sscanf(Buffer,"%s %s %s",tok1,tok2,tok3);
		if(strcmp(tok1,"MACRO")==0 && n==1)
		{
			fgets(Buffer,80,fp);
			sscanf(Buffer,"%s %s",tok1,tok2);
			strcpy(mnt[MNT_Ptr].MName,tok1);
			mnt[MNT_Ptr].KPDTP = KPDT_Ptr;
			mnt[MNT_Ptr].MDTP = MDT_Ptr;
			Make_KPDT_PNT(tok2);
		}
		else if(strcmp(tok1,"MEND")==0 && n==1)
		{
			strcpy(mdt[MDT_Ptr].Opcode,"MEND");
			strcpy(mdt[MDT_Ptr++].Value,"");
			MNT_Ptr++;
			//PNT_Ptr = 0;
		}
		else if(tok2[0]=='&')
		{      m=0;
			while(m<strlen(tok2))
			{  
				tok2[m]=tok2[m+1];
				m++;}  
				m=0;
				while(m<strlen(tok3))
				{  
					tok3[m]=tok3[m+1];
					m++;
				}   
				k = SearchPNT(tok2);
				if(k==-1)
				{
					printf("\nError: Parameter %s not found",tok2);
					exit(0);
				}
				sprintf(temp,"(P,%d)",k+1);
				k = SearchPNT(tok3);
				if(k==-1)
				{
					printf("\nError: Parameter %s not found",tok3);
					exit(0);
				}
				sprintf(temp1,"%s, (P,%d)",temp,k+1);
				strcpy(mdt[MDT_Ptr].Opcode,tok1);
				strcpy(mdt[MDT_Ptr++].Value,temp1);
		}
		else if(strcmp(tok1,"START")==0)
		{
			break;
		}
	}
	Print_PNT();
	Print_MNT();
	Print_KPDT();
	Print_MDT();    
	fclose(fp);
}
/*	OUTPUT:
[root@localhost tysys]# ./a.out
                                                                                                            
Enter Source File Name: expand.txt
Contents in expand.txt:
MACRO
CALC &X,&Y,&Z,&REG=BREG,&OP=ADD
MOVER &REG &X
&OP &REG &Y
MOVEM &REG &X
MEND
READ A
READ B
CALC A,B,&OP=MULT
STOP
A DS 1
B DS 1
END
                                                                                                              
---PNT TABLE---
#       PName
----------------------
(P,1)    X
(P,2)    Y
(P,3)    Z
(P,4)    REG
(P,5)    OP
----------------------

----------MACRO NAME TABLE---------------------
#       MName   #PP     #KP     #MDTP   KPDTP
-----------------------------------------------
0       CALC    3       2       0       0
-----------------------------------------------
 
---KEYWORD PARAMETER DEFAULT TABLE---
#       PName   Def
-------------------------------------
0       REG     BREG
1       OP      ADD
-------------------------------------
 
-------MACRO DEFINITION TABLE----------
#       Opcode  Operand
---------------------------------------
0       MOVER   (P,4), (P,1)
1       &OP     (P,4), (P,2)
2       MOVEM   (P,4), (P,1)
3       MEND
---------------------------------------		*/


