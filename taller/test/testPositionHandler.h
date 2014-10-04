#include <SDL.h>
#include "../vista/VistaEscenario.h"
#include "../vista/DatosPantalla.h"
#include "../vista/PositionHandler.h"
#include "../net/NewElement.h"
#include "../net/NewPosition.h"
#include "../constantes.h"
int pruebaPositionHandler(){
	Color  rojo = Color(255,0,0);
	Color  azul = Color(0,0,255);
	Color  verde = Color(0,255,0);
	Color violeta = Color(100,100,0);
	SDL_Init( SDL_INIT_VIDEO );
	SDL_Event evento;
//	SDL_Scancode sc;
	bool juegoEnMarcha = true;

	DatosPantalla datos = DatosPantalla(800,600,8.0f,6.0f);
	VistaEscenario* escenario_vista = new VistaEscenario(&datos);
	PositionHandler manejador = PositionHandler(escenario_vista);
	
	
	NewElement e_circulo;
	float x ,y;
	x= 2;
	y= 2;
	e_circulo.radio = 1;
	e_circulo.vertices[0].x = x;
	e_circulo.vertices[0].y = y;
	e_circulo.vertices[1].x = x+ 0.5f;
	e_circulo.vertices[1].y = y+ 0.5f;
	e_circulo.color = rojo;
	e_circulo.id = 3;
	e_circulo.tipo_figura = CIRCULO;//CIRCULO

	manejador.addData(&e_circulo);
	NewPosition pos;
	pos.id_figura = 3;

	//escenario_vista->agregarFondo("imagenes/homero.png");
	
	while( juegoEnMarcha ){
					
		//Dibujo figuras
		escenario_vista->mostrar();

		SDL_PollEvent( &evento);
		SDL_Delay(100);
		pos.vertices[0].x = x++;
		pos.vertices[0].y = y;
		pos.vertices[1].x = x;
		pos.vertices[1].y = y;
		manejador.updateData(&pos);
		switch(evento.type)
		{
		case SDL_QUIT:
			juegoEnMarcha= false;
			delete escenario_vista;
			break;
		}
	}
	SDL_Quit();
	return 0;
}