#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int leer_car()
{
    char letra;
    char almacen[80];

    scanf("%s", &almacen);
    sscanf(almacen, "%c", &letra);
    return letra;
}

int main(int argc, char const *argv[])
{
    int shmid, cont= 0;
    char *Nodo, *sig;
    key_t llave;

    llave = ftok(argv[0], 'K');

    if ((shmid = shmget(llave, sizeof(char) * 11, IPC_CREAT | 0600)) == -1)
    {
        perror("Error en shmget");
        exit(-1);
    }

    if ((sig = Nodo = (char *)shmat(shmid, NULL, 0)) == (char *)(-1))
    {
        perror("Error en shmat");
        exit(-1);
    }

    pid_t pid = fork();

    if (pid == -1)
    {
        printf("Error en el primer proceso");
        exit(-1);
    }
    else if (pid == 0)
      {	
      	printf("Proceso hijo\n");
        sleep(3);
	int i;
        for (i = 0; i < 10; i++)
        {
            Nodo=Nodo+1;
            *Nodo=i + 97;
            *sig=i + 1;
            sleep(1);
        }
        exit(0);
    }
    else
    {
        pid = fork();
        if(pid == -1)
        {
            printf("Error en el segundo proceso");
            exit(-1);
        }
        else if(pid == 0)
        {
        	printf("Segundo proceso hijo\n");
            sleep(25);
	    int i;
            for (i= 0; i < 10; i++)
            {
                Nodo--;
                *sig = 10 - i - 1;
                sleep(1);
            }
            exit(0);
        }
        else
        {
            while (1)
            {
                sleep(1);
                if(cont<*sig)
                {
                printf("Insertando\n");
                printf("CARACTER APILADO: %c \n",*(Nodo+cont+1));
                }
                else if (cont > *sig)
                {
                printf("Eliminando-\n");
                printf("CARACTER ELIMINADO DE LA PILA: %c\n", *(Nodo + cont));

                }
                cont=*sig;
                
                
            }
            exit(0);
        }
    }
}
