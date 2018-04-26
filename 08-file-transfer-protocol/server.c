/*
 * Title : File Transfer Protocol 
 * Name : Aditya Pratap Singh Rajput
 * Subject : Network Protocols And Programming using C
 * 
Note : Please consider the TYPOS in comments.
Thanks.
*/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
//headers for socket and related functions
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
//for including structures which will store information needed
#include <netinet/in.h>
#include <unistd.h>
//for gethostbyname
#include "netdb.h"
#include "arpa/inet.h"

// defining constants
#define PORT 9002
#define BACKLOG 5
int main()
{
    int size;
    int socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddress, clientAddress;
   
    socklen_t clientLength;
    
    struct stat statVariable;
   
    char buffer[100], file[1000];
    
    FILE *filePointer;
    bzero(&serverAddress, sizeof(serverAddress));
    
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(PORT);
    
    bind(socketDescriptor, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
 
    listen(socketDescriptor,BACKLOG);

    printf("Server has started working ...");
    int clientDescriptor = accept(socketDescriptor,(struct sockaddr*)&clientAddress,&clientLength);

    while(1){
        bzero(buffer,sizeof(buffer));
        bzero(file,sizeof(file));
        recv(clientDescriptor,buffer,sizeof(buffer),0);
        filePointer = fopen(buffer,"r");
        stat(buffer,&statVariable);
        size=statVariable.st_size;
        fread(file,sizeof(file),1,filePointer);
        send(clientDescriptor,file,sizeof(file),0);
    }
        return 0;
}