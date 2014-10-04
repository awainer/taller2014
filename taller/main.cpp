#include <SDL2\SDL.h>
#undef main
#include "GameLoop.h"
#include "test\pruebapoligono.h"
#include "test\testPositionHandler.h"
#include "Server.h"
#include "Client.h"
#undef main
#include <SDL_thread.h>

int run_server(void * data){
	Server server;
	server.init("");
	return 0;
}


int main(int argc, char ** argv){
	run_server(NULL);	
	/*SDL_Thread *server = NULL;
	SDL_Thread *clientthread = NULL;
	SDL_Thread *client_draw = NULL;
	Client client;
	client.init();
	server = SDL_CreateThread(run_server, "server",NULL);
	clientthread = SDL_CreateThread(run_client, "client",&client );*/
	//SDL_WaitThread(clientthread,NULL);
	//client_draw = SDL_CreateThread(run_client_draw, "client_draw",&client);
	
/*	log("Logger inicializado",DEBUG);

	if (argc != 2){
		log("Cantidad de argumentos incorrecta!",ERROR);
		path = "";
	}else
		 path = string(argv[1]);*/
	
	//pruebaPositionHandler();
	//caca();
	//gameLoop(path);
//	prueba_vistaEscenario();
	return 0;
}
