/**
 * Title : echo client
 * Name : Aditya Pratap Singh Rajput
 * Subject : Network Protocols And Programming
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAXLINE 1024

int main(){
  int socket_descriptor;
  int n;
  socklen_t length;
  char sendline[MAXLINE],recvline[MAXLINE];
  struct sockaddr_in servaddr;
  printf("\nEnter message :");
  scanf("%s",sendline);
  socket_descriptor = socket(AF_INET,SOCK_DGRAM,0);

  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = INADDR_ANY;
  servaddr.sin_port = htons(5035);

int isConnect = connect(socket_descriptor,(struct sockaddr*)&servaddr,sizeof(servaddr));

if(isConnect==-1){
  printf("\nNot connected");
}

  length = sizeof(servaddr);
  sendto(socket_descriptor,sendline,MAXLINE,0,(struct sockaddr*)&servaddr,length);
  n=recvfrom(socket_descriptor,recvline,MAXLINE,0,NULL,NULL);
  recvline[n]=0;
  printf("\nServer's Echo : %s\n",recvline);

  return 0;
}
