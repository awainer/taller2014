#include <SDL2\SDL.h>
#undef main
#include "prueba_VistaEscenario.h"
#include "pruebapoligono.h"
#include "pruebaParser.h"
#include "prueba_paralelogramo.h"
#include "prueba_trapecio.h"
#include "pruebaReiniciar.h"
//#include "pruebaSuperposicion.h"
//#include <vld.h>
#undef main
//#include <vld.h>
int main(int argc, char ** argv){
	//pruebaSuperposicion();
	//prueba_vistaEscenario();
	//caca();
	//caca2();
	//pruebaParser();

	char pathChar[2000];
	string path;
	
	if(argc != 2) {
		cout<<"USO: miPrograma.exe miJson.json "<<endl;
		cout<<"Escriba la ubicacion del archivo json: "<<endl;
		cin.getline(pathChar,2000,'\n');
		path = pathChar;
	} else {
		
		path = argv[1];
	}
	
	//prueba_vistaEscenario();
	//caca();
	//caca2();
	pruebaParser(path);
	//pruebaReiniciar();
	//prueba_paralelogramo();
	//prueba_trapecio();
	return 0;
}
