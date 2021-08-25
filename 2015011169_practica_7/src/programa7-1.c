#include<stdio.h>
#include<signal.h>
void tratar_alarma(void )
{
	printf("Alarma activada\n");
}

int main(void)
{
	struct sigaction act;
	sigset_t mask;

	act.sa_handler = tratar_alarma;
	act.sa_flags = 0;

	sigemptyset(&mask);
	sigaddset(&mask, SIGQUIT);
	sigprocmask(SIG_SETMASK, &mask, NULL);
	sigaction(SIGALRM, &act, NULL);

	for(;;)
	{
	  alarm(3);
	  pause();
	}
}
