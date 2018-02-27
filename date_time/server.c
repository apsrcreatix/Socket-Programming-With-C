//program for date time server
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<time.h>
// time


#define MAXLINE 1024

int main(){

  //for showing the time from the server to the client
  time_t time_from_pc;
  struct tm * timeinfo;
  time(&time_from_pc);
  timeinfo = localtime (&time_from_pc);
  //same as echo server
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

    printf("\n %s has requested for time at %s",msg,asctime(timeinfo));

    if(n<6)
      perror("send error");

      sendto(socket_descriptor,asctime(timeinfo),n,0,(struct sockaddr*)&cliaddr,length);
  }
  return 0;
}
