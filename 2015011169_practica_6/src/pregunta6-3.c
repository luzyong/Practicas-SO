#include<stdio.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/sem.h>
#define SEMAFORO_PADRE 0
#define SEMAFORO_HIJO 1
int main(int argc, char *argv[])
{
	int j = 10, pid, semid;
	struct sembuf operacion;
	key_t llave;
	
	llave = ftok(argv[0], 'U');
	if((semid = semget(llave, 2, IPC_CREAT | 0600))==-1)
	{
	  perror("Error al ejecutar segmet");
	  exit(-1);
	}
	semctl(semid, SEMAFORO_HIJO, SETVAL, 1);
	semctl(semid, SEMAFORO_PADRE, SETVAL, 0);

	if((pid = fork())==-1)
	{
	  perror("Error al ejecutar fork");
	  exit(-1);
	}	
	else if(pid ==0)
	{
	  while(j)
	  {
	     printf("entrando a prohijo sem_num:%i sem_op:%i\n", operacion.sem_num, operacion.sem_op);
	     operacion.sem_flg=0;
	     operacion.sem_op=-1;
	     operacion.sem_num=SEMAFORO_HIJO;
	     semop(semid, &operacion, 1);
	     printf("despues de las operaciones preprint hijo num:%i op:%i\n",operacion.sem_num, operacion.sem_op);
	     printf("SOY EL PROCESO HIJO. IMPRESION:%d\n", j--);

	     operacion.sem_op=1;
	     operacion.sem_num=SEMAFORO_PADRE;
	     semop(semid, &operacion, 1);
	    printf("despues de las operaciones postprint hijo num:%i op:%i\n\n",operacion.sem_num,operacion.sem_op);
	  }
	     semctl(semid, 0, IPC_RMID, 0);
	}
	else
	{
	  while(j)
	  {
	     printf("entrando a propadre sem_num:%i sem_op:%i\n",operacion.sem_num,operacion.sem_op);
	     operacion.sem_flg=0;
	     operacion.sem_op=-1;
	     operacion.sem_num=SEMAFORO_PADRE;

	     semop(semid, &operacion, 1);
	     printf("despues de las primeras operaciones pre printpadre num:%i op:%i\n",operacion.sem_num, operacion.sem_op);
	     printf("SOY EL PROCESO PADRE. IMPRESION: %d\n", j--);

	     operacion.sem_op=1;
	     operacion.sem_num=SEMAFORO_HIJO;
	     semop(semid, &operacion, 1);
	     printf("despues de las segundas operaciones postprint padre num:%i op:%i\n",operacion.sem_num, operacion.sem_op);
	  }
	     semctl(semid, 0, IPC_RMID, 0);
	}
}
