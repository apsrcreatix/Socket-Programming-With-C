/*
 * Title : Full duplex client side 
 * Name : Aditya Pratap Singh Rajput
 * Subject : Network Protocols And Programming using C
Note : please consider the TYPOS in comments.
Thanks.
*/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
//headers for socket and related functions
#include <sys/types.h>
#include <sys/socket.h>
//for including structures which will store information needed
#include <netinet/in.h>
#include <unistd.h>
//for gethostbyname
#include "netdb.h"
#include "arpa/inet.h"

int main()
{
int socketDescriptor;

struct sockaddr_in serverAddress;
char sendBuffer[1000],recvBuffer[1000];

pid_t cpid;

bzero(&serverAddress,sizeof(serverAddress));

serverAddress.sin_family=AF_INET;
serverAddress.sin_addr.s_addr=inet_addr("127.0.0.1");
serverAddress.sin_port=htons(5500);

/*Creating a socket, assigning IP address and port number for that socket*/
socketDescriptor=socket(AF_INET,SOCK_STREAM,0);

/*Connect establishes connection with the server using server IP address*/
connect(socketDescriptor,(struct sockaddr*)&serverAddress,sizeof(serverAddress));

/*Fork is used to create a new process*/
cpid=fork();
if(cpid==0)
{
while(1)
{
bzero(&sendBuffer,sizeof(sendBuffer));
printf("\nType a message here ...  ");
/*This function is used to read from server*/
fgets(sendBuffer,10000,stdin);
/*Send the message to server*/
send(socketDescriptor,sendBuffer,strlen(sendBuffer)+1,0);
printf("\nMessage sent !\n");
}
}
else
{
while(1)
{
bzero(&recvBuffer,sizeof(recvBuffer));
/*Receive the message from server*/
recv(socketDescriptor,recvBuffer,sizeof(recvBuffer),0);
printf("\nSERVER : %s\n",recvBuffer);
}
}
return 0;
}
