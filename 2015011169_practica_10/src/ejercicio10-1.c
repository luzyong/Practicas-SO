#include<sys/types.h>
#include<sys/socket.h>
#include<linux/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#define PUERTO 50000
#define TAMBUF 32
int num;
int main(void)
{	
	int s, c, n,i,j,estado;
	pid_t pid;
 	struct sockaddr_in sa;
  	char buf[TAMBUF];
  	time_t t;
	
	if((s=socket(PF_INET,SOCK_STREAM,0))<0)
	{
	  perror("socket");
	  exit(1);
	}
	sa.sin_family=AF_INET;

	sa.sin_port=htons(PUERTO);
	sa.sin_addr.s_addr=htonl(INADDR_ANY);
	if(bind(s,(struct sockaddr *)&sa,sizeof(sa))<0)
	{
	  perror("bind");
          exit(1);
	}
	if(listen(s,5)<0)
	{
	  perror("listen");
	  exit(1);
	}
	do
	{
	  
	  if((c=accept(s, NULL, 0))<0)
	  {
	    perror("accept");
	    exit(1);
	  }
	  for(i=1;i<s;i++)
	  {
	   pid=fork();
	   if(pid==0)
	   {
	    j=0;
	    break; 
	   }
	   else if(pid!=0)
	   {
	     operaciones();
	     j=1;
	     wait(&estado);
	   }
	  }
	  if(j==0)
	  {
	   operaciones();
	   n=sprintf(buf,"El resultado es %d",num);
	  }
	  else if(j==1)
	  {
	   n=sprintf(buf,"El resultado es %d",num);
	  }
	  if(write(c,buf,n)<0)
	  {
	    perror("write");
	    exit(1);
	  }
	  close(c);
	}
	while(1);
}

operaciones()
{
 int aleatorio,suma, resta,i;
 aleatorio=rand()%101;
 num=rand()%101;
 suma=num+aleatorio;
 resta=aleatorio-num;
 suma=resta+aleatorio;
 resta=suma-num;
 suma=suma+aleatorio;
 resta=resta-aleatorio;
 num=suma+resta;
 for(i=0;i<1000000000;i++)
 {
	
 }
 return num;
}
