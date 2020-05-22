
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define OP 0
#define REG 1
#define INDEX 2

char optab[15][8]={"stop","add","sub","mul","mover","movem","comp","bc","div","read","print","ds","dc","start","end"};

char regtab[4][5]={"Areg","Breg","Creg","Dreg"},sfname[30],tfname[30],instruction[30],temp[20];

char reloptab[6][4]={"LT","LE","EQ","GT","GE","Any"},w1[10],w2[10],w3[10],w4[10];

long int IC[1000][3],TC[1000];

int LC=0,PC=0,START=0,tcnt,e,symcnt,op,r,endflag=0;
FILE *fp=NULL;         
struct SYMBOL
{
	char symbol[10];                     
	int address,define,used,length,value;
}symtab[40];

void error(int errorcode, char w[])     
{
	++e;                     
	switch(errorcode)
	{
		case  1: printf("Error [%d]=> Invalid instruction %s\n",e,w);break;
		case  2: printf("Error [%d]=> Keyword %s can not use as a symbol\n",e,w);break;
		case  3: printf("Error [%d]=> Redeclaration of symbol %s\n",e,w);break;
		case  4: printf("Error [%d]=> Invalid opcode %s\n",e,w);break;
		case  5: printf("Error [%d]=> Invalid Register %s\n",e,w);break;
		case  6: printf("Error [%d]=> %s is compulsory",e,w);break;
		case  7: printf("Error [%d]=> Invalid Relational operator %s",e,w);break;
		case  8: printf("Error [%d]=> Symbol %s is used but not define",e,w);break;
	}
}
int searchoptab(char w[])     
{
	int i;	for(i=0;i<15;i++)   
			{
				if(strcasecmp(w,optab[i])==0)	
				    return i;   
			}
			return -1;          
}
int searchregtab(char w[])      
{
	int i;	for(i=0;i<4;i++)     
			{
				if(strcasecmp(w,regtab[i])==0)	
				    return i+1; 
			}
			return -1;  
}
int searchreloptab(char w[])    
{
	int i;  for(i=0;i<6;i++)     
				if(strcasecmp(w,reloptab[i])==0)	
				    return i+1; 
			return -1;  
}
int issymbol(char w[])  
{
	if(searchoptab(w)==-1 && searchregtab(w)==-1 && searchreloptab(w)==-1)
		return 1;   
	else 
	{   
	    error(2,w);   
	    return 0;   
	}
}
int searchsymtab(char w[])
{
	int i;	
	for(i=0;i<symcnt;i++)       
	    if(strcasecmp(w,symtab[i].symbol)==0)
		    return i;       

	/* if symbol not found */
	
	i=symcnt++; 
	strcpy(symtab[i].symbol,w); 
	return i;       
}
void setIC(int op,int r,int index1)
{
	IC[LC][OP]=op;  
	IC[LC][REG]=r;  
	IC[LC][INDEX]=index1; 
	printf("%d\t%d\t%d\n",op,r,index1); 
}
void updatesymbol(char w[30])  
{
	int index;
	index=searchsymtab(w);  
	symtab[index].used=1;	
	setIC(op,r,index);      
}
void definesymbol(char w[])  
{
	int index;
	index=searchsymtab(w); 
	if(symtab[index].define==0) 
	{
		symtab[index].define=1; 
		symtab[index].address=LC;
	}
	else 
	    error(3,w);     
	if(op==11)      
	{
		int i; 	symtab[index].length=atoi(w3);  
		for(i=0 ; i<symtab[index].length ; i++,LC++)  
		    setIC(0,0,-1);      
		LC--;    
	}
	else if(op==12) 
	{
		symtab[index].value=atoi(w3);   
		symtab[index].length=1;     
		setIC(0,0,symtab[index].value); 
	}
}

void actionplan1(char w1[])
{
	op=searchoptab(w1);
	if(op==0)	setIC(op,op,-1);
	else if(op==14)
	{
	    LC--;
		endflag=1;
		return;
	}
	else if(op==13)	LC=0;
	else error(1,instruction);
}

