#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
int main(void)
{
	char x;
	int shmid;
	printf("\nIntroduzca m para modificar el valor de la variable, v para visualiarla y t para terminar:\n");
	switch(leer_car()){
	  case 't':
		shmctl(shmid,IPC_RMID,0);
		exit(0);
	  case 'm':
		printf("Ingrese el valor de x(letra):\n");
		scanf("%c",&x);
		insertar(x); 
		break;
	  case 'v':
		imprimir();
		break;
	  default:
		printf("Opción inváida");
		break;
	}
}
struct nodo{
	char info;
	struct nodo *sig;
};
struct nodo *raiz=NULL;
int crear(int argc, char *argv[])
{
	int shmid,  *variable;
	key_t llave;
	llave = ftok(argv[0], 'K');
	if((shmid = shmget(llave, sizeof(int), IPC_CREAT | 0600))== -1)
	{
		perror("Error en shmget");
		exit(-1);
	}
	if((variable = (int *)shmat(shmid, NULL, 0))==(int *)(-1))
	{
		perror("Fallo shmat");
		exit(-1);
	}
      return variable;
}
void insertar(char x)
{
	int crear=0;
	if(crear==0);
	{
	 crear();
         crear =1;
         while(1)
	{
	   variable->info=x;
	   if(raiz==NULL)
	   {
		raiz = variable;
		variable->sig=NULL;
	   }
	   else
	   {
		variable->sig=raiz;
		raiz=variable;
	   }
	}
	else{
	while(1)
	{
		variable->info=x;
		if(raiz==NULL)
		{
		    raiz = variable;
		    variable->sig=NULL;
		}
		else
		{
		    variable->sig=raiz;
		    raiz = variable;
		}
	}
   }
}
			
	int leer_car()
	{
	  char letra;
	  char almacen[80];
		
	  scanf("%s", &almacen);
	  sscanf(almacen, "%c", &letra);
	  return letra;
	}
 
void imprimir()
{
	struct nodo *reco=raiz;
	printf("Pila:\n");
	while(reco!=NULL)
	{
	  printf("%c", reco->info);
	  reco=reco->sig;
	}
}

int extraer()
{
	if(raiz !=NULL)
	{
	  int informacion = raiz->info;
	  struct nodo *bor = raiz;
	  raiz = raiz->sig;
	  bor=NULL;
	  return informacion;
	}
	else
	{
	 return -1;
	}
}
