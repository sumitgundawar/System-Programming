/* 

   SetB Q1.	Write a program that behaves like a shell (command interpreter).
		It has its own prompt say "myshell$". Any normal shell command is
		executed from your shell by starting a child process to execute the
		system program corresponding to the command. It should additionally
		interpret the following command.
		i)typeline +n  <filename>  	- print first 10 lines of file
		ii)typeline -n  <filename> 	- print last 20 lines of file
		iii)typeline   a  <filename> 	- print all lines of  file */

#include<stdio.h>
#include<unistd.h>   	 //execlp()
#include<fcntl.h>	//O_RDONLY
#include<stdlib.h>     //exit()
void typeline(char *s, char *fn)
{
	int handle,i=0,cnt=0,n;
	char ch;
	if((handle=open(fn,O_RDONLY))==-1)
	{
		printf("File %s not found\n",fn);
		return;
	}
	if(strcmp(s,"a")==0)
	{
		while(read(handle,&ch,1)!=0)
		printf("%c",ch);
		close(handle);
		return;
	}
	n=atoi(s);
	if(n>0)
	{
		while(read(handle,&ch,1)!=0)
		{
			if(ch=='\n')
			i++;
			if(i==n)
			break;
			printf("%c",ch);
		}
		printf("\n");
		close(handle);
		return;
	}
	if(n<0)
	{
		while(read(handle,&ch,1)!=0)
		{
			if(ch=='\n')
			cnt++;
		}
		lseek(handle,0,SEEK_SET);      //lseek moves the read/write pointer
 		cnt++; 
		while(read(handle,&ch,1)!=0)  //SEEK_SET go at perticular line ,The offset is set to offset bytes.
                {
			if(ch=='\n')
			i++;
			if(i==cnt+n-1)
			break;
		}
		while(read(handle,&ch,1)!=0)
		printf("%c",ch);
		printf("\n");
		close(handle);
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
				if(strcmp(t1,"typeline")==0)
				typeline(t2,t3);
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



OUTPUT


myShell$ typeline +7 typeline.c
/* 

   SetB Q1.     Write a program that behaves like a shell (command interpreter).
                It has its own prompt say "myshell$". Any normal shell command is
                executed from your shell by starting a child process to execute the
                system program corresponding to the command. It should additionally
                interpret the following command.



myShell$ typeline -3 a.txt
8   hhhhhhhhhhhhhhhhhhhhhhh
9   iiiiiiiiiiiiiiiiiiiiiii
10  jjjjjjjjjjjjjjjjjjjjjj

myShell$ typeline a a.txt
1   aaaaaaaaaaaaaaaaaaaaa
2   bbbbbbbbbbbbbbbbbbbbb
3   ccccccccccccccccccccc
4   ddddddddddddddddddddd
5   eeeeeeeeeeeeeeeeeeeee
6   fffffffffffffffffffffff
7   gggggggggggggggggggggg
8   hhhhhhhhhhhhhhhhhhhhhhh
9   iiiiiiiiiiiiiiiiiiiiiii
10  jjjjjjjjjjjjjjjjjjjjjj
