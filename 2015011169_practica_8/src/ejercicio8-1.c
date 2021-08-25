#include<stdio.h>
#include<pthread.h>
int variable;
void aumento(void)
{	
	for(;;)
          variable+=1;
	pthread_exit(0);
}
void decremento(void)
{
	for(;;)
	  variable-=1;
	pthread_exit(0);
}
void main()
{
	int i, n;
	printf("Ingresa el tiempo del proceso:\n");
	scanf("%d",&n);
	pthread_attr_t atributos;
	pthread_t thid[2];
	pthread_attr_init(&atributos);
	pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_DETACHED);
	pthread_create(&thid[0], &atributos, (void *)aumento, NULL);
	pthread_create(&thid[1], &atributos, (void *)decremento, NULL); 
	
	sleep(n);
	printf("El valor de la variable es:%d\n",variable);
}
