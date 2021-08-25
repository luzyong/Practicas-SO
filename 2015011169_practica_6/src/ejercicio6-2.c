#include<stdio.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/sem.h>
#define SEMAFORO_PP 0
#define SEMAFORO_PH1 1
#define SEMAFORO_PH2 2
int main(int argc, char *argv[])
{
	int j = 10, pid, semid;
	struct sembuf operacion;
	key_t llave;
	
	llave = ftok(argv[0], 'U');
	if((semid = semget(llave, 3, IPC_CREAT | 0600))==-1)
	{
	  perror("Error al ejecutar segmet");
	  exit(-1);
	}
	semctl(semid, SEMAFORO_PH1, SETVAL, 1);
	semctl(semid, SEMAFORO_PH2, SETVAL, 2);
	semctl(semid, SEMAFORO_PP, SETVAL, 0);

	if((pid = fork())==-1)
	{
	  perror("Error al ejecutar fork");
	  exit(-1);
	}	
	else if(pid ==0)
	{
	  if((pid=fork())==-1)
	  {
		perror("Error al ejecutar fork 2");
		exit(-1);
	  }
	  else if(pid ==0)
	  {
		while(j)
		{
		  operacion.sem_flg=0;
		  operacion.sem_op=-1;
		  operacion.sem_num=SEMAFORO_PH2;
		  semop(semid, &operacion, 1);
		  printf("SOY EL PROCESO HIJO 2. IMPRESION:%d\n",j--);
		  operacion.sem_op=1;
		  operacion.sem_num=SEMAFORO_PH1;
		  semop(semid, &operacion,1);
	  	}
		semctl(semid,0,IPC_RMID,0);
	   }
	else
	{
	  while(j)
	  {
	     printf("hijo 1 sem_num:%i sem_op:%i\n", operacion.sem_num, operacion.sem_op);
	     operacion.sem_flg=0;
	     operacion.sem_op=-1;
	     operacion.sem_num=SEMAFORO_PH1;
	     semop(semid, &operacion, 1);

	     printf("SOY EL PROCESO HIJO. IMPRESION:%d\n", j--);

	     operacion.sem_op=1;
	     operacion.sem_num=SEMAFORO_PP;
	     semop(semid, &operacion, 1);
	    
	  }
	    semctl(semid, 0, IPC_RMID, 0);
	 }
	}
	else
	{
	  while(j)
	  {
	     printf("padre sem_num:%i sem_op:%i\n",operacion.sem_num,operacion.sem_op);
	     operacion.sem_flg=0;
	     operacion.sem_op=-1;
	     operacion.sem_num=SEMAFORO_PP;

	     semop(semid, &operacion, 1);
	     printf("SOY EL PROCESO PADRE. pid=%d IMPRESION: %d\n",getpid(), j--);

	    operacion.sem_op=1;
	     operacion.sem_num=SEMAFORO_PH2;
	     semop(semid, &operacion, 1);
	
	  }
	     semctl(semid, 0, IPC_RMID, 0);
	}
}
