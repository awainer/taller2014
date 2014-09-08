#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include "..\vista\VistaPoligono.h"
#include "..\model\CoordenadasR2.h"
#include "..\model\Escenario.h"
#include "..\model\Paralelogramo.h"
#include "..\model\Color.h"


SDL_Texture* loadTexture( std::string path );

//SDL_Renderer *ren2 = NULL;


int  prueba_paralelogramo(){
	Color  rojo = Color(255,0,0);
	Color  azul = Color(0,0,100);
	Color  verde = Color(0,255,0);
	Color violeta = Color(100,100,0);
	int r = SDL_Init(SDL_INIT_EVERYTHING);
	printf("sdl init %d \n",r);
	SDL_Event evento;
	SDL_Scancode sc;
	bool juegoEnMarcha = true;
	//creo la pantalla
	SDL_Window *win = SDL_CreateWindow("Prueba Paralelogramo", 100, 100, 640, 480, SDL_WINDOW_SHOWN);	
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_SOFTWARE);
	Escenario * esc = new Escenario(6.4, 4.8,CoordenadasR2(0,-10),std::string("pathfondo"),NULL);

	// cambio de escala segun Box2D a SDL, necesaria para dibujar en el pixel correcto
	//float xratio = 640 / 6.4f;
	//float yratio = 480 / 4.8f;
	DatosPantalla datos = DatosPantalla(640,480,6.4f,4.8f);

	esc->agregarParalelogramo(CoordenadasR2(2,2),1,1,1,rojo,0,false,2);

	VistaFigura* poligono = new VistaPoligono(ren,(Poligono*)esc->getPoligonos()[0],&datos);
	//Clear screen		
		SDL_SetRenderDrawColor( ren, 255, 255, 255, 255 );
		SDL_RenderClear( ren );
		
		//Dibujo figuras
		poligono->render();
		SDL_RenderPresent(ren);
	
	while( juegoEnMarcha ){
			
		

		
		SDL_PollEvent( &evento);
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
				resizePantalla(win,ren,300,100);
			// Aca verifique que si se pone escala (1,1) en el renderder vuelve al estado original de la pantalla si presiono D.
			if( sc == SDL_SCANCODE_D)
				SDL_SetWindowSize(win,640,480);
			
			break;

		}
	}

	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
	delete poligono;
	return 0;
}
