#include "vista\VistaRectangulo.h"
#include <SDL2\SDL.h>

#include "..\vista\VistaCirculo.h"
#include "..\vista\VistaPoligono.h"
#include "..\model\CoordenadasR2.h"
#include "..\model\Escenario.h"
#include "..\model\Poligono.h"


int  caca(){

	int r = SDL_Init(SDL_INIT_EVERYTHING);
	printf("sdl init %d \n",r);
	SDL_Event evento;
	const Uint8* m_keys = SDL_GetKeyboardState(NULL);
	bool juegoEnMarcha = true;
	//creo la pantalla
	SDL_Window *win = SDL_CreateWindow("Prueba poligono, rectangulo", 100, 100, 640, 480, SDL_WINDOW_SHOWN);	
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_SOFTWARE);
	Escenario * esc = new Escenario(6.4, 4.8,NULL);
	
	// cambio de escala segun Box2D a SDL, necesaria para dibujar en el pixel correcto
	float xratio = 640 / 6.4f;
	float yratio = 480 / 4.8f;
	esc->agregarPelota(CoordenadasR2(2,2));
	/*esc->agregarPoligono(CoordenadasR2(100,100),30,3,0);
	esc->agregarPoligono(CoordenadasR2(200,100),30,4,45);
	esc->agregarPoligono(CoordenadasR2(300,100),30,8,90);*/


	VistaCirculo circulo = VistaCirculo(ren,esc->getPelotas()[0],xratio,yratio); 
	/*VistaPoligono poligono = VistaPoligono(ren,(Poligono*)esc->getPoligonos()[0]);
	VistaPoligono poligono2 = VistaPoligono(ren,(Poligono*)esc->getPoligonos()[1]);
	VistaPoligono poligono3 = VistaPoligono(ren,(Poligono*)esc->getPoligonos()[2]);*/


	
	int x,y;
	x=0;
	y=0;
	
	//std::vector<CoordenadasR2> vector = esc->getPoligonos()[0]->getVertices();
	while( juegoEnMarcha ){
				
		//Clear screen
		
		SDL_SetRenderDrawColor( ren, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( ren );
		circulo.render();
	/*	poligono.render();
		poligono2.render();
		poligono3.render();*/
		
		SDL_RenderPresent(ren);
		SDL_PollEvent( &evento);
		esc->step();
		SDL_Delay(20);
		if(evento.type == SDL_QUIT){
			juegoEnMarcha= false;
		} 

		//magia
		if (m_keys[SDL_SCANCODE_C]){
			SDL_SetWindowSize(win,300,100);
			float resizeX = 300.0f/640.0f;
			float resizeY = 100.0f/480.0f;
			SDL_RenderSetScale(ren,resizeX,resizeY);
		}
	}

	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
return 0;
}