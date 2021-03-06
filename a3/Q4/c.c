#include<stdio.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<stdlib.h>
#define MAX 80
#define PORT 52288
#define SA struct sockaddr

void func(int sockfd)
{
    char buff[MAX];
    int ascii;
    int n;
    for(;;)
    {
        bzero(buff,sizeof(buff));
        printf("Type string to send : ");
        n=0;
        while((buff[n++]=getchar())!='\n');
        write(sockfd,buff,sizeof(buff));
        bzero(buff,sizeof(buff));
        read(sockfd,buff,sizeof(buff));
        printf("Sum Received : %s\n",buff);
        if((strncmp(buff,"exit",4))==0)
        {
        printf("Client Exit...\n");
        break;
    }
    }
}

main( argc, argv)
int argc;
char **argv;
{
int sockfd,connfd;
struct sockaddr_in servaddr,cli;
sockfd=socket(AF_INET,SOCK_STREAM,0);
	
if(sockfd==-1)
{
printf("socket creation failed...\n");
exit(0);
}
else
printf("Socket successfully created..\n");
bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=inet_addr(argv[1]);
    servaddr.sin_port=htons(atoi(argv[2]));

if(connect(sockfd,(SA *)&servaddr,sizeof(servaddr))!=0)
{
printf("connection with the server failed...\n");
exit(0);
}
else
printf("connected to the server..\n");
func(sockfd);
close(sockfd);
}