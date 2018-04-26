/**
 * Title : Day-Time client
 * Name : Aditya Pratap Singh Rajput
 * Subject : Network Protocols And Programming using C
 * 
 * */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "string.h"

#define PORT 9002 //the port users will be connecting to
#define MAXLINE 500 //for buffer size

int main(){

  //variable for socket descriptor
  int socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in servaddr;
  

  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = INADDR_ANY;
  servaddr.sin_port = htons(PORT);

//if not connected then print the error message
  if (connect(socket_descriptor, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
  {
   perror("\nNot connected");
   exit(0);
  }

  char server_response[MAXLINE];


  
  //if not received the data it will show the error message
if(recv(socket_descriptor,server_response,MAXLINE-1,0)==-1){
  perror("recv");
  exit(0);
}

  printf("\nTIME FROM SERVER %s\n",server_response);

  return 0;
}
