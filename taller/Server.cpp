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

	NewElement * circulo;
	Pelota * p;
	for(std::list<Figura*>::iterator it= pelotas.begin(); it != pelotas.end(); ++it){
		p = (Pelota*) *it;
		circulo = new NewElement(p);
		log("Enviando mensaje de creacion tipo("+ std::to_string((long long)circulo->type)    +") de nueva pelota: [pos: " + circulo->vertices[0].str() + " radio: " + std::to_string((long double)circulo->radio) + " color:" + circulo->color.str() + "]",WARNING);
		send( clientSocket, (char*)circulo , sizeof(NewElement), 0 );
		delete circulo;
	}

	std::list<Figura*> poligonos;
	poligonos = this->esc->getPoligonos();

	Poligono *f;
	NewElement * poligono;
	for(std::list<Figura*>::iterator it=poligonos.begin(); it != poligonos.end(); ++it){
		f = (Poligono *)*it;
		poligono = new NewElement(f);
		log("Enviando mensaje de creacion de nuevo poligono tipo("+ std::to_string((long long)poligono->type) + ") id: " +  std::to_string((long long)poligono->id)   +  " color: " + circulo->color.str() + " lados: " + std::to_string((long long)poligono->lados) + "]",WARNING);
		log("Tamanio de paquete:" + std::to_string((long long)sizeof(NewElement)),WARNING);
		send( clientSocket, (char*)poligono , sizeof(NewElement), 0 );
		delete poligono;
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
