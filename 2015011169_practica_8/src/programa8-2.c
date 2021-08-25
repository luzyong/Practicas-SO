#include<stdio.h>
#include<pthread.h>
int MAXHILOS=10;
void function(void)
{
	printf("Hilo %u \n", pthread_self());
	sleep(3);
	pthread_exit(0);
}
void main()
{
	int i;
	pthread_attr_t atributos;
	pthread_t thid[MAXHILOS];
	pthread_attr_init(&atributos);
	pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_DETACHED);

	for(i=0;i<MAXHILOS;i++)
	{
	 pthread_create(&thid[i], &atributos, (void *)function, NULL);
	 sleep(6);
	}
}
