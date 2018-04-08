/*
 * Title : Full duplex server side
 * Name : Aditya Pratap Singh Rajput
 * Subject : Network Protocols And Programming

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

#define PORT 9002 // port number
#define MAX 1000  //maximum buffer size
#define BACKLOG 5 // how many pending connections queue will hold

//main function
int main(int argc, char *argv[])
{
    //create the server socket
    int server_descriptor;
    // for storing child process id
    pid_t childProcessId;
    
    int _fd;
    
    
    socklen_t servlen, clilen;
    char recvBuffer[MAX], sendBuffer[MAX];
 

    server_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    //define the server address
    //creating the address as same way we have created for TCPclient
    //for client address
    struct sockaddr_in client_address;
    //for server address
    struct sockaddr_in server_address;
    bzero(&server_address, sizeof(server_address));

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    //calling bind function to oir specified IP and port
    if (bind(server_descriptor, (struct sockaddr *)&server_address, sizeof(server_address)))
    {
        perror("bind");
    }

    listen(server_descriptor,BACKLOG);

    printf("%s\n", "Server has stared working ...");

    /*The server to return the next completed connection from the front of the
    completed connection Queue calls it*/
    int client_socket = accept(server_descriptor, (struct sockaddr *)&client_address, &clilen);

    /*Fork system call is used to create a new process*/
    childProcessId = fork();

    if (childProcessId == 0)
    {
        while (1)
        {
            bzero(&recvBuffer, sizeof(recvBuffer));
            /*Receiving the request from client*/
            recv(_fd, recvBuffer, sizeof(recvBuffer), 0);
            printf("Client : %s\n", recvBuffer);
        }
    }
    else
    {
        while (1)
        {

            bzero(&sendBuffer, sizeof(sendBuffer));
            printf("%s\n", "You : ");
            /*Read the message from client*/
            fgets(sendBuffer, 10000, stdin);
            /*Sends the message to client*/
            send(_fd, sendBuffer, strlen(sendBuffer) + 1, 0);
            printf("\n#sent#");
        }
    }
    return 0;
}
