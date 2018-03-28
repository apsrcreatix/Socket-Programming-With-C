/**
 * Title : Day-Time server
 * Name : Aditya Pratap Singh Rajput
 * Subject : Network Protocols And Programming
*/

//program for date time server
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<time.h>
//port value and the max size for buffer
#define PORT 9002 //the port users will be connecting to
#define BACKLOG 10 //how many pending connections queue will hold
int main(){
  //*******************Time Setup***********************
  int counter=0;
  //for showing the time from the server to the client
  time_t time_from_pc;
  struct tm * timeinfo;
  time(&time_from_pc);
  timeinfo = localtime (&time_from_pc);
  //same as echo server
  //****************************************************
  int socket_descriptor=socket(AF_INET, SOCK_STREAM, 0);


  struct sockaddr_in  servaddr;


  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr=INADDR_ANY;
  servaddr.sin_port=htons(PORT);
//binding address 
  if(bind(socket_descriptor,(struct sockaddr*)&servaddr,sizeof(servaddr))==-1){
    perror("bind");
    exit(0);
  }
//listening to the queue 
  listen(socket_descriptor,BACKLOG);

  printf("\nServer Started ...");

while(1){
  counter++;
    printf("\n");
  
    int client_socket = accept(socket_descriptor, NULL, NULL);
    char *string = asctime(timeinfo);

    printf("\nClient %d has requested for time at %s",counter,asctime(timeinfo));
    //sending time to the client side 
    if (send(client_socket, ctime(&time_from_pc), 30, 0) == -1)
      perror("send");
   
  }
  return 0;
}
