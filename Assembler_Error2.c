#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char mnem[][12]={"START","ADD","SUB","MULT","MOVER","MOVEM","COMP","BC","DIV","READ","PRINT"};
char assd[][7]={"START","EQU","LTORG","ORIGIN","END"};
char reg[][5]={"AREG","BREG","CREG","DREG"};
int search_mnem(char Tok[])
{
	int i;
	for(i=0;i<11;i++)
	{
		if(strcmp(mnem[i],Tok)==0)
		return 1;
	}
	return -1;
}
int search_assd(char Tok[])
{
	int i;
	for(i=0;i<5;i++)
	{
		if(strcmp(assd[i],Tok)==0)
		return 2;
	}
	return -1;
}
int search_reg(char Tok[])
{
	int i;
	for(i=0;i<4;i++)
	{
		if(strcmp(reg[i],Tok)==0)
		return 3;
	}
	return -1;
}
void pass1(char fname[])
{
	FILE *fp=NULL;
	char Tok1[10],Tok2[10],Tok3[10],Tok4[10],Buff[80],*str;
	int n, value,i;
	int found,lno=0;
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
		lno++;
		switch(n)
		{ 
			case 4: 
				strcpy(Tok1,Tok2);
				strcpy(Tok2,Tok3);
				strcpy(Tok3,Tok4);
			case 3: 
				if(strcmp(Tok2,"DS")==0 || strcmp(Tok2,"DC")==0);
				else
					Tok2[strlen(Tok2)-1]='\0';
				if(strcmp(Tok1,"START")==0)
				{
					printf("\nInvalid Statement at line %d",lno);
					break;
				}
				else
				found=search_mnem(Tok1);
				if(found!=1)
				{
					if(strcmp(Tok2,"DS")!=0)
					{
						if(strcmp(Tok2,"DC")!=0)
						printf("\nInvalid Mnemonic at Line %d",lno);
					}
				}
				else	
				{
					found=search_reg(Tok2);
					if(found!=3)
					printf("\nInvalid Statement at Line %d",lno);
				}
				if(strcmp(Tok2,"DS")==0 || strcmp(Tok2,"DC")==0)
				{
					value=atoi(Tok3);
					if(value>0);
					else
					printf("\nInvalid Statement at Line %d",lno);
				}
				break;
			case 2: found=search_mnem(Tok1);
				if(found!=1)	//For Read, Print
					printf("\nInvalid Mnemonic at Line %d",lno);
		}
		strcpy(Buff,"");
	}
	fcloseall();
}	
void dispfile(char fname[])
{
	FILE *fp=NULL;
	char Buff[80];	
	int i;
	fp=fopen(fname,"r");
	if(fp==NULL)
	{
		printf("cannot open file");
		exit(0);
	}
	while(!feof(fp))
	{
		fgets(Buff,80,fp);
		printf("%s",Buff);
		strcpy(Buff,"");
	}
}

main()
{
	char fname[40];
	printf("Enter the filename: ");
	scanf("%s",fname);
	dispfile(fname);
	pass1(fname);
	printf("\n\n");
}
/*	OUTPUT:
	[root@localhost tysys]# ./a.out
	Enter the filename: assma2.txt
	START 100, 2
	READ A
	MOVER A, AREG
	BDD AREG, A
	A MOVEM AREG, '=2'
	STOP
	X DS 1
	Y DS 1
	END
 
	Invalid Statement at line 1
	Invalid Statement at Line 3
	Invalid Mnemonic at Line 4
*/
