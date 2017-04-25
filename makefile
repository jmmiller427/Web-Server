all: myserver

myserver: AcceptTCPConnection.c  CreateTCPServerSocket.c  DieWithError.c  HandleTCPClient.c TCPEchoServer-Fork.c  TCPEchoServer.h
	gcc -g AcceptTCPConnection.c  CreateTCPServerSocket.c  DieWithError.c  HandleTCPClient.c TCPEchoServer-Fork.c  TCPEchoServer.h -o myserver

clean:
	-rm -f myserver
