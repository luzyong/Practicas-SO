#include<stdio.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/sem.h>
#define SEMAFORO_PADRE 1
#define SEMAFORO_HIJO 0
int main(int argc, char *argv[])
{
	int j = 10, pid, semid;
	struct sembuf operacion;
	key_t llave;
	printf("sem_num:%i sem_op:%i sem_flg:%i\n",operacion.sem_num, operacion.sem_op, operacion.sem_flg);
	llave = ftok(argv[0], 'U');
	if((semid = semget(llave, 0, IPC_CREAT | 0600))==-1)
	{
	  perror("Error al ejecutar segmet");
	  exit(-1);
	}
	semctl(semid, SEMAFORO_HIJO, SETVAL, 0);
	semctl(semid, SEMAFORO_PADRE, SETVAL, 1);

	if((pid = fork())==-1)
	{
	  perror("Error al ejecutar fork");
	  exit(-1);
	}	
	else if(pid ==0)
	{
	  while(j)
	  {
	     operacion.sem_flg=0;
	     operacion.sem_op=-1;
	     operacion.sem_num=SEMAFORO_HIJO;
	     semop(semid, &operacion, 1);

	     printf("SOY EL PROCESO HIJO. IMPRESION:%d\n", j--);

	     operacion.sem_op=1;
	     operacion.sem_num=SEMAFORO_PADRE;
	     semop(semid, &operacion, 1);
	    
	  }
	     semctl(semid, 0, IPC_RMID, 0);
	}
	else
	{
	  while(j)
	  {
	     operacion.sem_flg=0;
	     operacion.sem_op=-1;
	     operacion.sem_num=SEMAFORO_PADRE;

	     semop(semid, &operacion, 1);
	     printf("SOY EL PROCESO PADRE. IMPRESION: %d\n", j--);

	     operacion.sem_op=1;
	     operacion.sem_num=SEMAFORO_HIJO;
	     semop(semid, &operacion, 1);
	
	  }
	     semctl(semid, 0, IPC_RMID, 0);
	}
}
