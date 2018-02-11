/*
Creating the TCP Client workflow in this program using C.
By Aditya Pratap Singh Rajput


Note : please consider the TYPOS in comments.
Thanks.
*/
//adding includes
#include <stdio.h>
#include <stdlib.h>
//for socket and related functions
#include <sys/types.h>
#include <sys/socket.h>
//for including structures which will store information needed
#include <netinet/in.h>
#include <unistd.h>
//main functions
int main(){
  //creating a socket
  int network_socket;
  //calling socket function and storing the result in the variable
  //socket(domainOfTheSocket,TypeOfTheSocket,FlagForProtocol{0 for default protocol i.e, TCP})
  //AF_INET = constant defined in the header file for us
  //TCP vs UDP --- SOCK_STRAM for TCP
  // flag 0 for TCP (default protocol)
  network_socket = socket(AF_INET,SOCK_STREAM,0);
  //creating network connection
  //in order to connect to the other side of the socket we need to declare connect
  //with specifying address where we want to connect to
  //already defined struct sockaddr_in
  struct sockaddr_in server_address;
  //what type of address we are woking with
  server_address.sin_family = AF_INET;
//for taking the port number and htons converts the port # to the appropriate data type we want to write
//to specifying the port
//htons : conversion functions
  server_address.sin_port = htons(9002);
  //structure within structure A.B.c
  server_address.sin_addr.s_addr = INADDR_ANY;//INADDR_ANY is for connection with 0000
//connect returns us a response that connection is establlised or not
int connect_status =  connect(network_socket,(struct sockaddr *) &server_address, sizeof(server_address));
//check for the error with the connection
if (connect_status == -1){
  printf("There was an error making a connection to socket\n" );
}
//recieve data from the server
char server_response[256];
//recieve the data from the server
recv(network_socket,&server_response,sizeof(server_response),0);
//recieved data from the server successfully then printing the data obtained from the server

printf("Ther server sent the data : %s\n",server_response);
//closing the socket
close(network_socket);
  return 0;
}
