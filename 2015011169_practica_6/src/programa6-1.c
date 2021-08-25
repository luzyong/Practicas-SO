#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
int main(void)
{
	int i = 10, pid;
	if((pid = fork())==-1)
	{
	  perror("fork");
	  exit(-1);
	}	
	else if(pid ==0)
	{
	  while(i)
	  {
	     printf("PROCESO HIJO: %d\n", i--);
	  }
	}
	else
	{
	  while(i)
	  {
	    printf("PROCESO PADRE: %d\n", i--);
	  }
	}
}