void actionplan2(char w1[],char w2[])
{
	int l;
	r=0;       
	op=searchoptab(w1); 
	if(op==9 || op==10)     
	{
		if(issymbol(w2))    
		    updatesymbol(w2);  
	}
	else if(op==13)         
	{
		START=LC=atoi(w2);	
		LC--;               
	}else if(op==14)        
	{
		int index;
		index=searchsymtab(w2); 
        if(symtab[index].define==1) 
		{
			int i;
			PC=symtab[index].address;   
			symtab[index].used=1;       
			LC--;	        
			endflag=1;      
			return;         
		}
		else 
		error(8,w2);  
	}
	else if(op==-1)     
	{
		if(issymbol(w1))    
		{
			if(searchoptab(w2)==0)  
			{	
			    definesymbol(w1);   
			    actionplan1(w2);    
			}
			else 	error(4,w2);    
		}
	}
	else error(1,instruction);  
}

void actionplan3(char w1[],char w2[],char w3[])
{
	op=searchoptab(w1); 
	if((op>0 && op<7) || op==8)     
	{
		r=searchregtab(w2);         
		if(r>0 && r<5)      
		{
			if(issymbol(w3))   	
			    updatesymbol(w3);
		}
		else 	
		    error(5,w2);    
	}
	else if(op==7)     
	{
		r=searchreloptab(w2);   
		if(r>0 && r<7)  
		{
		   if(issymbol(w3))	   
		    updatesymbol(w3);   
		}
		else 	
		    error(7,w2);    
	}
	else if(op==-1)     
	{
		if(issymbol(w1))    
		{
			op=searchoptab(w2); 
			if(op==9 || op==10) 
			{	
			    definesymbol(w1);   
			    actionplan2(w2,w3); 
			}
			else if(op==11 || op==12)   
			        definesymbol(w1);   
			else 
			    error(4,w2);     
		}
	}else error(1,instruction); 
}

void actionplan4(char w1[],char w2[],char w3[],char w4[])
{
	if(issymbol(w1))        
	{
		op=searchoptab(w2); 
		if(op>0 && op<9)    
		{
			definesymbol(w1);   
			actionplan3(w2,w3,w4);
		}
		else 
		    error(4,w2); 
	}
}
void generateTC()    	
{
	int i,index;
	fp=fopen(tfname,"w+");  
	printf("\nTarget code :\n");
	for(i=START ; i<LC ;i++)  
	{
		index=IC[i][INDEX]; 
		if(index==-1)   
		    TC[i]=0;    
		else    
		{               
		    int add;
		    if(IC[i][OP]==0 && IC[i][REG]==0)   
		        TC[i]=index;        
		    else
		    {
		        add=symtab[index].address;  
		        TC[i]=(((IC[i][OP]*10)+IC[i][REG])*1000)+add;   
		    }
		}
		printf("%d %ld\n",i,TC[i]);         
		fprintf(fp,"%d %ld\n",i,TC[i]);
		
	}
	fclose(fp);	    
	printf("Target code generated in file %s\n",tfname);  
    printf("-------------------------------\n");
}
int main(int argc,char *argv[])  
{
	int i;
	if(argc>2)     
	{	
	    strcpy(sfname,argv[1]);     
	    strcpy(tfname,argv[2]);     
	}
	else    
	{
		printf("Enter a source file name: ");	scanf("%s",sfname); 
		printf("Enter a target file name: ");	scanf("%s",tfname); 
	}
	fp=fopen(sfname,"r");   
	if(fp==NULL)    
	{
		printf("File not found..!\n");  
		return 0;   
	}
	else        
	{
		printf("\nIntermediate Code\nop\treg\tindex\n");
		while(!feof(fp) && endflag==0)  
		{
			fgets(instruction,30,fp);   
			tcnt = sscanf(instruction,"%s %s %s %s",w1,w2,w3,w4); 
			switch(tcnt)
			{
					case 1 : actionplan1(w1);break; 
					case 2 : actionplan2(w1,w2);break;  
					case 3 : actionplan3(w1,w2,w3);break; 
					case 4 : actionplan4(w1,w2,w3,w4);break; 
					default : error(1,instruction);
			}
			LC++;       
		}
		fclose(fp);    
		if(endflag==0)  
			printf("Error [%d]=> End is compulsory",++e);
		
		printf("\n------------------------------------------");
		printf("\nSymbol Table\nSymbol\taddress\tdefine\tused\tlength\tvalue\n");
		for(i=0;i<symcnt;i++)       
			printf("%s\t%d\t%d\t%d\t%d\t%d\n",symtab[i].symbol,symtab[i].address,symtab[i].define,symtab[i].used,symtab[i].length,symtab[i].value);
		printf("\n---------------------------------------------\n");
		if(e==0)      
		    generateTC(); 
		else    
		    printf("Target code cant be generate.\n\n\n\n");    
	}
	return 0;   
}
