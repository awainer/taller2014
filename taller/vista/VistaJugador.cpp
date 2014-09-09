#include "VistaJugador.h"
#include <iostream>

VistaJugador::VistaJugador(SDL_Renderer* renderer,Jugador* jugador,DatosPantalla* datos)
{
	this->m_jugador= jugador;
	this->m_renderer = renderer;
	m_vx = new Sint16[4];
	m_vy = new Sint16[4];
	this->m_datos = datos;
	paso=0;
}

void VistaJugador::render(){
	CoordenadasR2 size = m_jugador->getSize(); //ancho,alto
	CoordenadasR2 pos = m_jugador->getPosicion();//x,y
	this->agregarSprite("imagenes/sprite.png");
	int x,y,w,h;
	x = ( pos.x - ( size.x / 2 ) ) * this->m_datos->getXratio();
	y = this->m_datos->getAltoPixel() - ( (pos.y + ( size.y / 2 ) ) * this->m_datos->getYratio());
	w = size.x * this->m_datos->getXratio();
	h = size.y * this->m_datos->getYratio();
	//SDL_Rect* renderQuad = new SDL_Rect;
	//renderQuad->x = x;
	//renderQuad->y = y;
	//renderQuad->h = h;
	//renderQuad->w = w;
	this->cargarSprites(m_jugador->getDireccion(), x, y, w, h); // se podrian cargar todas antes, teniendo un SDL_rect para cada posicion
	if ((this->m_jugador->getDireccion() == IZQUIERDA) || (this->m_jugador->getDireccion() == ARRIBA_IZQUIERDA) ){
		m_dirAnterior = IZQUIERDA;
	}else if ((this->m_jugador->getDireccion() == DERECHA) || (this->m_jugador->getDireccion() == ARRIBA_IZQUIERDA) ){
		m_dirAnterior = DERECHA;
	}
	//delete renderQuad;

}

