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
#include <vld.h>
//#include <vld.h>
int main(int argc, char ** argv){
	//pruebaSuper();
	//pruebaSuperposicion();
	//prueba_vistaEscenario();
	//caca();
	//caca2();
	//string path = "";
	pruebaParser(string(argv[1]));
	/*
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
	
	prueba_vistaEscenario();*/

	//prueba_vistaEscenario();

	//caca();
	//caca2();
	//pruebaParser("");
	//pruebaReiniciar();
	//prueba_paralelogramo();
	//prueba_trapecio();
	return 0;
}
