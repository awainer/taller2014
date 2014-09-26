#include <SDL2\SDL.h>
#undef main
#include "GameLoop.h"
#include "test\prueba_VistaEscenario.h"
#undef main

int main(int argc, char ** argv){
	string path;
	log("Logger inicializado",DEBUG);

	if (argc != 2){
		log("Cantidad de argumentos incorrecta!",ERROR);
		 path = "";
	}else
		 path = string(argv[1]);

	gameLoop(path);
	prueba_vistaEscenario();
	return 0;
}
