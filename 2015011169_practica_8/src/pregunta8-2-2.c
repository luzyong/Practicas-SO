#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>

void aumento()
{
	variable+=3;
	pthread_exit(0);
}
void decremento()
{
	variable-=2;
	pthread_exit(0);
}
int main(void)
{
	int variable;
	pthread_t th1, th2;
	pthread_create(&th1, NULL, aumento(variable), NULL);
	pthread_create(&th2, NULL, decremento(variable), NULL);
	printf("El hilo principal espera a sus hijos\n");

	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	printf("El hilo principal termina\n");
	printf("El valor de la variable es: %d\n",variable);
	exit(0);
}
