#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
int main()
{
	pid_t pid;
	int i=0, estado;
	
	pid = fork();
	if(pid == -1)
	{
		perror("Error en el fork");
	}
	else if(pid == 0)
	{
		printf("Soy el hijo: PID %d PPID=%d i=%d fork=%d\n", getpid(), getppid(), ++i, pid);
		exit(0);
	}
	else
	{
		printf("Soy el padre: PID %d PPID=%d i=%d\n", getpid(), getppid(), --i);
		wait(&estado);
	}
	
}
