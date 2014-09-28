#include <SDL2\SDL.h>
#undef main
#include "GameLoop.h"
#include "test\pruebapoligono.h"
#include "test\testPositionHandler.h"
#include "Server.h"
#undef main

int main(int argc, char ** argv){
	string path;
	Server server;
	

	log("Logger inicializado",DEBUG);

	if (argc != 2){
		log("Cantidad de argumentos incorrecta!",ERROR);
		path = "";
	}else
		 path = string(argv[1]);
	server.init(path);
	//pruebaPositionHandler();
	//caca();
	//gameLoop(path);
//	prueba_vistaEscenario();
	return 0;
}
