/* 
   SetA Q1.	Write a program that behaves like a shell (command interpreter).
		It has its own prompt say "Myshell$". Any normal shell command is
		executed from your shell by starting a child process to execute the
		system program corresponding to the command. 
   
*/   

#include<stdio.h>
#include<unistd.h>        // for fork(),exclp()
#include<fcntl.h>        // O_RDONLY
#include<stdlib.h>      //exit()
void count(char c, char *fn)
{
	int lc=0,wc=0,cc=0,handle;
	char ch;
	if((handle=open(fn,O_RDONLY))==-1)
	{
		printf("File %s not found\n",fn);
		return;
	}
	while(read(handle,&ch,1)!=0)
	{
		if(ch==' '|| ch=='\n')
		wc++;
                else 
		cc++;

		if(ch=='\n')
		lc++;
	}
	close(handle);
	switch(c)
	{
		case 'c':
			printf("Total No.of Characters = %d\n",cc);
			break;
		case 'w':
			printf("Total No.of Words = %d\n",wc);
			break;
		case 'l':
			printf("Total No.of Lines = %d\n",lc);
			break;
	}
}

main()
{
	char command[80],t1[20],t2[20],t3[20],t4[20];
	int n;
	system("clear");
	while(1)
	{
		printf("myShell$");
		fflush(stdin);
		fgets(command,80,stdin);
		n = sscanf(command,"%s %s %s %s",t1,t2,t3,t4);
		switch(n)
		{
			case 1:
                         	if(strcmp(t1,"exit")==0)
                                 exit(1);      
				if(!fork())
				{
					execlp(t1,t1,NULL);
					perror(t1);
				}
				break;
			case 2:
				if(!fork())
				{
					execlp(t1,t1,t2,NULL);
					perror(t1);
				}
				break;
			case 3:
				if(strcmp(t1,"count")==0)
				count(t2[0],t3);
				else
				{
					if(!fork())
					{
						execlp(t1,t1,t2,t3,NULL);
						perror(t1);
					}
				}
				break;
			case 4:
				if(!fork())
				{
					execlp(t1,t1,t2,t3,t4,NULL);
					perror(t1);
				}
		}
	}
}
