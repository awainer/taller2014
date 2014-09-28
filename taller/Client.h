#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include "EventLogger.h"
#pragma comment(lib,"ws2_32.lib")

class Client
{
public:
	Client(void);
	void init();
	void connectar();
	~Client(void);
private:
	SOCKET mySocket;
	sockaddr_in server;
	char recbuffer[1024];
};

