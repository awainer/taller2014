#include <SDL2\SDL.h>
#undef main
#include "prueba_VistaEscenario.h"
#include "pruebapoligono.h"
#include "pruebaParser.h"
#include "prueba_paralelogramo.h"
#include "prueba_trapecio.h"
//#include "pruebaReiniciar.h"
#include "pruebaSuper.h"
#undef main

int main(int argc, char ** argv){
	string path;
	log("Logger inicializado",DEBUG);

	if (argc != 2){
		log("Cantidad de argumentos incorrecta!",ERROR);
		 path = "";
	}else
		 path = string(argv[1]);

	pruebaParser(path);
	return 0;
}
