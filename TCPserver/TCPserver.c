#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <unistd.h> 
int main(){
  char server_message[256] = "You have a missed call from server";
//create the server socket
  int server_socket;
  server_socket = socket(AF_INET,SOCK_STREAM,0);
  //define the server address
  //creating the address as same way we have created for TCPclient

  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(9002);
  server_address.sin_addr.s_addr = INADDR_ANY;

  //calling bind function to oir specified IP and port
  bind(server_socket,(struct sockaddr*) &server_address,sizeof(server_address));

  listen(server_socket,5);

  //starting the accepting
  int client_socket;
  //accept(socketWeAreAccepting,structuresClientIsConnectingFrom,)
  client_socket = accept(server_socket,NULL,NULL);
  //sending data
  //send(toWhom,Message,SizeOfMessage,FLAG);
  send(client_socket,server_message,sizeof(server_message),0);
//close the socket
  close(server_socket);
    return 0;
}
