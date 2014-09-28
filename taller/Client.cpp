#include "Client.h"
#include "net\Packet.h"

Client::Client(void)
{
}

void Client::init(){
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2),&wsa);
	this->mySocket = socket(AF_INET , SOCK_STREAM , 0 );
	this->server.sin_addr.s_addr = inet_addr("127.0.0.1");
	this->server.sin_family = AF_INET;
    this->server.sin_port = htons( 100 );

}

void Client::connectar(){
	int rsize;
	Packet * packet;
	connect(this->mySocket , (struct sockaddr *)&(this->server),sizeof(this->server));
	rsize = recv(this->mySocket,this->recbuffer,sizeof(this->recbuffer),0);
	log("Recibo " + std::to_string((long long) rsize) + " bytes.",DEBUG);
	packet = (Packet*) (&(this->recbuffer));
	log("Recibo paquete tipo: "+ std::to_string((long long)packet->type),DEBUG);

}

Client::~Client(void)
{
}
