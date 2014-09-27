#pragma once
#pragma comment(lib, "Ws2_32.lib")

#include <winsock2.h>
#include <ws2tcpip.h>

class Server
{
public:
	Server(void);
	~Server(void);
private:
	char recvbuf[500];
};

