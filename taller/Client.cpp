#include "Client.h"
#include "net\Packet.h"
#include "net\NewElement.h"

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
	DatosPantalla datos = DatosPantalla(800,600,8.0f,6.0f);
	this->vistaEscenario = new VistaEscenario(&datos);
	this->positionHandler = new PositionHandler(vistaEscenario);
}

void Client::loop(){
	log("LOOP!", DEBUG);
	SDL_Init( SDL_INIT_VIDEO );
	SDL_Event evento;

	bool juegoEnMarcha = true;
	while( juegoEnMarcha ){
		//Dibujo figuras
		log("Render!", DEBUG);
		this->vistaEscenario->mostrar();

		SDL_PollEvent( &evento);
		SDL_Delay(10);
		switch(evento.type)
		{
		case SDL_QUIT:
			juegoEnMarcha= false;
			//delete this->vistaEscenario;
			break;
		}
	}
	SDL_Quit();
}


void Client::connectar(){

	int rsize=0;
	Packet * packet;
	NewElement * newElem;
	connect(this->mySocket , (struct sockaddr *)&(this->server),sizeof(this->server));
	
	do{
		rsize = recv(this->mySocket,this->recbuffer,sizeof(this->recbuffer),0);
		int bytecounter = 0;
		log("Recibo " + std::to_string((long long) rsize) + " bytes.",DEBUG);
		packet = (Packet*) (&(this->recbuffer));
		newElem = (NewElement*) packet;
		while(bytecounter < rsize){
			log("Recibo paquete tipo: "+ std::to_string((long long)packet->type),DEBUG);
			if (packet->type == NEW_ELEMENT){
				log("byteCounter:" + std::to_string((long long)bytecounter),WARNING);
				log("Tamanio de paquete:"  + std::to_string((long long)sizeof(NewElement)),WARNING);
				
				bytecounter = bytecounter + sizeof(NewElement);
				log("PacketPTR: " + std::to_string((long long)packet),DEBUG);
				//packet = (Packet*) ((char*)packet + sizeof(NewElement));
				log("newElem:" + newElem->str(),WARNING);
				newElem++;
			}
		}
	}while(rsize);
	
}

Client::~Client(void)
{
	delete this->positionHandler;
	delete this->vistaEscenario;
}
