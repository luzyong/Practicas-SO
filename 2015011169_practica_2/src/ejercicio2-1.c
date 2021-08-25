#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
main()
{
  printf("Identificador de usuario: %d\n", getuid());
  printf("Identificador de usuario efectivo: %d\n", geteuid());
}
