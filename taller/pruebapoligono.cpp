#pragma once
#ifdef WIN32
#pragma comment(lib, "SDL2.lib")
#endif 
#include <SDL.h>
#include "..\vista\VistaRectangulo.h"
#include "..\vista\VistaPoligono.h"
#include "..\model\CoordenadasR2.h"
#include "..\model\Escenario.h"
#include "..\model\Poligono.h"



int  main(){

SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Event evento;
	bool juegoEnMarcha = true;
	//creo la pantalla
	SDL_Window *win = SDL_CreateWindow("Prueba poligono, rectangulo", 100, 100, 640, 480, SDL_WINDOW_SHOWN);	
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	Escenario * esc = new Escenario(640, 480,NULL);

	esc->agregarPoligono(CoordenadasR2(10,10),30,6);

	VistaPoligono poligono = VistaPoligono(ren,6);


	 
	//int vx[6]={200-100,250-100,350-100,400-100,350-100,250-100};
	//int vy[6]={400-200,450-200,450-200,400-200,350-200,350-200};
	
	int x,y;
	x=0;
	y=0;
	std::vector<CoordenadasR2> vector = esc->getPoligonos()[0]->getVertices();
	while( juegoEnMarcha ){
		//Clear screen
		SDL_SetRenderDrawColor( ren, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( ren );

		poligono.render(vector);
		
		SDL_RenderPresent(ren);
		SDL_PollEvent( &evento);
		if(evento.type == SDL_QUIT){
			juegoEnMarcha= false;
		} 
	}

	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
return 0;
}