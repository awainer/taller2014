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
	bool juegoEnMarcha = true;
	//creo la pantalla
	SDL_Window *win = SDL_CreateWindow("Prueba poligono, rectangulo", 100, 100, 640, 480, SDL_WINDOW_SHOWN);	
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_SOFTWARE);
	Escenario * esc = new Escenario(640, 480,NULL);

	esc->agregarPelota(CoordenadasR2(50,50));
	esc->agregarPoligono(CoordenadasR2(100,100),30,3,0);
	esc->agregarPoligono(CoordenadasR2(200,100),30,4,45);
	esc->agregarPoligono(CoordenadasR2(300,100),30,8,90);


	VistaCirculo circulo = VistaCirculo(ren,esc->getPelotas()[0]); 
	VistaPoligono poligono = VistaPoligono(ren,(Poligono*)esc->getPoligonos()[0]);
	VistaPoligono poligono2 = VistaPoligono(ren,(Poligono*)esc->getPoligonos()[1]);
	VistaPoligono poligono3 = VistaPoligono(ren,(Poligono*)esc->getPoligonos()[2]);


	
	int x,y;
	x=0;
	y=0;
	std::vector<CoordenadasR2> vector = esc->getPoligonos()[0]->getVertices();
	while( juegoEnMarcha ){
		//Clear screen
		SDL_SetRenderDrawColor( ren, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( ren );
		circulo.render();
		poligono.render();
		poligono2.render();
		poligono3.render();
		
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