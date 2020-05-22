#include<stdio.h>
#include<stdlib.h>
#include<string.h>
FILE *fp;

struct mnttab
        {
        char macroname[20];
        int ppcnt;
        int kpcnt;
        int kptptr;
        int mdtptr;
        }mnttab[10];

struct mdttab
{
char name[20];
}mdttab[10];

struct kpttab
{
char name[20];
char value[10];
}kpttab[10];

struct pnttab
{
char name[10];
}pnttab[10];

int lno;

int mntptr=0;
int kptptr=-1;
int pntptr=0;
int mdtptr=0;
int ppcnt=0;
void addkpt(char *str1,char *str2)
{
strcpy(kpttab[kptptr].name,str1);
strcpy(kpttab[kptptr].value,str2);
kptptr++;
}
void addpnt(char *str)
{
strcpy(pnttab[pntptr].name,str);
pntptr++;
}
void addmnt(char *mname,int ppcnt,int kpcnt,int kptptr,int mdtptr)
{
strcpy(mnttab[mntptr].macroname,mname);
mnttab[mntptr].ppcnt=ppcnt;
mnttab[mntptr].kpcnt=kpcnt;
mnttab[mntptr].kptptr=kptptr;
mnttab[mntptr].mdtptr=mdtptr;
mntptr++;
}
char *strcut(char *str,char *str1)
{
int i=0;
while(*str!=' ' && *str!='=' && *str!='\n' && *str!=',')
        {
        str1[i++]=*str;
        str++;
        }
str1[i]='\0';
return str;
}
void separate(char *s)
{
char mname[30],str1[30],str2[30];
int i=0,kpcnt=0,ppcnt=0;
s=strcut(s,mname);
                 
    while(s[i]!='\n')
        {
        switch(s[i])
                {
                case '&':
                        s=strcut(++s,str1);
                        ppcnt++;
                        addpnt(str1);
                        break;

                case ' ':

                case ',': s++;
                          break;

                case '=':
                        s=strcut(++s,str2);
                        kpcnt++;
                        kptptr++;
                        addkpt(str1,str2);
                        break;
                }
        }
addmnt(mname,ppcnt-kpcnt,kpcnt,kptptr-kpcnt+1,mdtptr);
}
int checkpnttab(char s[])
{
int i;
for(i=0;i<pntptr;i++)
        {
        if(!strcmp(pnttab[i].name,s))
        return i+1;
        }
return -1;
}

int checkmnttab(char s[])
{
int i;
for(i=0;i<mntptr;i++)
        {
        if(!strcmp(mnttab[i].macroname,s))
        return i+1;
        }
return -1;
}

int checkkpttab(char s[])
{
int i;
for(i=0;i<kptptr;i++)
        {
        if(!strcmp(kpttab[i].name,s))
        return i+1;
        }
return -1;
}
void displaypnttab()
{
int i;
printf("\n\n********************************************************");
printf("\n\n\tPNTTAB");
printf("\n----------------------------");
for(i=0;i<pntptr;i++)
        {
        printf("\n%s",pnttab[i].name);
        }
}
void displaykpt()
{
int i;
printf("\n\n********************************************************");
printf("\n\n\tKPTTAB");
printf("\n----------------------------\n");
printf("NAME\t\tVALUE");
printf("\n---------------------------\n");
for(i=0;i<=kptptr;i++)
        {
        printf("%s\t\t%s\n",kpttab[i].name,kpttab[i].value);
        }
}

void displaymnt()
{
int i;
printf("\n\n********************************************************");
printf("\n\n\tMNT");
printf("\n---------------------------------\n");
printf("MACRONAME\tPPCNT\tKPCNT\tKPPTR\tMDTPTR");
printf("\n-------------------------------------\n");
for(i=0;i<mntptr;i++)
        {
printf("%s\t\t%d\t%d\t%d\t%d\n",mnttab[i].macroname,mnttab[i].ppcnt,mnttab[i].kpcnt,mnttab[i].kptptr,mnttab[i].mdtptr);
        }
}

int main()
{
    char FName[20];
    char *str=(char *)malloc(80*sizeof(char));
    printf("\nEnter Source File Name: ");
    scanf("%s",FName);
    fp=fopen(FName,"r");
    while(!feof(fp))
                {
                fgets(str,80,fp);
                      if(!strcmp(str,"MACRO\n"))
                        {
                        pntptr=0;
                        fgets(str,80,fp);
                        separate(str);
                       }
                }
	fclose(fp);
	displaymnt();
	displaypnttab();
	displaykpt();
}

