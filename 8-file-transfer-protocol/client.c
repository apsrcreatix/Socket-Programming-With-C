/*
 * Title : File Transfer Protocol 
 * Name : Aditya Pratap Singh Rajput
 * Subject : Network Protocols And Programming

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
    int socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_address, client_address;
    socklen_t client_length;
    client_length = sizeof(client_address);
    struct stat x;
    char buffer[100], file[1000];
    FILE *filePointer;
    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(PORT);

    connect(socket_descriptor,(struct sockaddr*)&server_address,sizeof(server_address));
    
    while (1){
        printf("File name : ");
        scanf("%s",buffer);
        send(socket_descriptor,buffer,strlen(buffer)+1,0);
        printf("%s\n","File Output : ");
        recv(socket_descriptor,file,sizeof(file),0);
        printf("%s",file);
    }
    return 0;
}