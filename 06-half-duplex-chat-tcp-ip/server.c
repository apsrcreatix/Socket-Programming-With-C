/*
 * Title : Half duplex server side
 * Name : Aditya Pratap Singh Rajput
 * Subject : Network Protocols And Programming using C
 * 
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
#define MAX 1000
#define BACKLOG 5 // how many pending connections queue will hold
int main()
{
    char serverMessage[MAX];
    char clientMessage[MAX];
    //create the server socket
    int  socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(9002);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    //calling bind function to oir specified IP and port
    bind(socketDescriptor, (struct sockaddr*)&serverAddress, sizeof(serverAddress));    

    listen(socketDescriptor, BACKLOG);
    
    //starting the accepting
    int clientSocketDescriptor = accept(socketDescriptor, NULL, NULL);

    while (1)
    {
        printf("\ntext message here .. :");
        scanf("%s", serverMessage);
        send(clientSocketDescriptor, serverMessage, sizeof(serverMessage) , 0);
        //recieve the data from the server
        recv(clientSocketDescriptor, &clientMessage, sizeof(clientMessage), 0) ;
        //recieved data from the server successfully then printing the data obtained from the server
        printf("\nCLIENT: %s", clientMessage);
       
    }
        //close the socket
        close(socketDescriptor);
        return 0;
}
