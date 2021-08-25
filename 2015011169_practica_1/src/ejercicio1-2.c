#include<stdio.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
	int tokens, n=1, i, N=1;
	for(tokens = 0; tokens < argc; tokens++){
	  if(argv[tokens][0] == '-')
		printf("opcion: %s\n", argv[tokens]+1);
	  else
	        printf("argumento %d: %s\n", tokens, argv[tokens]);
		for(i = 0; i < N; i++){
			N++;
			if(argv[tokens][i]==0)
				i=N;
		        else
		           n++;
		}
		printf("#acumulado de caracteres del arg.%d: %d\n", tokens, n-1);
	}
	exit(0);
}
