#include<stdio.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
	int tokens, N=1;
	for(tokens = 0; tokens < N; tokens++){
	  N++;
	  if(argv[tokens][0] == '-')
		printf("opcion: %s\n", argv[tokens]+1);
	  else
	        printf("argumento %d: %s\n", tokens, argv[tokens]);
	if(argv[tokens+1]==0)
	 tokens=N;
	}
	exit(0);
}
