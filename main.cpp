
#include <SDL.h>
#include "taller\vista\VistaRectangulo.h"
#include "taller\vista\VistaPoligono.h"
#include "taller\model\CoordenadasR2.h"
//#include <vld.h>

void pruebaPoligono_rectangulo(){

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Event evento;
	bool juegoEnMarcha = true;
	//creo la pantalla
	SDL_Window *win = SDL_CreateWindow("Prueba poligono, rectangulo", 100, 100, 640, 480, SDL_WINDOW_SHOWN);	
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	

	VistaRectangulo* r = new VistaRectangulo(100,50,ren);
	VistaRectangulo* r2 = new VistaRectangulo(80,50,ren);
	VistaRectangulo r3 = VistaRectangulo(40,640,ren);
	VistaPoligono poligono = VistaPoligono(ren,6);
	CoordenadasR2* vector[6];
	vector[0] = new  CoordenadasR2(100,200);
	vector[1] = new  CoordenadasR2(150,250);
	vector[2] = new  CoordenadasR2(250,250);
	vector[3] = new  CoordenadasR2(300,200);
	vector[4] = new  CoordenadasR2(250,150);
	vector[5] = new  CoordenadasR2(150,150);

	 
	//int vx[6]={200-100,250-100,350-100,400-100,350-100,250-100};
	//int vy[6]={400-200,450-200,450-200,400-200,350-200,350-200};
	
	int x,y;
	x=0;
	y=0;
	
	while( juegoEnMarcha ){
		x++;
		y++;
		
		for(int j = 0; j<6; j++){
		vector[j]->x= vector[j]->x+1;
		vector[j]->y= vector[j]->y+1;
		}
		//Clear screen
		SDL_SetRenderDrawColor( ren, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( ren );

		
		r->render(x,y);
		r2->render(480,200);
		r3.render(0,430);
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
	delete r ;
	delete r2 ;
	for (int i=0; i<6; i++)
		delete vector[i];

}
int main(int argc, char * argv[]){
	//prueba commit Carlos Delvalle
	pruebaPoligono_rectangulo();
	//prueba commit Gustavo Morinigo
	return 0;
}