#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
int main()
{
	pid_t pid;
	int i=0, estado;
	
	pid = fork();
	switch(pid){
	 case -1:
		perror("Error en el fork");
		 break;
	 case 0:
		printf("Soy el hijo: PID %d PPID=%d i=%d fork=%d\n", getpid(), getppid(), ++i, pid);
		exit(0);
		 break;
	 default:
		printf("Soy el padre: PID %d PPID=%d i=%d\n", getpid(), getppid(), --i);
		exit(0);
	}
}
