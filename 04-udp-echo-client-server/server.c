/**
 * Title : echo server
 * Name : Aditya Pratap Singh Rajput
 * Subject : Network Protocols And Programming using C
 * 
 * */
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
// time

#define MAXLINE 1024

int main(){

  int socket_descriptor;
  int n;
  socklen_t length;
  char msg[MAXLINE];
  struct sockaddr_in  servaddr,cliaddr;

  socket_descriptor = socket(AF_INET,SOCK_DGRAM,0);

  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr=INADDR_ANY;
  servaddr.sin_port=htons(5035);

  bind(socket_descriptor,(struct sockaddr*)&servaddr,sizeof(servaddr));

  printf("\nServer Started ...");
while(1){
    printf("\n");
    length = sizeof(cliaddr);

    n = recvfrom(socket_descriptor,msg,MAXLINE,0,(struct sockaddr*)&cliaddr,&length);

    printf("\n Client's Message:%s ",msg);

    if(n<6)
      perror("send error");

      sendto(socket_descriptor,msg,n,0,(struct sockaddr*)&cliaddr,length);
  }
  return 0;
}
