#include<stdlib.h>
#include<stdio.h>

extern char **environ;
int main()
{
	printf("El valor de la variable HOME es: %s\n", getenv("HOME"));
	return(0);
}
