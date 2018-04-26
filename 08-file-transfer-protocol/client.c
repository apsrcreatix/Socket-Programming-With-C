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

int main()
{
  
    int serverDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddress;

    char buffer[100], file[1000];
    
    bzero(&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_port = htons(PORT);

    connect(serverDescriptor,(struct sockaddr*)&serverAddress,sizeof(serverAddress));
    
    while (1){
        printf("File name : ");
        scanf("%s",buffer);
        send(serverDescriptor,buffer,strlen(buffer)+1,0);
        printf("%s\n","File Output : ");
        recv(serverDescriptor,&file,sizeof(file),0);
        printf("%s",file);
    }
    return 0;
}                                 