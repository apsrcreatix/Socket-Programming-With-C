# UDP ECHO SERVER

The simplest form of client-server interaction uses unreliable datagram delivery to convey messages from a client to a server and back. Consider, for example, a UDP echo server.

At the server site, a UDP echo server process begins by negotiating with its operating system for permission to use the UDP port ID reserved for the echo service, the UDP echo port.

Once it has obtained permission, the echo server process enters an infiite loop that has three steps:

1. wait for a datagram to amve at the echo port,
2. reverse the source and destination addresses(including source and destination IP addresses as well as UDP port ids) and
3. return the datagram to its original sender.

A UDP message to the UDP echo server, and awaits the reply.
The client expects to receive back exactly the same data as it sent.
The UDP echo service illustrates two important points that are generally true about
client-server interaction. The first concerns the difference between the lifetime of servers and clients:

A server starts execution before interaction begins and (usually) continues to accept requests and send responses without ever terminating.

A server waits for requests at a well-known port that has been
reserved for the service it offers. A client allocates an arbitrary,
unused nonreservedport for its communication.

## Who would use an echo service '?'

It is not a service that the average user finds interesting. However, programmers who design, implement, measure, or modify network protocol software, or network managers who test routes and debug communication problems, often use echo servers in testing. For example, an echo service can be used
to determineif it is possible to reach a remote machine.

## Learn about code

* For implementation of UDP use SOCK_DGRAM

```C
  int serverDescriptor = socket(AF_INET, SOCK_DGRAM, 0);
```

* For sending message use sendto function

```C
  sendto(serverDescriptor,sendMessage,MAXLINE,0,(struct sockaddr*)&serverAddress,addressLength);
```

* For recieving message use recv

```C
  recvfrom(socketDescriptor,message,MAXLINE,0,(struct sockaddr*)&clientAddress,&addressLength);
```

* On server side only use ```bind()``` function