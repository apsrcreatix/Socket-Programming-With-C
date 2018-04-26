/*
 * Title : Remote command execution using UDP
 * Name : Aditya Pratap Singh Rajput
 * Subject : Network Protocols And Programming

Note : please consider the TYPOS in comments.
Thanks.
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <unistd.h>
    int
    main(int argc, char *argv[])
{
    int sd, size;
    char buff[1024], file[10000];
    struct sockaddr_in cliaddr, servaddr;
    FILE *fp;
    struct stat x;
    socklen_t clilen;
    clilen = sizeof(cliaddr);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(9976);
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sd < 0)
    {
        printf("Socket CReation Error");
    }
    bind(sd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    while (1)
    {
        bzero(buff, sizeof(buff));
        recvfrom(sd, buff, sizeof(buff), 0, (struct sockaddr *)&cliaddr, &clilen);
        strcat(buff, ">file1");
        system(buff);
        fp = fopen("file1", "r");
        stat("file1", &x);
        size = x.st_size;
        fread(file, size, 1, fp);
        sendto(sd, file, sizeof(file), 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
        printf("Data Sent to UDPCLIENT : %s ", buff);
    }
    close(sd);
    return 0;
}