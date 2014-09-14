

#include "parser\Parser.h"
#include "parser\Funciones.h"
#include "parser\Constantes.h"
#include "EventLogger.h"
#include "model\Escenario.h"
#include "vista\SDL2_gfx\SDL2_framerate.h"

Escenario* iniciar(){
	Parser parser = Parser();
	parser.Inicializar();
	Escenario* esc = parser.CrearObjetos();
	
	return esc;
}

int pruebaParser(string path){
	Color  rojo = Color(255,0,0);
	Color  azul = Color(0,0,255);
	Color  verde = Color(0,255,0);
	Color violeta = Color(100,100,0);
	SDL_Event evento;
	SDL_Scancode sc;
	Parser parser = Parser(path);
	parser.Inicializar();
	Escenario * esc = parser.CrearObjetos();
	DatosPantalla datos = parser.CargarDatosPantalla();

	bool juegoEnMarcha = true;
	VistaEscenario* escenario_vista = new  VistaEscenario(esc,&datos);
	Jugador* jugador = *(esc->getJugadores().begin());
	
	if ( escenario_vista->agregarJugador(jugador) == true){
	
		ControladorJugador* control_jugador = new ControladorJugador(jugador);
		FPSmanager fps;
		SDL_initFramerate(&fps);
		SDL_setFramerate(&fps,60);

		while( juegoEnMarcha ){


			control_jugador->actualizar();
			esc->step();
			SDL_framerateDelay(&fps);
			escenario_vista->mostrar();

			SDL_PollEvent( &evento);
			switch(evento.type){
			case SDL_QUIT:
				juegoEnMarcha= false;
				break;
			case SDL_KEYDOWN:
				sc = evento.key.keysym.scancode;
				break;
			case SDL_KEYUP:
				//se ejecuta instruccion cuando la tecla deja de ser presionada
				sc = evento.key.keysym.scancode;
				if( sc == SDL_SCANCODE_R){
					delete control_jugador;
					delete escenario_vista;
					delete esc;

					esc= iniciar();
					escenario_vista = new VistaEscenario(esc,&datos);
					Jugador* jugador = *(esc->getJugadores().begin());
					escenario_vista->agregarJugador(jugador);
					control_jugador = new ControladorJugador(jugador);
				}
				break;
			}

		}

		delete control_jugador;
	}
	delete escenario_vista;
	delete esc;

	return 0;
}