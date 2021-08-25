#include<stdlib.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>

char buffer[BUFSIZ];

int main(int argc, char *argv[])
{
	int nbytes, origen, destino,j;
	if((origen = open("archivo.txt", O_RDWR)) == -1)
	{
	  perror("Error");
	  exit(-1);
	}
	if((destino = open("destino.txt",O_RDWR|O_CREAT|O_APPEND, 0777))==-1)
	{
	  perror("Error");
	  exit(-1);
	}
	lseek(origen,0,SEEK_END);//posiciona el puntero en el byte final del archivo
	while(j!=0)//Mientras j no sea 0, va a seguir leyendo
	{
	 j=lseek(origen,-1,SEEK_CUR);//J es igual a la posición del puntero, aqui siempre desde la posicion actual, va a retroceder 1
	 printf("%d",j);
	 nbytes=read(origen,&buffer,1);//Solo va a almacenar en el buffer 1 byte según la posicion
         printf("se leyeron %d bytes La palabra leida es : %s :)\n",nbytes,buffer);  
	 write(destino,&buffer,nbytes);
	 lseek(origen,j,SEEK_SET);//posiciona el puntero en la posicion j, que es la última que se configuró, así podemos ir avanzando del 59 al 0 sin que se quede en la misma posicion
	}
	
	close(origen);
	close(destino);	
}
