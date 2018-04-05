# Socket in C

Sockets are low level endpoint used for processing information across a network.
common networking protocols like HTTP and FTP rely on the sockets underneath to make connection.

## client socket workflow

## Client socket workflow

**socket()
|
connect()
|
recv()**

- The client socket is created with a socket() call, and the connected to a remote address with the connect() call, and then finally can retrive data with recv() call.

the client socket is created with a socket() call, and the connected to a remote address with the connect() call, and then finally can retrive data with recv() call.

## server socket workflow

on the "server" end of the socket,we need to also create a socket with a socket() call,
but then,we need to bind(),that socket to an IP and port where it can then listen() for
connections, and then finally accept() a connection and then send() or recv() data to the
other sockets it has connected to

socket()
|
bind()
|
listen()
|
accept()
