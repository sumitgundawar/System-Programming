#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct MNT
{
	char MName[20];
	int PP,MDTP;
}mnt[5];

/*struct KPDT
{
	char PName[15],Def[15];
}kpdt[15];*/

struct MDT
{
	char Opcode[15],Value[35];
}mdt[30];

char PNT[15][15],APT[10][15];
int MDT_Ptr,MNT_Ptr,PNT_Ptr,APT_Ptr,MEC,m;
char FName[20];
char Buffer[80],tok1[35],tok2[35],tok3[35];
char temp[40];
FILE *fp;

int SearchMNT(char *s)
{
	for(m=0;m<MNT_Ptr;m++)
		if(strcmp(s,mnt[m].MName)==0)
			return(m);
		return (-1);
}

int SearchPNT(char *s)
{
	for(m=0;m<PNT_Ptr;m++)
		if(strcmp(PNT[m],s)==0)
			return(m);
		return (-1);
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
			k=SearchPNT(temp);
			if(k==-1)
			{
				strcpy(PNT[PNT_Ptr++],temp);
				
			}
			else
			{
				printf("\n Error : Multiple Declaration of symbol %s in argument list ",temp);
				exit(0);
			}
		}
		
		else if(*s!='&')
			temp[i++]=*s;
		s++;
	}
	
	mnt[MNT_Ptr].PP =j;
}

void Expand(int n)
{
	int a;
	MEC=mnt[n].MDTP;
	while(strcmp(mdt[MEC].Opcode,"MEND")!=0)
	{
		sscanf(mdt[MEC].Value, "%s %s" ,tok1,tok2);
		tok2[strlen(tok2)-1]='\0';
		a=atoi(strstr(tok2,",")+1);
		sprintf(temp ,"%s %s" ,tok1,APT[a]);
		printf("+%s\t%s\n",mdt[MEC].Opcode,temp);
		MEC++;
		
	}
}

int main()
{
	int i=0,j=0,k=0,n;
	printf("\n Enter the source File name :");
	scanf("%s",FName);
	fp=fopen(FName,"r");
	while(fgets(Buffer,80,fp))
	{	
		n = sscanf(Buffer,"%s %s %s ",tok1,tok2,tok3);
		if(strcmp(tok1,"MACRO")==0 && n==1)
		{
			fgets(Buffer,80,fp);
			sscanf(Buffer, "%s %s",tok1,tok2);
			strcpy(mnt[MNT_Ptr].MName,tok1);
			mnt[MNT_Ptr].MDTP=MDT_Ptr;
			Make_PNT(tok2);
		}
		else if(strcmp(tok1,"MEND")==0 && n==1)
		{
			strcpy(mdt[MDT_Ptr].Opcode,"MEND");
			strcpy(mdt[MDT_Ptr++].Value,"");
			MNT_Ptr++;
			PNT_Ptr =0;
		}
		else if(tok3[0]=='&' && n==3)
		{
			tok2[strlen(tok2)-1]='\0';
			k=SearchPNT(tok3+1);
			if(k==-1)
			{
				printf("\n Error : Parameter %s not found ",tok3+1);
				exit(0);
			}
			
			sprintf(temp,"%s, (P,%d)",tok2,k);
			strcpy(mdt[MDT_Ptr].Opcode,tok1);
			strcpy(mdt[MDT_Ptr++].Value,temp);
		}
		else 
		{
			k=SearchMNT(tok1);
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
					temp[i++]=tok2[j];
				j++;
				}
				if(APT_Ptr!=mnt[k].PP)
				{
					printf("\n Positional parameter is missing");
					exit(0);
				}
				Expand(k);
			
			}
		}
	}
	fcloseall();	
	
}


/*OUTPUT:

 Enter the source File name :Expandmacro.txt
READ A
READ B
+MOVER  AREG, A
+MULT   AREG, B
+SUB    AREG, B
+MOVEM  AREG, A
PRINT A
STOP
A DS 1
B DS 1
*/
