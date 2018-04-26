# Socket in C

_Sockets are low level endpoint used for processing information across a network.Common networking protocols like HTTP and FTP rely on the sockets underneath to make connection._

## Client Socket Workflow

**socket()
|
connect()
|
recv()**

* The client socket is created with a socket() call, and the connected to a remote address with the connect() call, and then finally can retrive data with recv() call.

* The client socket is created with a socket() call, and the connected to a remote address with the connect() call, and then finally can retrive data with recv() call.

## Server Socket Workflow

* On the "server" end of the socket,we need to also create a socket with a socket() call, but we need to bind() that socket to an IP and port where it can then listen() for connections, finally accept() a connection and then send() or recv() data to the other sockets it has connected to.

**socket()
|
bind()
|
listen()
|
accept()**

### Understanding Client Side Code

```C
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
//TCP vs UDP --- SOCK_STREAM for TCP
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
server_address.sin_addr.s_addr = INADDR_ANY; //INADDR_ANY is for connection with 0000
//connect returns us a response that connection is establlised or not
int connect_status = connect(network_socket,(struct sockaddr *) &server_address, sizeof(server_address));
//check for the error with the connection

if (connect_status == -1){
printf("There was an error making a connection to socket\n" );
}

//recieve data from the server
char server_response[256];

//recieve the data from the server
recv(network_socket,&server_response,sizeof(server_response),0);

//recieved data from the server successfully then printing the data obtained from the server

printf("Ther server sent the data : %s",server_response);

//closing the socket
close(network_socket);
return 0;
}
```

### Understanding Server Side Code

```C
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
```