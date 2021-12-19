#include<sys/types.h>
#include<sys/socket.h>
#include<net/if_arp.h>
#include<sys/ioctl.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<math.h>
#include<complex.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<netinet/if_ether.h>
#include<net/ethernet.h>
#include<stdlib.h>
int main()
{
	struct sockaddr_in sin={0};
	struct arpreq myarp={{0}};
	unsigned char *ptr;
	int sd;
	sin.sin_family=AF_INET;
	printf("Enter IP address: ");
	char ip[20];
	scanf("%s", ip); if(inet_pton(AF_INET,ip,&sin.sin_addr)==0) {
		printf("IP address Entered '%s' is not valid \n",ip);
		exit(0); 
	}
	memcpy(&myarp.arp_pa,&sin,sizeof(myarp.arp_pa));
       	strcpy(myarp.arp_dev,"echo");
       	sd=socket(AF_INET,SOCK_DGRAM,0);
       	printf("\nSend ARP request\n");
       	if(ioctl(sd,SIOCGARP,&myarp)==1)
	{
		printf("No Entry in ARP cache for '%s'\n",ip);
		exit(0);
       	}
	ptr=&myarp.arp_pa.sa_data[0];
	printf("Received ARP Reply\n");
	printf("\nMAC Address for '%s' : ",ip);
       	printf("%p:%p:%p:%p:%p:%p\n",ptr,(ptr+1),(ptr+2),(ptr+3),(ptr+4),(ptr+5));
       	return 0;
}