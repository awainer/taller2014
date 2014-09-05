#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include "..\vista\VistaCirculo.h"
#include "..\vista\VistaPoligono.h"
#include "..\model\CoordenadasR2.h"
#include "..\model\Escenario.h"
#include "..\model\Poligono.h"
#include "..\model\Color.h"
#include "vista\VistaEscenario.h"

void resizePantalla1(SDL_Window* window,SDL_Renderer* renderer, int ancho,int alto){

			int alto_actual;
			int ancho_actual;
			SDL_GetWindowSize(window,&ancho_actual,&alto_actual);
			
			float ancho_2= (float)ancho;
			float ancho_1= (float)ancho_actual;
			float alto_2= (float)alto;
			float alto_1= (float)alto_actual;

			float resizeX = ancho_2/ancho_1;
			float resizeY = alto_2/alto_1;

			SDL_RenderSetScale(renderer,resizeX,resizeY);
			
			SDL_SetWindowSize(window,ancho,alto);
}

int  prueba_vistaEscenario(){
	Color  rojo = Color(255,0,0);
	Color  azul = Color(0,0,255);
	Color  verde = Color(0,255,0);
	Color violeta = Color(100,100,0);
	int r = SDL_Init(SDL_INIT_EVERYTHING);
	printf("sdl init %d \n",r);
	SDL_Event evento;
	SDL_Scancode sc;
	bool juegoEnMarcha = true;
	//creo la pantalla
	SDL_Window *win = SDL_CreateWindow("Prueba vistaEscenario", 100, 100, 640, 480, SDL_WINDOW_SHOWN);	
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_SOFTWARE);
	Escenario * esc = new Escenario(6.4, 4.8,NULL);
	
	// cambio de escala segun Box2D a SDL, necesaria para dibujar en el pixel correcto
	float xratio = 640 / 6.4f;
	float yratio = 480 / 4.8f;
	esc->agregarPelota(  CoordenadasR2(4,4),0.5,azul,true,1);
	esc->agregarPoligono(CoordenadasR2(4,2),1,3,0,rojo,true,2);
	esc->agregarPelota(  CoordenadasR2(2,2),0.2,verde,true,1);

	//creo vista del escenario
	VistaEscenario escenario_vista = VistaEscenario(ren,xratio,yratio);
	//agrego figuras
	escenario_vista.agregarPelota(esc->getPelotas()[0]);
	escenario_vista.agregarPelota(esc->getPelotas()[1]);
	escenario_vista.agregarPoligonos((Poligono*)esc->getPoligonos()[0]);
	

	
	while( juegoEnMarcha ){
					
		//Dibujo figuras
		escenario_vista.mostrar();

		SDL_PollEvent( &evento);
		esc->step();
		SDL_Delay(30);

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
				resizePantalla1(win,ren,300,100);
			// Aca verifique que si se pone escala (1,1) en el renderder vuelve al estado original de la pantalla si presiono D.
			if( sc == SDL_SCANCODE_D)
				SDL_SetWindowSize(win,640,480);
			
			break;

		}
	}

	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();

	return 0;
}