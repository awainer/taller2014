

#include "parser\Parser.h"
#include "parser\Funciones.h"
#include "parser\Constantes.h"
#include "EventLogger.h"
#include "model\Escenario.h"
#include "vista\SDL2_gfx\SDL2_framerate.h"
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
	int timerFps;
	
	/*while( juegoEnMarcha ){
		timerFps = SDL_GetTicks(); // SDL_GetTicks() gives the number of milliseconds since the program start.
                                   // I initialize the timer.		
		
		control_jugador.actualizar();
		esc->step();
		timerFps = SDL_GetTicks() - timerFps; //I get the time it took to update and draw;

        if(timerFps < 1000/60.0f) // if timerFps is < 16.6666...7 ms (meaning it loaded the frame too fast)
        {
            SDL_Delay((1000/60.0f) - timerFps); //delay the frame to be in time
        } 
		escenario_vista.mostrar();
	}*/
	FPSmanager fps;
	SDL_initFramerate(&fps);
	SDL_setFramerate(&fps,60);
	while( juegoEnMarcha ){
			
		
		control_jugador.actualizar();
		esc->step();
		std::cout << "frame = " << SDL_getFramerate(&fps) << std::endl;
		SDL_framerateDelay(&fps);

		escenario_vista.mostrar();
	}

	delete esc;

	return 0;
}