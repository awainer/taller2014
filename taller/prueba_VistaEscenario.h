#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include "..\vista\VistaCirculo.h"
#include "..\vista\VistaPoligono.h"
#include "..\model\CoordenadasR2.h"
#include "..\model\Escenario.h"
#include "..\model\Poligono.h"
#include "..\model\Color.h"
#include "vista\VistaEscenario.h"
#include "vista\DatosPantalla.h"
int  prueba_vistaEscenario(){
	Color  rojo = Color(255,0,0);
	Color  azul = Color(0,0,255);
	Color  verde = Color(0,255,0);
	Color violeta = Color(100,100,0);
	SDL_Event evento;
	SDL_Scancode sc;
	bool juegoEnMarcha = true;
	//creo la pantalla
	Escenario * esc = new Escenario(6.4, 4.8,NULL);
	
	// cambio de escala segun Box2D a SDL, necesaria para dibujar en el pixel correcto
	//float xratio = 640 / 6.4f;
	//float yratio = 480 / 4.8f;
	DatosPantalla datos = DatosPantalla(640,480,6.4f,4.8f);
	esc->agregarPelota(  CoordenadasR2(4,4),0.5,azul,true,1);
	esc->agregarPoligono(CoordenadasR2(4,2),1,3,0,rojo,true,2);
	esc->agregarPelota(  CoordenadasR2(2,2),0.2,verde,true,1);
	esc->agregarPelota(  CoordenadasR2(1,0),0.2,violeta,true,1);

	//creo vista del escenario
	VistaEscenario escenario_vista = VistaEscenario(esc,&datos);
	
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

	return 0;
}