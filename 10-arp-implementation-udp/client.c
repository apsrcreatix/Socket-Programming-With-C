#include <sys/types.h>
#include <sys/socket.h>
#include <net/if_arp.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
int main(int argc, char *argv[])
{
    struct sockaddr_in sin = {0};
    struct arpreq myarp = {{0}};
    unsigned char *ptr;
    int sd;
    sin.sin_family = AF_INET;
    if (inet_aton(argv[1], &sin.sin_addr) == 0)
    {
        printf("Ip address Entered '%s' is not valid \n", argv[1]);
        exit(0);
    }
    memcpy(&myarp.arp_pa, &sin, sizeof(myarp.arp_pa));
    strcpy(myarp.arp_dev, "eth0");
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    if (ioctl(sd, SIOCGARP, &myarp) == 1)
    {
        printf("No Entry in ARP Cache for '%s'", argv[1]);
        exit(0);
    }
    ptr = &myarp.arp_ha.sa_data[0];
    printf("MAC Address For '%s' : ", argv[1]);
    printf("%X:%X:%X:%X:%X:%X\n", *ptr, *(ptr + 1), *(ptr + 2), *(ptr + 3), *(ptr + 4), *(ptr + 5), *(ptr + 5));
    return 0;
}