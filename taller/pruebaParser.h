

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
		escenario_vista.agregarFondo("imagenes/homero.png");
	
	while( juegoEnMarcha ){
					
		//Dibujo figuras
		escenario_vista.mostrar();

		SDL_PollEvent( &evento);
		esc->step();
		SDL_Delay(10);

		switch(evento.type)
		{
		case SDL_QUIT:
			juegoEnMarcha= false;
			break;
		case SDL_KEYDOWN:
			sc = evento.key.keysym.scancode;
			if( sc == SDL_SCANCODE_C)
				//se ejecuta instruccion mientras la tecla esta presionada
			break;
		case SDL_KEYUP:
			//se ejecuta instruccion cuando la tecla deja de ser presionada
			sc = evento.key.keysym.scancode;
			// si se presiona por segunda vez C la segunda redimensiona al formato original porque 300/300 =1 es decir escala original 
			if( sc == SDL_SCANCODE_C) 
				escenario_vista.resize(300,100);
			// Aca verifique que si se pone escala (1,1) en el renderder vuelve al estado original de la pantalla si presiono D.
			if( sc == SDL_SCANCODE_D)
				escenario_vista.resize(640,480);
			break;

		}
	}


	delete esc;

	return 0;
}