#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
void tratar_alarma(void)
{
	
	printf("Alarma activada\n");
	printf("numero de señal:%d pid:%d\n", SIGALRM, getpid());
}

int main(void)
{
	struct sigaction act;
	sigset_t mask;
	
	
	
	
	printf("antes de ir a tratar alarma\n");
	act.sa_handler = (void *)tratar_alarma;
	printf("antes de flag\n");
	act.sa_flags = 0;
	printf("despues de flag\n");
	
	sigemptyset(&mask);
	sigaddset(&mask, SIGQUIT);
	sigprocmask(SIG_SETMASK, &mask, NULL);
	sigaction(SIGALRM, &act, NULL);
	
	for(;;)
	{
	 
	  ualarm(500000,0);
	  pause();
	}

}
