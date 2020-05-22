/*
	Write a MACRO PREPROCESSOR for SMAC0, which reads a macro definition &
	main program in which macro is called. Define a macro with any number of
	positional and keyword parameters. Your program should display
	MNT (Macro Name Table), MDT(Macro Definition Table)  and KPT(Keyword
	Parameter Table) only.
*/

#include<stdio.h>
#include<conio.h>
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
		if(strcmpi(PNT[m],s)==0)
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
	getch();
}

void Print_KPDT()
{
	printf("\n---KEYWORD PARAMETER DEFAULT TABLE---");
	printf("\n#\tPName\tDef");
	printf("\n-------------------------------------");
	for(m=0;m<KPDT_Ptr;m++)
		printf("\n%d\t%s\t%s",m,kpdt[m].PName,kpdt[m].Def);
	printf("\n-------------------------------------");
	getch();
}

void Print_MDT()
{
	printf("\n-----------MACRO DEFINITION TABLE--------------");
	printf("\n#\tOpcode\tOperand");
	printf("\n-----------------------------------------------");
	for(m=0;m<MDT_Ptr;m++)
		printf("\n%d\t%s\t%s",m,mdt[m].Opcode,mdt[m].Value);
	printf("\n-----------------------------------------------");
	getch();
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

void main()
{
	int k=0,n;
	clrscr();
	printf("\nEnter Source File Name: ");
	scanf("%s",FName);
	fp=fopen(FName,"r");
	while(fgets(Buffer,80,fp))
	{
		n = sscanf(Buffer,"%s %s %s",tok1,tok2,tok3);
		if(strcmpi(tok1,"MACRO")==0 && n==1)
		{
			fgets(Buffer,80,fp);
			sscanf(Buffer,"%s %s",tok1,tok2);
			strcpy(mnt[MNT_Ptr].MName,tok1);
			mnt[MNT_Ptr].KPDTP = KPDT_Ptr;
			mnt[MNT_Ptr].MDTP = MDT_Ptr;
			Make_KPDT_PNT(tok2);
		}
		else if(strcmpi(tok1,"MEND")==0 && n==1)
		{
			strcpy(mdt[MDT_Ptr].Opcode,"MEND");
			strcpy(mdt[MDT_Ptr++].Value,"");
			MNT_Ptr++;
			PNT_Ptr = 0;
		}
		else if(tok2[0]=='&')
		{
			tok2[strlen(tok2)-1]='\0';
			k = SearchPNT(tok2+1);
			if(k==-1)
			{
				printf("\nError: Parameter %s not found",tok2+1);
				exit(0);
			}
			sprintf(temp,"(P,%d)",k);
			k = SearchPNT(tok3+1);
			if(k==-1)
			{
				printf("\nError: Parameter %s not found",tok3+1);
				exit(0);
			}
			sprintf(temp1,"%s, (P,%d)",temp,k);
			strcpy(mdt[MDT_Ptr].Opcode,tok1);
			strcpy(mdt[MDT_Ptr++].Value,temp1);
		}
		else if(strcmpi(tok1,"START")==0)
		{
			break;
		}
	}
	Print_MNT();
	Print_KPDT();
	Print_MDT();
	fclose(fp);
}
