#include<stdio.h>
int q, inp, start, final, cur;
char E[10];
int F[10], D[20][20];

main ()
{
  int n, i, j;
  int choice;
  printf ("Enter the number of states: ");
  scanf ("%d", &q);
  printf ("The states are: ");
  for (i = 0; i < q; i++)
    printf ("q%d \t", i);

  printf ("\nEnter the number of input symbols: ");
  scanf ("%d", &inp);
  for (i = 0; i < inp; i++)
    {
      printf ("Give input symbol %d:\n", i + 1);

      scanf (" %c", &E[i]);
    }

  printf ("Enter the Starting position: ");
  scanf ("%d", &start);
  cur = start;

  printf ("How many final positions are there: ");
  scanf ("%d", &final);
  for (i = 0; i < final; i++)
    {
      printf ("final state %d :\t", i + 1);
      scanf ("%d", &F[i]);
    }

  printf ("Delta: \n");
  for (i = 0; i < q; i++)
    {
      for (j = 0; j < inp; j++)
	{
	  printf ("q%d goes on   %c :\t", i, E[j]);
	  scanf ("%d", &D[i][j]);
	}
    }


  while (1)
    {
      printf ("\nEnter the choice: \n");
      printf ("1.display \n 2.check the string \nEnter the choice : \n");
      scanf ("%d", &n);
      switch (n)
	{
	case 1:
	  display ();
	  break;
	case 2:
	  check (cur);
	  printf ("Do you want to check one more string 1.y   2.n: ");
	  scanf ("%d", &choice);
	  if (choice == 1)
	    check (cur);
	  else
	    return;
	  break;
	default:
	  printf ("Invalid input given.");
	  break;
	}
    }
}

display ()
{
  int i, j;
  printf ("The states are: ");
  for (i = 0; i < q; i++)
    printf ("q%d \t", i);
  printf ("\n");

  printf ("The input symbols are: ");
  for (i = 0; i < inp; i++)
    printf (" %c\t", E[i]);
  printf ("\n");
  printf ("Starting position is : q%d", start);
  printf ("\n");
  printf ("Final positions are:  ");
  printf ("\n");
  for (i = 0; i < final; i++)
    printf ("q%d\t", F[i]);
  printf ("\n");

  printf ("The delta is as follows: \n\n");
  printf ("\t");
  for (i = 0; i < inp; i++)
    printf (" %c\t", E[i]);
  printf ("\n");
  for (i = 0; i < q; i++)
    {
      printf ("q%d\t", i);	//q(i)
      for (j = 0; j < inp; j++)
	{
	  printf ("q%d", D[i][j]);
	  printf ("\t");
	}
      printf ("\n");
    }

}

check (int cur)
{
  int i, j;
  char string[30];

  printf ("Enter the string: ");
  scanf ("%s", &string);

  for (i = 0; string[i] != '\0'; i++)
    {
      for (j = 0; j < inp; j++)
	{
	  if (string[i] == E[j])
	    break;
	}

      if (j >= inp)
	{
	  printf ("Invalid input symbol %c", string[i]);
	  return;
	}
      cur = D[cur][j];
    }
  for (i = 0; i < final; i++)
    if (cur == F[i])
      break;
  if (i >= final)
    printf ("Fail.\n");
  else
    printf ("Success.\n");
}




/*

[root@localhost sneha]# cc dfa.c
[root@localhost sneha]# ./a.out
Enter the number of states: 4
The states are: q0      q1      q2      q3 
Enter the number of input symbols: 2
Give input symbol 1:
0
Give input symbol 2:

1
Enter the Starting position: 0
How many final positions are there: 2
final state 1 : 1
final state 2 : 2
Delta: 
q0 goes on   0 :        1
q0 goes on   1 :        2
q1 goes on   0 :        1
q1 goes on   1 :        3
q2 goes on   0 :        3
q2 goes on   1 :        2
q3 goes on   0 :        3
q3 goes on   1 :        3

Enter the choice: 
1.display 
 2.check the string 
Enter the choice : 
2
Enter the string: 0000
Success.
*/
