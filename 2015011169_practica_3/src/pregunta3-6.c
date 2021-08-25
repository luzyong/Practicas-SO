#include<sys/types.h>
#include<stdio.h>
main()
{
	pid_t pid;
	int j,n=0;
	
	for(j=0;j<3;j++)
	{
	  pid = fork();
	  n++;
	  if(n!=1 && pid!=0)
	    break;
	}
	printf("El padre del proceso %d es %d, j=%d n=%d\n", getpid(), getppid(), j,n);
	sleep(3);

	 
}
