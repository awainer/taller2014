#include "Server.h"
#define DEFAULT_BUFLEN 512

char recvbuf[DEFAULT_BUFLEN];
int iResult, iSendResult;
int recvbuflen = DEFAULT_BUFLEN;

Server::Server(void)
{	
	//do{
	//	iResult = recv(clientSocket,recvbuf,500,NULL);
	//	send( clientSocket, recvbuf, iResult, 0 );
	//}while (iResult);
}

void Server::initSocket(){
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons (100);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	this->listenSocket = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
	bind(this->listenSocket , (LPSOCKADDR)&addr, sizeof(addr));
	listen(this->listenSocket, SOMAXCONN);
}

void Server::sendInitialStatus(SOCKET clientSocket){
	std::list<Figura*>  pelotas;
	pelotas = this->esc->getPelotas();

	DatosCirculo * circulo;
	Pelota * p;
	for(std::list<Figura*>::iterator it= pelotas.begin(); it != pelotas.end(); ++it){
		p = (Pelota*) *it;
		circulo = new DatosCirculo(p);
		log("Enviando mensaje de creacion de nueva pelota: [pos: " + circulo->getPosicion().str() + " radio: " + std::to_string((long long)circulo->getRadio()) + " color:" + circulo->color.str() + "]",WARNING);
		send( clientSocket, (char*)circulo , sizeof(DatosCirculo), 0 );
		delete circulo;
	}

	std::list<Figura*> poligonos;
	poligonos = this->esc->getPoligonos();

	Poligono *f;
	DatosPoligono * poligono;
	for(std::list<Figura*>::iterator it=poligonos.begin(); it != poligonos.end(); ++it){
		f = (Poligono *)*it;
		poligono = new DatosPoligono(f);
		log("Enviando mensaje de creacion de nuevo poligono  color:" + circulo->color.str() + " lados: " + std::to_string((long long)poligono->getVertexCount()) + "]",WARNING);
		send( clientSocket, (char*)poligono , sizeof(DatosPoligono), 0 );
	}
}
void Server::init(string path){
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	Parser parser = Parser(path);
	parser.Inicializar();
	this->esc = parser.CrearObjetos();
	this->initSocket();	
	SOCKET clientSocket = accept(this->listenSocket,NULL,NULL);
	this->sendInitialStatus(clientSocket);
}

Server::~Server(void)
{
}
