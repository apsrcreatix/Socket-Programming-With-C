
/*
 * Title : Full duplex server side 
 * Name : Aditya Pratap Singh Rajput
 * Subject : Network Protocols And Programming

Note : please consider the TYPOS in comments.
Thanks.
*/

#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<unistd.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>

int main(int argc,char *argv[])
{
int ad,sd;
struct sockaddr_in servaddr,cliaddr;
socklen_t servlen,clilen;
char buff[1000],buff1[1000];
pid_t cpid;
bzero(&servaddr,sizeof(servaddr));
/*Socket address structure*/
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
servaddr.sin_port=htons(5500);
/*TCP socket is created, an Internet socket address structure is filled with
wildcard address & server’s well known port*/
sd=socket(AF_INET,SOCK_STREAM,0);
/*Bind function assigns a local protocol address to the socket*/
bind(sd,(struct sockaddr*)&servaddr,sizeof(servaddr));
/*Listen function specifies the maximum number of connections that kernel should queue
for this socket*/
listen(sd,5);
printf("%s\n","Server is running.......");
/*The server to return the next completed connection from the front of the
completed connection Queue calls it*/
ad=accept(sd,(struct sockaddr*)&cliaddr,&clilen);
/*Fork system call is used to create a new process*/
cpid=fork();

if(cpid==0)
{
while(1)
{
bzero(&buff,sizeof(buff));
/*Receiving the request from client*/
recv(ad,buff,sizeof(buff),0);
printf("Received message from the client:%s\n",buff);
}
}
else
{
while(1)
{

bzero(&buff1,sizeof(buff1));
printf("%s\n","Enter the input data:");
/*Read the message from client*/
fgets(buff1,10000,stdin);
/*Sends the message to client*/
send(ad,buff1,strlen(buff1)+1,0);
printf("%s\n","Data sent…");
}
}
return 0;
}
