

#include "parser\Parser.h"
#include "parser\Funciones.h"
#include "parser\Constantes.h"
#include "parser\EventLogger.h"
#include "model\Escenario.h"

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
	
	//DatosPantalla datos = DatosPantalla(700,500,7.0f,5.0f);
	DatosPantalla datos = parser.CargarDatosPantalla();

	bool juegoEnMarcha = true;
	VistaEscenario escenario_vista = VistaEscenario(esc,&datos);
	Jugador* jugador = *(esc->getJugadores().begin());
	escenario_vista.agregarJugador(jugador);
	ControladorJugador control_jugador = ControladorJugador(jugador);
	while( juegoEnMarcha ){
					
		//Dibujo figuras
		escenario_vista.mostrar();

		control_jugador.actualizar();

		esc->step();
		SDL_Delay(10);
	}


	delete esc;

	return 0;
}