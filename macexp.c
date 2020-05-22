/*
	Rollno: 175		Date: 15/09/2012 
	Assignment 5 Set C que 2
	Program for Macro Expansion.
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct MNT
{
	char MName[20];
	int PP,MDTP;
}mnt[5];
struct MDT
{
	char Opcode[15],Value[35];
}mdt[30];
char PNT[15][15],APT[10][15];
int  MDT_Ptr,MNT_Ptr,PNT_Ptr,APT_Ptr,MEC,m;
char FName[20],Buffer[80],tok1[35],tok2[35],tok3[35],temp[40];
FILE *fp;
int SearchMNT(char *s)
{	for(m=0; m<MNT_Ptr; m++)
	if(strcmp(s,mnt[m].MName)==0)
	return(m);
	return(-1);
}
int SearchPNT(char *s)
{
	for(m=0;m<PNT_Ptr;m++)
	if(strcmp(PNT[m],s)==0)
			return(m);
	return(-1);
}
void Make_PNT(char *s)
{
	int i=0,j=0,k=0;
	strcat(s,",");
	while(*s)
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
}
void Expand(int n)
{
	int a;
	MEC = mnt[n].MDTP;
	while(strcmp(mdt[MEC].Opcode,"MEND")!=0)
	{
		sscanf(mdt[MEC].Value,"%s %s",tok1,tok2);
		tok2[strlen(tok2)-1]='\0';
		a = atoi(strstr(tok2,",")+1);
		sprintf(temp,"%s %s",tok1,APT[a]);
		printf("+%s\t%s\n",mdt[MEC].Opcode,temp);
		MEC++;
	}
}
main()
{
	int i=0,j=0,k=0,n;
	printf("\nEnter Source File Name: ");
	scanf("%s",FName);
	fp=fopen(FName,"r");
	if(fp==NULL)
	{
		printf("FILE NOT FOUND!!");  exit(0);
	}
	printf("Before Expansion, Original Program: \n");
	while(fgets(Buffer,80,fp))
		printf("%s",Buffer);
	rewind(fp);
	printf("\n\nAfter Macro Expansion: \n");
	while(fgets(Buffer,80,fp))
	{
		n = sscanf(Buffer,"%s %s %s",tok1,tok2,tok3);
		if(strcmp(tok1,"MACRO")==0 && n==1)
		{
			fgets(Buffer,80,fp);
			sscanf(Buffer,"%s %s",tok1,tok2);
			strcpy(mnt[MNT_Ptr].MName,tok1);
			mnt[MNT_Ptr].MDTP = MDT_Ptr;
			Make_PNT(tok2);
		}
		else if(strcmp(tok1,"MEND")==0 && n==1)
		{
			strcpy(mdt[MDT_Ptr].Opcode,"MEND");
			strcpy(mdt[MDT_Ptr++].Value,"");
			PNT_Ptr = 0;
			MNT_Ptr++;
		}
		else if(tok3[0]=='&' && n==3)
		{
			tok2[strlen(tok2)-1]='\0';
			k = SearchPNT(tok3+1);
			if(k==-1)
			{
				printf("\nError: Parameter %s not found",tok3+1);
				exit(0);
			}
			sprintf(temp,"%s, (P,%d)",tok2,k);
			strcpy(mdt[MDT_Ptr].Opcode,tok1);
			strcpy(mdt[MDT_Ptr++].Value,temp);
		}
		else
		{
			k = SearchMNT(tok1);
			if(k==-1)
				printf("%s",Buffer);
			else
			{
				i=j=APT_Ptr=0;
				strcat(tok2,",");
				while(tok2[j])
				{
					if(tok2[j]==',')
					{
						temp[i]='\0';
						i=0;
						strcpy(APT[APT_Ptr++],temp);
					}
					else
						temp[i++] = tok2[j];
					j++;
				}
				if(APT_Ptr!=mnt[k].PP)
				{
					printf("\nPosition Parameters Missing");
					exit(0);
				}
				Expand(k);
			}
		}
	}
	fcloseall();

}
/*	OUTPUT:
[root@localhost tysys]# ./a.out
 
Enter Source File Name: macexp.txt
Before Expansion, Original Program:
MACRO
CALC &X,&Y,&Z
MOVER AREG, &X
ADD AREG, &Y
SUB AREG, &Z
MOVEM  AREG, &X
MEND
READ A
READ B
READ C
CALC A,B,C
PRINT A
PRINT B
STOP
A DS 1
B DS 1
C DS 1

After Macro Expansion:
READ A
READ B
READ C
+MOVER  AREG, A
+ADD    AREG, B
+SUB    AREG, C
+MOVEM  AREG, A
PRINT A
PRINT B
STOP
A DS 1
B DS 1
C DS 1
*/
