/*
 * Title : Half duplex client side 
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

//defines
#define h_addr h_addr_list[0] /* for backward compatibility */

#define PORT 9002 // port number
#define MAX 1000  //maximum buffer size
#define MAX_ONE 1000  //maximum buffer size : second option

//main function
int main(){
   
    //creating a socket
    int network_socket;
    
    //placeholder for the hostname and my ip address
    char hostname[MAX_ONE], ipaddress[MAX_ONE];

struct hostent *hostIP; //placeholder for the ip address

//if the gethostname returns a name then the program will get the ip address
if(gethostname(hostname,sizeof(hostname))==0){
    hostIP = gethostbyname(hostname);//the netdb.h fucntion gethostbyname
}else{
printf("ERROR:FCC4539 IP Address Not ");
}

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
//what type of address we are woking with
server_address.sin_family = AF_INET;
//for taking the port number and htons converts the port # to the appropriate data type we want to write
//to specifying the port
//htons : conversion functions
server_address.sin_port = htons(PORT);
//structure within structure A.B.c
server_address.sin_addr.s_addr = INADDR_ANY; //INADDR_ANY is for connection with 0000
//connect returns us a response that connection is establlised or not
//check for the error with the connection
if (connect(network_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
{
    perror("error");
    exit(0);
    }

// getting the address port and remote host
    printf("\nLocalhost: %s\n", inet_ntoa(*(struct in_addr*)hostIP->h_addr));
    printf("Local Port: %d\n", PORT);
    printf("Remote Host: %s\n", inet_ntoa(server_address.sin_addr));

    while (1)
    {

        

        //recieve data from the server
        char server_response[MAX];
        char client_response[MAX];
        //recieve the data from the server
        if (recv(network_socket, server_response, sizeof(server_response), 0))
            //recieved data from the server successfully then printing the data obtained from the server
            printf("\nSERVER : %s", server_response);
        printf("\ntext message here... :");
        scanf("%s", client_response);

    send(network_socket, client_response, sizeof(client_response), 0);
    //closing the socket
   
    }
    close(network_socket);
    return 0;
}