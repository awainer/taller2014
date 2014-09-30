#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include "EventLogger.h"
#include <vista/VistaEscenario.h>
#include <vista/DatosPantalla.h>
#include <vista/PositionHandler.h>
#pragma comment(lib,"ws2_32.lib")

class Client
{
public:
	Client(void);
	void init();
	void connectar();
	void loop();
	~Client(void);
private:
	SOCKET mySocket;
	sockaddr_in server;
	char recbuffer[1024];
	PositionHandler * positionHandler;
	VistaEscenario* vistaEscenario;
};

