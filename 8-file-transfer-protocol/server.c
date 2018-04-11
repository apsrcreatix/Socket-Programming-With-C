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
{   int size;
    int socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_address, client_address;
    socklen_t client_length;
    struct stat x;
    char buffer[100], file[1000];
    FILE *filePointer;
    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(PORT);
    if (bind(socket_descriptor, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
    {
        perror("bind");
    }
    listen(socket_descriptor, 5);
    printf("Server has started working ...");
    int client_descriptor = accept(socket_descriptor,(struct sockaddr*)&client_address,&client_length);

    while(1){
        bzero(buffer,sizeof(buffer));
        bzero(file,sizeof(file));
        recv(client_descriptor,buffer,sizeof(buffer),0);
        filePointer = fopen(buffer,"r");
        stat(buffer,&x);
        size=x.st_size;
        fread(file,sizeof(file),1,filePointer);
        send(client_descriptor,file,sizeof(file),0);
    }
        return 0;
}