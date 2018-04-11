#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/stat.h>
int main(int argc, char *argv[])
{
    int sd;
    char buff[1024], file[10000];
    struct sockaddr_in cliaddr, servaddr;
    struct hostent *h;
    socklen_t servlen;
    servlen = sizeof(servaddr);
    h = gethostbyname(argv[1]);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = h->h_addrtype;
    memcpy((char *)&servaddr.sin_addr, h->h_addr_list[0], h->h_length);
    servaddr.sin_port = htons(9976);
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sd < 0)
    {
        printf("Socket CReation Error");
    }
    bind(sd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    while (1)
    {
        printf("\nEnter the command to be executed");
        fgets(buff, 1024, stdin);
        sendto(sd, buff, strlen(buff) + 1, 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
        printf("\nData Sent");
        recvfrom(sd, file, strlen(file) + 1, 0, (struct sockaddr *)&servaddr, &servlen);
        printf("Recieved From UDPSERVER %s", file);
    }
    return 0;
}