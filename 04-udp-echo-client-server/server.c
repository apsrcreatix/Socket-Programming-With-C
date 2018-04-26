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
#define PORT 5035

int main(){

  int socketDescriptor = socket(AF_INET, SOCK_DGRAM, 0);
  int number;
  socklen_t addressLength;
  char message[MAXLINE];

  struct sockaddr_in  serverAddress,clientAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr=INADDR_ANY;
  serverAddress.sin_port=htons(PORT);

  bind(socketDescriptor,(struct sockaddr*)&serverAddress,sizeof(serverAddress));

  printf("\nServer Started ...\n");

  while(1){
    printf("\n");
    addressLength = sizeof(clientAddress);

    number = recvfrom(socketDescriptor,message,MAXLINE,0,(struct sockaddr*)&clientAddress,&addressLength);

    printf("\n Client's Message: %s ",message);

    if(number<6)
      perror("send error");

      sendto(socketDescriptor,message,number,0,(struct sockaddr*)&clientAddress,addressLength);
  }
  return 0;
}
