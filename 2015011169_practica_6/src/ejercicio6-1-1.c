#include<stdio.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/sem.h>
#include"programa1.h"
#include"programa2.h"
#define SEMAFORO_PADRE 0
#define SEMAFORO_HIJO 1
int main(int argc, char *argv[])
{
	int j = 2, pid, semid;
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
	     operacion.sem_flg=0;
	     operacion.sem_op=-1;
	     operacion.sem_num=SEMAFORO_HIJO;
	     semop(semid, &operacion, 1);
	     if(j==2)
	     {
	       printf("%d ",j--);
	       situ();
	
	     }
	     else
	    {
	       printf("%d ",j--);
	       sino();
	    }
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
	     if(j==2)
             {
               printf("%d ", j--);
	       dame();
	     }
	     else
	     {
               printf("%d ",j--);
	       nome();
	     }

	     operacion.sem_op=1;
	     operacion.sem_num=SEMAFORO_HIJO;
	     semop(semid, &operacion, 1);
	
	  }
	     semctl(semid, 0, IPC_RMID, 0);
	}
}
