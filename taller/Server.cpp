#include "Server.h"
#define DEFAULT_BUFLEN 512

char recvbuf[DEFAULT_BUFLEN];
int iResult, iSendResult;
int recvbuflen = DEFAULT_BUFLEN;

Server::Server(void)
{
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);

	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons (100);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	SOCKET s = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
	bind(s, (LPSOCKADDR)&addr, sizeof(addr));
	listen(s, SOMAXCONN);
	SOCKET clientSocket = accept(s,NULL,NULL);
	
	do{
		iResult = recv(clientSocket,recvbuf,500,NULL);
		send( clientSocket, recvbuf, iResult, 0 );
	}while (iResult);
}



Server::~Server(void)
{
}
