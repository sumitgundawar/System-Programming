/*Write a MACRO PREPROCESSOR for SMAC0, which reads a macro definition &
main program in which macro is called. Your program should display SMAC0
program with expanded macro. Consider only positional parameters.

source file:

MACRO
CALC &X,&Y,&REG=BREG,&OP=ADD
MOVER &REG,&X
&OP &REG,&Y
MOVEM &REG,&X
MEND
READ A
READ B
CALC A,B,&REG=&BREG,&OP=MULT
STOP
A DS 1
B DS 1
END*/



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

void Print_MNT()
{
	printf("\n----------MACRO NAME TABLE--------------------------");
	printf("\n#\tMName\t#PP\t#KP\t#MDTP\tKPDTP");
	printf("\n----------------------------------------------------");
	for(m=0;m<MNT_Ptr;m++)
		printf("\n%d\t%s\t%d\t%d\t%d\t%d",
		m,mnt[m].MName,mnt[m].PP,mnt[m].KP,mnt[i].MDTP,mnt[i].KPDTP);
	printf("\n----------------------------------------------------");
}

void Print_KPDT()
{
	printf("\n---KEYWORD PARAMETER DEFAULT TABLE---");
	printf("\n#\tPName\tDef");
	printf("\n-------------------------------------");
	for(m=0;m<KPDT_Ptr;m++)
		printf("\n%d\t%s\t%s",m,kpdt[m].PName,kpdt[m].Def);
	printf("\n-------------------------------------");
}
void Print_PNT()
{
int i;
printf("\n\n********************************************************");
printf("\n\n\tPNTTAB");
printf("\n----------------------------\n");
for(i=0;i<PNT_Ptr;i++)
        {
        printf("\n%s",PNT[i]);
        }
}

void Print_MDT()
{
	printf("\n-----------MACRO DEFINITION TABLE--------------");
	printf("\n#\tOpcode\tOperand");
	printf("\n-----------------------------------------------");
	for(m=0;m<MDT_Ptr;m++)
		printf("\n%d\t%s\t%s",m,mdt[m].Opcode,mdt[m].Value);
	printf("\n-----------------------------------------------");
}

void Make_KPDT_PNT(char *s)
{
	int i=0,j=0,k=0;
	strcat(s,",");
	while(*s!='=')
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

int  main()
{
	int k=0,n;
	printf("\nEnter Source File Name: ");
	scanf("%s",FName);
	fp=fopen(FName,"r");
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
			PNT_Ptr=0;
		}
		else if(tok2[0]=='&')
		{
			tok2[strlen(tok2)-1]='\0';
			k = SearchPNT(tok2+1);
			sprintf(temp1,"%s, (P,%d)",temp,k);
			strcpy(mdt[MDT_Ptr].Opcode,tok1);
			strcpy(mdt[MDT_Ptr++].Value,temp1);
		}
	}
	Print_MNT();
	Print_PNT();
	Print_KPDT();
	Print_MDT();
	fclose(fp);
}
/*
*****************************************************************
output:
[root@fedora15 swapnil]# ./a.out

Enter Source File Name: macro1.txt

----------MACRO NAME TABLE--------------------------
#       MName   #PP     #KP     #MDTP   KPDTP
----------------------------------------------------
0       CALC    2       2       0       0
----------------------------------------------------
---KEYWORD PARAMETER DEFAULT TABLE---
#       PName   Def
-------------------------------------
0       REG     BREG
1       OP      ADD
-------------------------------------
-----------MACRO DEFINITION TABLE--------------
#       Opcode  Operand
-----------------------------------------------
0       MOVER   ADD, (P,-1)
1       &OP     ADD, (P,-1)
2       MOVEM   ADD, (P,-1)
3       MEND
-----------------------------------------------*/
