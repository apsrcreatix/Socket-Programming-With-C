/*
Creating the TCP socket workflow in this program using C.

 * Title : TCP client
 * Name : Aditya Pratap Singh Rajput
 * Subject : Network Protocols And Programming using C
Note : please consider the TYPOS in comments.
Thanks.
*/
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <unistd.h>

int main(){
  
  char serverMessage[256] = "You have a missed call from server\n";

    //create the server socket
   int socketDescriptor = socket(AF_INET,SOCK_STREAM,0);
  
  //define the server address
  //creating the address as same way we have created for TCPclient
  struct sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(9002);
  serverAddress.sin_addr.s_addr = INADDR_ANY;

  //calling bind function to oir specified IP and port
  bind(socketDescriptor,(struct sockaddr*) &serverAddress,sizeof(serverAddress));

  listen(socketDescriptor,5);

  //starting the accepting 
  //accept(socketWeAreAccepting,structuresClientIsConnectingFrom,)
  int client_socket = accept(socketDescriptor, NULL, NULL);
  
  //sending data
  //send(toWhom,Message,SizeOfMessage,FLAG);
  send(client_socket,serverMessage,sizeof(serverMessage),0);

  //close the socket
  close(socketDescriptor);
    return 0;
}
