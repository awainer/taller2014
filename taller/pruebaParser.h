

#include "parser\Parser.h"
#include "parser\Funciones.h"
#include "parser\Constantes.h"
#include "parser\EventLogger.h"
#include "model\Escenario.h"

int pruebaParser(){
	Color  rojo = Color(255,0,0);
	Color  azul = Color(0,0,255);
	Color  verde = Color(0,255,0);
	Color violeta = Color(100,100,0);
	SDL_Event evento;
	SDL_Scancode sc;
	Parser parser = Parser();
	parser.Inicializar();
	Escenario * esc = parser.CrearObjetos();
	
	//DatosPantalla datos = DatosPantalla(700,500,7.0f,5.0f);
	DatosPantalla datos = parser.CargarDatosPantalla();

	VistaEscenario escenario_vista = VistaEscenario(esc,&datos);

	bool juegoEnMarcha = true;
	Jugador* jugador = esc->getJugadores()[0];
	ControladorJugador control_jugador = ControladorJugador(jugador);
	escenario_vista.agregarJugador(esc->getJugadores()[0]);
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