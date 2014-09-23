#include "parser\Parser.h"
#include "parser\Funciones.h"
#include "parser\Constantes.h"
#include "EventLogger.h"
#include "model\Escenario.h"
#include <SDL.h>
#include "vista\VistaEscenario.h"
#include "vista\DatosPantalla.h"

Escenario* iniciar(){
	Parser parser = Parser();
	parser.Inicializar();
	Escenario* esc = parser.CrearObjetos();
	
	return esc;
}

int pruebaReiniciar(){
	Color  rojo = Color(255,0,0);
	Color  azul = Color(0,0,255);
	Color  verde = Color(0,255,0);
	Color violeta = Color(100,100,0);
	//SDL_Init( SDL_INIT_VIDEO );
	//int imgFlags = IMG_INIT_JPG|IMG_INIT_PNG;
	//IMG_Init( imgFlags );
	SDL_Event evento;
	SDL_Scancode sc;
	bool juegoEnMarcha = true;
	Escenario* esc = iniciar();
	DatosPantalla datos = DatosPantalla(700,500,7.0f,5.0f);
	VistaEscenario* escenario_vista = new VistaEscenario(esc,&datos);
	//escenario_vista->agregarFondo("imagenes/homero.png");
	
	while( juegoEnMarcha ){
					
		//Dibujo figuras
		escenario_vista->mostrar();

		SDL_PollEvent( &evento);
		esc->step();
		SDL_Delay(10);

		switch(evento.type)
		{
		case SDL_QUIT:
			juegoEnMarcha= false;
			delete escenario_vista;
			break;
		case SDL_KEYDOWN:
			sc = evento.key.keysym.scancode;
			break;
		case SDL_KEYUP:
			//se ejecuta instruccion cuando la tecla deja de ser presionada
			sc = evento.key.keysym.scancode;
			if( sc == SDL_SCANCODE_R){
				delete escenario_vista;
				delete esc;
				esc = iniciar();
				escenario_vista = new VistaEscenario(esc,&datos);
			}
			break;

		}
	}

	//delete escenario_vista;
	delete esc;
	//IMG_Quit();
	//SDL_Quit();
	return 0;
}