#include<sys/types.h>
#include<signal.h>
#include<stdlib.h>
#include<stdio.h>
pid_t pid;

void mensaje()
{
	sleep(rand()%11+1);
	printf("Hijo: Me mandaste un SIGUSR1\n");
	return;
}
void terminar(void)
{
  kill(0,SIGKILL);
}
int main(int argc, char **argv)
{
	int pid, status, n;
	struct sigaction act;
	sigset_t mask;

	pid=fork();
	switch(pid)
	{
	 case -1:
	   exit(-1);
	 case 0:
	  printf("Hijo: Rápido, mándame un SIGUSR1 a este pid:%d\n", getpid());
	  signal(SIGUSR1, mensaje);
	  pause();
	  printf("Hijo: Terminé sin morir en el intento :)\n"); 
	  exit(0);
	   
	 default:
	printf("Padre: Nomas 5 segundos, eh\n"); 
	printf("%d",pid);
	 act.sa_handler=(void *)terminar;
	 act.sa_flags=0;
	sigemptyset(&mask);
	sigaddset(&mask,SIGQUIT);
	sigprocmask(SIG_SETMASK, &mask, NULL);
	sigaction(SIGALRM, &act, NULL);
	alarm(10);
	pause();
	 }

}
