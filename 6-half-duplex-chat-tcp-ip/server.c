/*
 * Title : Half duplex server side
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

#define BACKLOG 5 // how many pending connections queue will hold
int main()
{
    //create the server socket
    int server_descriptor;
 
  server_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    //define the server address
    //creating the address as same way we have created for TCPclient

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    //calling bind function to oir specified IP and port
    if(bind(server_descriptor, (struct sockaddr*)&server_address, sizeof(server_address))){
        perror("bind");
    }

    listen(server_descriptor, BACKLOG);
    
    //starting the accepting
    int client_socket = accept(server_descriptor, NULL, NULL);

    while (1)
    {
        char server_message[1000];
        char client_message[1000];
        printf("\ntext message here .. :");
        scanf("%s", server_message);
        //accept(socketWeAreAccepting,structuresClientIsConnectingFrom,)
        //sending data
        //send(toWhom,Message,SizeOfMessage,FLAG);
        send(client_socket, server_message, sizeof(server_message) , 0);
        //recieve the data from the server
        if (recv(client_socket, &client_message, sizeof(client_message), 0) != -1)
        {
            //recieved data from the server successfully then printing the data obtained from the server
            printf("\nCLIENT: %s", client_message);
        }
        else
        {
            perror("recv");
            exit(0);
        }
    }
        //close the socket
        close(server_descriptor);
        return 0;
}
