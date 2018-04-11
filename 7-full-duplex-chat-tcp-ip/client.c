/*
 * Title : Full duplex client side 
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

//main function
int main(int argc, char *argv[])
{

    int _fd;

    struct sockaddr_in  client_address;

    //creating buffers for receiving and sending messages 
    char sendBuffer[MAX], recvBuffer[MAX];

    //for storing child process id
    pid_t childProcessId;
    
    //creating a socket
    int network_socket;
    
    //calling socket function and storing the result in the variable
    //socket(domainOfTheSocket,TypeOfTheSocket,FlagForProtocol{0 for default protocol i.e, TCP})
    //AF_INET = constant defined in the header file for us
    //TCP vs UDP --- SOCK_STRAM for TCP
    // flag 0 for TCP (default protocol)
    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    //creating network connection
    //in order to connect to the other side of the socket we need to declare connect
    //with specifying address where we want to connect to
    //already defined struct sockaddr_in
    struct sockaddr_in server_address;

    bzero(&server_address, sizeof(server_address));

    struct hostent *host;
    host=gethostbyname("127.0.0.1");
    //for taking the port number and htons converts the port # to the appropriate data type we want to write
    //to specifying the port
    //htons : conversion functions
    server_address.sin_port = htons(PORT);
   
    //structure within structure A.B.c
    memcpy((char *)&server_address.sin_addr.s_addr,host->h_addr_list[0],host->h_length); 

    //what type of address we are woking with
    server_address.sin_family = host->h_addrtype;
    
    //connect returns us a response that connection is establlised or not
    //check for the error with the connection
    if (connect(network_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
    {
        perror("error");
        exit(0);
    }

   
    //fork() is used to create a new process
    childProcessId=fork();

    if (childProcessId==0)
    {
        while (1)
        {
            bzero(&sendBuffer, sizeof(sendBuffer));
            printf("%s\n","You : ");
            fgets(sendBuffer, 10000, stdin);
            /*Send the message to server using send*/
            send(_fd, sendBuffer, strlen(sendBuffer)+1, 0);
            printf("\n#sent#");
        }
    }
    else
    {
        while (1)
        {
            bzero(&recvBuffer, sizeof(recvBuffer));
            /*Receive the message from server using recv*/
            recv(_fd, recvBuffer, sizeof(recvBuffer), 0);
            printf("Server : %s\n", recvBuffer);
        }
    }
    return 0;
}
