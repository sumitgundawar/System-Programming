#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct Symtab
{
	char sym[10];
	int used, def;
}SymTab;
SymTab Sym[10]={0};
int SymPtr=0;
int InsertSymTab(char Tok1[])
{
	int i,val=-1;
	for(i=0;i<SymPtr;i++)
	{
		if(strcmp(Sym[i].sym,Tok1)==0)
			val=i;
	}
	if(val<0)
	{
		val=SymPtr;
		strcpy(Sym[SymPtr].sym,Tok1);
		SymPtr++;
	}
	return val;
}

void pass1(char fname[])
{
	FILE *fp=NULL;
	char Tok1[10],Tok2[10],Tok3[10],Tok4[10],Buff[80],*str;
	int n, val,i;
	int found;
	fp=fopen(fname,"r");
	if(fp==NULL)
	{
		printf("File Not Found!!!");
		exit(0);
	}
	while(!feof(fp))
	{
		fgets(Buff,80,fp);
		n=sscanf(Buff,"%s%s%s%s",Tok1,Tok2,Tok3,Tok4);
		switch(n)
		{ 
			case 4: val=InsertSymTab(Tok1);
				Sym[val].def+=1;
				val=InsertSymTab(Tok4);
				Sym[val].used=1;
				break;
			case 3: 
				if(strcmp(Tok1,"START")==0)
					break;
				if(strcmp(Tok2,"DS")==0 || strcmp(Tok2,"DC")==0)
				{
					val=InsertSymTab(Tok1);
					Sym[val].def+=1;
				}
				else 
				if(strcmp(Tok2,"EQU")==0)
				{
					val=InsertSymTab(Tok1);
					Sym[val].used=1;
					val=InsertSymTab(Tok3);
					Sym[val].used=1;
				}else
				if(strcmp(Tok1,"ORIGIN")!=0)
				{
					val=InsertSymTab(Tok3);
					Sym[val].used=1;
				}
				break;
			case 2: if(strcmp("START",Tok1)!=0)
				{
					SymPtr++;
					val=InsertSymTab(Tok2);
					Sym[val].used=1;
				}
				break;
		}
		strcpy(Buff,"");
	}
	fcloseall();
}	
void dispfile(char fname[])
{
	FILE *fp=NULL;
	char Buff[80],t1[20],t2[20],a1[20],a2[20],a3[20],a4[20];	
	int i,j;
	fp=fopen(fname,"r");
	if(fp==NULL)
	{
		printf("cannot open file");
		exit(0);
	}	
	fgets(Buff,80,fp);
	sscanf(Buff,"%s%s",t1,t2);
	i=atoi(t2);
	printf("%s",Buff);
	while(!feof(fp))
	{
		fgets(Buff,80,fp);
		sscanf(Buff,"%s%s%s%s",a1,a2,a3,a4);
		if(strcmp(a1,"END")!=0)
			printf("%d %s",i++,Buff);
		else
			printf("%s",Buff);
		strcpy(Buff,"");
	}
}
void DisplayError(char fname[])
{
	int i;
	for(i=0;i<SymPtr;i++)
	{
		if(Sym[i].used>=1 && Sym[i].def==0)
		printf("\nError: %s Used but not defined.",Sym[i].sym);
		if(Sym[i].used==0 && Sym[i].def>0)
		printf("\nWarning: %s Defined but not Used.",Sym[i].sym);
		if(Sym[i].def>1)
		printf("\nError: Redeclaration of Symbol %s",Sym[i].sym);
	}
	printf("\n\n");
}
main()
{
	char fname[40];
	printf("Enter the filename: ");
	scanf("%s",fname);
	dispfile(fname);
	pass1(fname);
	DisplayError(fname);
}