void VistaJugador::cargarSprites(int dire, int x, int y, int w, int h){
	int i,j;
	SDL_Rect renderQuad = { x, y, w, h };
	switch(dire) 
	{
	case IZQUIERDA : 
		m_spriteClips[ 0 ].x =  32;
		m_spriteClips[ 0 ].y =  58;
		m_spriteClips[ 0 ].w =  21;
		m_spriteClips[ 0 ].h =  24;
		
		m_spriteClips[ 1 ].x =  56;
		m_spriteClips[ 1 ].y =  58;
		m_spriteClips[ 1 ].w =  21;
		m_spriteClips[ 1 ].h =  24;

		m_spriteClips[ 2 ].x =  87;
		m_spriteClips[ 2 ].y =  58;
		m_spriteClips[ 2 ].w =  21;
		m_spriteClips[ 2 ].h =  24;
		if(paso>2){
			paso=0;
		}
		if(paso==0){ 
			SDL_RenderCopy( this->m_renderer, this->m_sprite, &m_spriteClips[0], &renderQuad );
			std::cout << "paso " << paso << std::endl;
			paso++;
			
		} else if(paso==1){ 
			SDL_RenderCopy( this->m_renderer, this->m_sprite, &m_spriteClips[1], &renderQuad );
			std::cout << "paso " << paso << std::endl;
			paso++;
		}else if(paso==2){ 
			SDL_RenderCopy( this->m_renderer, this->m_sprite, &m_spriteClips[2], &renderQuad );
			std::cout << "paso " << paso << std::endl;
			paso=0;
		}
		/*for(i=0;i<3;i++){
			//for (j=0;j<4;j++){
				//SDL_SetRenderDrawColor( this->m_renderer, 0xFF, 0xFF, 0xFF, 0xFF );
				//SDL_RenderClear( this->m_renderer );
				SDL_RenderCopy( this->m_renderer, this->m_sprite, &m_spriteClips[1+i], &renderQuad );
				SDL_RenderPresent(this->m_renderer);
				
			//}
		}*/
		break;
	case DERECHA :
		m_spriteClips[ 0 ].x =  56; 
		m_spriteClips[ 0 ].y =  82;
		m_spriteClips[ 0 ].w =  21;
		m_spriteClips[ 0 ].h =  24;
		
		m_spriteClips[ 1 ].x =  32; 
		m_spriteClips[ 1 ].y =  82;
		m_spriteClips[ 1 ].w =  21;
		m_spriteClips[ 1 ].h =  24;

		m_spriteClips[ 2 ].x =   0; 
		m_spriteClips[ 2 ].y =  82;
		m_spriteClips[ 2 ].w =  21;
		m_spriteClips[ 2 ].h =  24;
		if(paso>2){
			paso=0;
		}

		if(paso==0){ 
			SDL_RenderCopy( this->m_renderer, this->m_sprite, &m_spriteClips[0], &renderQuad );
			std::cout << "paso " << paso << std::endl;
			paso++;
			
		} else if(paso==1){ 
			SDL_RenderCopy( this->m_renderer, this->m_sprite, &m_spriteClips[1], &renderQuad );
			std::cout << "paso " << paso << std::endl;
			paso++;
		}else if(paso==2){ 
			SDL_RenderCopy( this->m_renderer, this->m_sprite, &m_spriteClips[2], &renderQuad );
			std::cout << "paso " << paso << std::endl;
			paso=0;
		}
		/*for(i=0;i<3;i++){
			//for (j=0;j<4;j++){
				//SDL_SetRenderDrawColor( this->m_renderer, 0xFF, 0xFF, 0xFF, 0xFF );
				//SDL_RenderClear( this->m_renderer );
				SDL_RenderCopy( this->m_renderer, this->m_sprite, &m_spriteClips[i], &renderQuad );
				SDL_RenderPresent(this->m_renderer);
			//}
		}*/
		break;
	case ARRIBA_IZQUIERDA:
		m_spriteClips[ 0 ].x =   0;
		m_spriteClips[ 0 ].y =   0;
		m_spriteClips[ 0 ].w =  23;
		m_spriteClips[ 0 ].h =  29;

		m_spriteClips[ 1 ].x =  32;
		m_spriteClips[ 1 ].y =   0;
		m_spriteClips[ 1 ].w =  23;
		m_spriteClips[ 1 ].h =  29;
		
		m_spriteClips[ 2 ].x =  64;
		m_spriteClips[ 2 ].y =   0;
		m_spriteClips[ 2 ].w =  23;
		m_spriteClips[ 2 ].h =  29;

		m_spriteClips[ 3 ].x =  96;
		m_spriteClips[ 3 ].y =   0;
		m_spriteClips[ 3 ].w =  23;
		m_spriteClips[ 3 ].h =  29;
		
		m_spriteClips[ 4 ].x = 128;
		m_spriteClips[ 4 ].y =   0;
		m_spriteClips[ 4 ].w =  23;
		m_spriteClips[ 4 ].h =  29;
		
		if(paso==0){ 
			SDL_RenderCopy( this->m_renderer, this->m_sprite, &m_spriteClips[0], &renderQuad );
			std::cout << "paso " << paso << std::endl;
			paso++;
			
		} else if(paso==1){ 
			SDL_RenderCopy( this->m_renderer, this->m_sprite, &m_spriteClips[1], &renderQuad );
			std::cout << "paso " << paso << std::endl;
			paso++;
		}else if(paso==2){ 
			SDL_RenderCopy( this->m_renderer, this->m_sprite, &m_spriteClips[2], &renderQuad );
			std::cout << "paso " << paso << std::endl;
			paso++;
		}else if(paso==3){ 
			SDL_RenderCopy( this->m_renderer, this->m_sprite, &m_spriteClips[3], &renderQuad );
			std::cout << "paso " << paso << std::endl;
			paso++;
		}else if(paso==4){ 
			SDL_RenderCopy( this->m_renderer, this->m_sprite, &m_spriteClips[4], &renderQuad );
			std::cout << "paso " << paso << std::endl;
			paso=0;
		}
		/*for(i=0;i<5;i++){
			for (j=0;j<4;j++){
				SDL_RenderCopy( this->m_renderer, this->m_sprite, &m_spriteClips[i], &renderQuad );
				SDL_RenderPresent(this->m_renderer);
			}
		}*/
		break;

	case ARRIBA_DERECHA:
		m_spriteClips[ 0 ].x = 128;
		m_spriteClips[ 0 ].y =   0;
		m_spriteClips[ 0 ].w =  23;
		m_spriteClips[ 0 ].h =  29;

		m_spriteClips[ 1 ].x =  96;
		m_spriteClips[ 1 ].y =   0;
		m_spriteClips[ 1 ].w =  23;
		m_spriteClips[ 1 ].h =  29;
		
		m_spriteClips[ 2 ].x =  64;
		m_spriteClips[ 2 ].y =   0;
		m_spriteClips[ 2 ].w =  23;
		m_spriteClips[ 2 ].h =  29;

		m_spriteClips[ 3 ].x =  32;
		m_spriteClips[ 3 ].y =   0;
		m_spriteClips[ 3 ].w =  23;
		m_spriteClips[ 3 ].h =  29;
		
		m_spriteClips[ 4 ].x =   0;
		m_spriteClips[ 4 ].y =   0;
		m_spriteClips[ 4 ].w =  23;
		m_spriteClips[ 4 ].h =  29;
		
		if(paso==0){ 
			SDL_RenderCopy( this->m_renderer, this->m_sprite, &m_spriteClips[0], &renderQuad );
			std::cout << "paso " << paso << std::endl;
			paso++;
			
		} else if(paso==1){ 
			SDL_RenderCopy( this->m_renderer, this->m_sprite, &m_spriteClips[1], &renderQuad );
			std::cout << "paso " << paso << std::endl;
			paso++;
		}else if(paso==2){ 
			SDL_RenderCopy( this->m_renderer, this->m_sprite, &m_spriteClips[2], &renderQuad );
			std::cout << "paso " << paso << std::endl;
			paso++;
		}else if(paso==3){ 
			SDL_RenderCopy( this->m_renderer, this->m_sprite, &m_spriteClips[3], &renderQuad );
			std::cout << "paso " << paso << std::endl;
			paso++;
		}else if(paso==4){ 
			SDL_RenderCopy( this->m_renderer, this->m_sprite, &m_spriteClips[4], &renderQuad );
			std::cout << "paso " << paso << std::endl;
			paso=0;
		}
		/*for(i=0;i<5;i++){
			for (j=0;j<4;j++){
				SDL_RenderCopy( this->m_renderer, this->m_sprite, &m_spriteClips[i], &renderQuad );
				SDL_RenderPresent(this->m_renderer);
			}
		}*/
		break;
		
	case ARRIBA:
		if (m_dirAnterior = IZQUIERDA) {
		m_spriteClips[ 0 ].x =   0;
		m_spriteClips[ 0 ].y =   0;
		m_spriteClips[ 0 ].w =  23;
		m_spriteClips[ 0 ].h =  29;

		m_spriteClips[ 1 ].x =  32;
		m_spriteClips[ 1 ].y =   0;
		m_spriteClips[ 1 ].w =  23;
		m_spriteClips[ 1 ].h =  29;
		
		m_spriteClips[ 2 ].x =  64;
		m_spriteClips[ 2 ].y =   0;
		m_spriteClips[ 2 ].w =  23;
		m_spriteClips[ 2 ].h =  29;

		m_spriteClips[ 3 ].x =  96;
		m_spriteClips[ 3 ].y =   0;
		m_spriteClips[ 3 ].w =  23;
		m_spriteClips[ 3 ].h =  29;
		
		m_spriteClips[ 4 ].x = 128;
		m_spriteClips[ 4 ].y =   0;
		m_spriteClips[ 4 ].w =  23;
		m_spriteClips[ 4 ].h =  29;
		}
		else{
		m_spriteClips[ 0 ].x = 128;
		m_spriteClips[ 0 ].y =   0;
		m_spriteClips[ 0 ].w =  23;
		m_spriteClips[ 0 ].h =  29;

		m_spriteClips[ 1 ].x =  96;
		m_spriteClips[ 1 ].y =   0;
		m_spriteClips[ 1 ].w =  23;
		m_spriteClips[ 1 ].h =  29;
		
		m_spriteClips[ 2 ].x =  64;
		m_spriteClips[ 2 ].y =   0;
		m_spriteClips[ 2 ].w =  23;
		m_spriteClips[ 2 ].h =  29;

		m_spriteClips[ 3 ].x =  32;
		m_spriteClips[ 3 ].y =   0;
		m_spriteClips[ 3 ].w =  23;
		m_spriteClips[ 3 ].h =  29;
		
		m_spriteClips[ 4 ].x =   0;
		m_spriteClips[ 4 ].y =   0;
		m_spriteClips[ 4 ].w =  23;
		m_spriteClips[ 4 ].h =  29;
		}
		if(paso==0){ 
			SDL_RenderCopy( this->m_renderer, this->m_sprite, &m_spriteClips[0], &renderQuad );
			std::cout << "paso " << paso << std::endl;
			paso++;
			
		} else if(paso==1){ 
			SDL_RenderCopy( this->m_renderer, this->m_sprite, &m_spriteClips[1], &renderQuad );
			std::cout << "paso " << paso << std::endl;
			paso++;
		}else if(paso==2){ 
			SDL_RenderCopy( this->m_renderer, this->m_sprite, &m_spriteClips[2], &renderQuad );
			std::cout << "paso " << paso << std::endl;
			paso++;
		}else if(paso==3){ 
			SDL_RenderCopy( this->m_renderer, this->m_sprite, &m_spriteClips[3], &renderQuad );
			std::cout << "paso " << paso << std::endl;
			paso++;
		}else if(paso==4){ 
			SDL_RenderCopy( this->m_renderer, this->m_sprite, &m_spriteClips[4], &renderQuad );
			std::cout << "paso " << paso << std::endl;
			paso=0;
		}
		/*for(i=0;i<5;i++){
			for (j=0;j<4;j++){
				SDL_RenderCopy( this->m_renderer, this->m_sprite, &m_spriteClips[i], &renderQuad );
				SDL_RenderPresent(this->m_renderer);
			}
		}*/
		break;
	case ESTATICO : 
		if (m_dirAnterior == IZQUIERDA) {
			m_spriteClips[ 0 ].x =   0;
			m_spriteClips[ 0 ].y =  58;
			m_spriteClips[ 0 ].w =  21;
			m_spriteClips[ 0 ].h =  24;
		} else {
			m_spriteClips[ 0 ].x =  88; 
			m_spriteClips[ 0 ].y =  82;
			m_spriteClips[ 0 ].w =  21;
			m_spriteClips[ 0 ].h =  24;
		}
		SDL_RenderCopy( this->m_renderer, this->m_sprite, &m_spriteClips[0], &renderQuad );
		//SDL_RenderPresent(this->m_renderer);
		break;
	}

}


VistaJugador::~VistaJugador(void)
{
	delete[] m_vx;
	delete[] m_vy;
}

void VistaJugador::transformarSint16(std::vector<CoordenadasR2> vertices){

		for(int i = 0; i<4; i++){
			m_vx[i]=vertices[i].x *  this->m_datos->getXratio();
			m_vy[i]= this->m_datos->getAltoPixel() -(vertices[i].y *  this->m_datos->getYratio());
		} 
		
}

void VistaJugador::agregarSprite(std::string path){
	
	//if(m_sprite != NULL){
	//	SDL_DestroyTexture( m_sprite );
	//}
	//Levanto los sprites
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "No se pudo levantar la imagen de sprite %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		// Asigno el color clave de la imagen
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 186, 254, 202 ) );

		//Creo textura a partir de la surface
        m_sprite = SDL_CreateTextureFromSurface( m_renderer, loadedSurface );
		if( m_sprite == NULL )
		{
			printf( "No se pudo crear la textura desde %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Me guardo la dimension de la imagen
			ms_ancho = loadedSurface->w;
			ms_alto = loadedSurface->h;
		}

		//Elimino la surface temporal
		SDL_FreeSurface( loadedSurface );
	}


}