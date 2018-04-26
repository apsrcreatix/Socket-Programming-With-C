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

//main function
int main(){
    char serverResponse[MAX];
    char clientResponse[MAX];

    //creating a socket
    int socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);

    //placeholder for the hostname and my ip address
    char hostname[MAX], ipaddress[MAX];
struct hostent *hostIP; //placeholder for the ip address
//if the gethostname returns a name then the program will get the ip address
if(gethostname(hostname,sizeof(hostname))==0){
    hostIP = gethostbyname(hostname);//the netdb.h fucntion gethostbyname
}else{
printf("ERROR:FCC4539 IP Address Not ");
}

struct sockaddr_in serverAddress;
serverAddress.sin_family = AF_INET;
serverAddress.sin_port = htons(PORT);
serverAddress.sin_addr.s_addr = INADDR_ANY; 

connect(socketDescriptor, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

// getting the address port and remote host
    printf("\nLocalhost: %s\n", inet_ntoa(*(struct in_addr*)hostIP->h_addr));
    printf("Local Port: %d\n", PORT);
    printf("Remote Host: %s\n", inet_ntoa(serverAddress.sin_addr));

    while (1)
    {   //recieve the data from the server
        recv(socketDescriptor, serverResponse, sizeof(serverResponse), 0);
            //recieved data from the server successfully then printing the data obtained from the server
            printf("\nSERVER : %s", serverResponse);
        
    printf("\ntext message here... :");
    scanf("%s", clientResponse);
    send(socketDescriptor, clientResponse, sizeof(clientResponse), 0);
    }

    //closing the socket
    close(socketDescriptor);
    return 0;
}