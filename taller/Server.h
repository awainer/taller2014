#pragma once
#pragma comment(lib, "Ws2_32.lib")

#include <winsock2.h>
#include <ws2tcpip.h>
#include "parser\Parser.h"
#include "model\Escenario.h"
class Server
{
public:
	Server(void);
	void init(string path);
	void sendInitialStatus(SOCKET clientSocket);
	~Server(void);
private:
	char recvbuf[500];
	Escenario * esc;
	void initSocket();
	SOCKET listenSocket;
};

