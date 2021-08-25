#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
void function(void)
{
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

	printf("El hilo principal termina\n");
	exit(0);
}
