#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
void nieto(void)
{
	printf("Hilo nieto %u \n", pthread_self());
	sleep(2);
	pthread_exit(0);
}
void function(void)
{
	pthread_t thn;
	pthread_create(&thn, NULL, (void *)nieto, NULL);
	printf("El hilo hijo tiene un hilo nieto\n");
	pthread_join(thn, NULL);
	printf("Hilo %u \n", pthread_self());
	sleep(2);
	pthread_exit(0);
}
int main(void)
{
	pthread_t th1, th2;
	pthread_create(&th1, NULL, (void *)function, NULL);
	pthread_create(&th2, NULL, (void *)function, NULL);
	printf("El hilo principal espera a sus hijos\n");

	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	printf("El hilo principal termina\n");
	exit(0);
}
