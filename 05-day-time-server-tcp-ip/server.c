/**
 * Title : Day-Time server
 * Name : Aditya Pratap Singh Rajput
 * Subject : Network Protocols And Programming using C
 * 
 * */

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
  time_t currentTime ;
  time(&currentTime);
  //****************************************************
  
  int countClient = 0;
 
  int socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in  serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr=INADDR_ANY;
  serverAddress.sin_port=htons(PORT);

//binding address 
bind(socket_descriptor,(struct sockaddr*)&serverAddress,sizeof(serverAddress));

//listening to the queue 
  listen(socket_descriptor,BACKLOG);

  printf("\nServer Started ...");

while(1){
  countClient++;
    printf("\n");
  
    int client_socket = accept(socket_descriptor, NULL, NULL);
    // char *string = asctime(timeinfo);

    printf("\nClient %d has requested for time at %s", countClient, ctime(&currentTime));
    
    //sending time to the client side
    // ctime(&time_from_pc)
    send(client_socket,ctime(&currentTime), 30, 0);
     
  }
  return 0;
}
