/*
Creating the TCP Client workflow in this program using C.

 * Title : TCP client
 * Name : Aditya Pratap Singh Rajput
 * Subject : Network Protocols And Programming using C
Note : please consider the TYPOS in comments.
Thanks.
*/

// adding headers 
#include <stdio.h>
#include <stdlib.h>
//for socket and related functions
#include <sys/types.h>
#include <sys/socket.h>
//for including structures which will store information needed
#include <netinet/in.h>
#include <unistd.h>
#define SIZE 1000

//main functions
int main()
{
  int socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
// server address
  struct sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(9002);
  serverAddress.sin_addr.s_addr = INADDR_ANY;

// communicates with listen
  connect(socketDescriptor, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

  char serverResponse[SIZE];
  recv(socketDescriptor, &serverResponse, sizeof(serverResponse), 0);
  printf("Ther server sent the data : %s", serverResponse);

  //closing the socket
  close(socketDescriptor);
  return 0;
}
