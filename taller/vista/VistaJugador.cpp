#include "VistaJugador.h"
#include <iostream>

VistaJugador::VistaJugador(SDL_Renderer* renderer,Jugador* jugador,DatosPantalla* datos)
{
	this->m_jugador= jugador;
	this->m_renderer = renderer;
	this->m_datos = datos;
	this->agregarSprite("imagenes/sprite.png");
	paso=0;
	delay=0;
}

void VistaJugador::render(){
	CoordenadasR2 size = m_jugador->getSize(); //ancho,alto
	CoordenadasR2 pos = m_jugador->getPosicion();//x,y
	int x,y,w,h;
	x = ( pos.x - ( size.x / 2 ) ) * this->m_datos->getXratio();
	y = this->m_datos->getAltoPixel() - ( (pos.y + ( size.y / 2 ) ) * this->m_datos->getYratio());
	w = size.x * this->m_datos->getXratio();
	h = size.y * this->m_datos->getYratio();
	this->cargarSprites(m_jugador->getDireccion(), x, y, w, h); // se podrian cargar todas antes, teniendo un SDL_rect para cada posicion
	if ((this->m_jugador->getDireccion() == IZQUIERDA) || (this->m_jugador->getDireccion() == ARRIBA_IZQUIERDA) ){
		m_dirAnterior = IZQUIERDA;
		//std::cout << " ultimo izquierda" << std::endl;
	}else if ((this->m_jugador->getDireccion() == DERECHA) || (this->m_jugador->getDireccion() == ARRIBA_DERECHA) ){
		m_dirAnterior = DERECHA;
		//std::cout << " ultimo derecha" << std::endl;
	}

}

void VistaJugador::dibujar(int numSprite,int x, int y, int w, int h){
	SDL_Rect* renderQuad = new SDL_Rect;
	renderQuad->x = x;
	renderQuad->y = y;
	renderQuad->h = h;
	renderQuad->w = w;
	SDL_RenderCopy( this->m_renderer, this->m_sprite, &m_spriteClips[numSprite], renderQuad );
	if( delay == 3){
		paso++;
		delay = 0;
	}else{ delay++;}
	delete renderQuad;
}

void VistaJugador::cargarSprites(int dire, int x, int y, int w, int h){
	
	switch(dire) 
	{
	case IZQUIERDA : 

		if(paso>2){
			paso=0;
		}
		if(paso==0){ 
			dibujar(0, x,  y,  w, h);			
		} else if(paso==1){ 
			dibujar(1, x,  y,  w, h);
		}else if(paso==2){ 
			dibujar(2, x,  y,  w, h);
			paso = 0;
		}

		break;
	case DERECHA :
	
		if(paso>2){
			paso=0;
		}

		if(paso==0){ 
			dibujar(3, x,  y,  w, h);		
		} else if(paso==1){ 
			dibujar(4, x,  y,  w, h);
		}else if(paso==2){ 
			dibujar(5, x,  y,  w, h);
			paso = 0;
		}
		
		break;
	case ARRIBA_IZQUIERDA:
		
		if(paso==0){ 
			dibujar(6, x,  y,  w, h);	
		} else if(paso==1){ 
			dibujar(7, x,  y,  w, h);
		}else if(paso==2){ 
			dibujar(8, x,  y,  w, h);
		}else if(paso==3){ 
			dibujar(9, x,  y,  w, h);
		}else if(paso==4){ 
			dibujar(10, x,  y,  w, h);
			paso = 1;
		}
		break;

	case ARRIBA_DERECHA:
		
		if(paso==0){ 
			dibujar(11, x,  y,  w, h);	
		} else if(paso==1){ 
			dibujar(12, x,  y,  w, h);
		}else if(paso==2){ 
			dibujar(13, x,  y,  w, h);
		}else if(paso==3){ 
			dibujar(14, x,  y,  w, h);
		}else if(paso==4){ 
			dibujar(15, x,  y,  w, h);
			paso = 1;
		}
		break;
		
	case ARRIBA:
		if (m_dirAnterior == IZQUIERDA) {
			if(paso==0){ 
				dibujar(6, x,  y,  w, h);	
			} else if(paso==1){ 
				dibujar(7, x,  y,  w, h);
			}else if(paso==2){ 
				dibujar(8, x,  y,  w, h);
			}else if(paso==3){ 
				dibujar(9, x,  y,  w, h);
			}else if(paso==4){ 
				dibujar(10, x,  y,  w, h);
				paso = 1;
			}
		}
		else{
			if(paso==0){ 
				dibujar(11, x,  y,  w, h);	
			} else if(paso==1){ 
				dibujar(12, x,  y,  w, h);
			}else if(paso==2){ 
				dibujar(13, x,  y,  w, h);
			}else if(paso==3){ 
				dibujar(14, x,  y,  w, h);
			}else if(paso==4){ 
				dibujar(15, x,  y,  w, h);
				paso = 1;
			}
		}
		break;
	case ESTATICO : 
		if (m_dirAnterior == IZQUIERDA) {
			dibujar(16, x,  y,  w, h);
			//std::cout << "estatico" << std::endl;
			paso=0;
		} else {
			dibujar(17, x,  y,  w, h);
			paso=0;
		}
		break;
	}

}


VistaJugador::~VistaJugador(void)
{
	SDL_DestroyTexture(this->m_sprite);
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

		m_spriteClips[ 3 ].x =  56; 
		m_spriteClips[ 3 ].y =  82;
		m_spriteClips[ 3 ].w =  21;
		m_spriteClips[ 3 ].h =  24;
		
		m_spriteClips[ 4 ].x =  32; 
		m_spriteClips[ 4 ].y =  82;
		m_spriteClips[ 4 ].w =  21;
		m_spriteClips[ 4 ].h =  24;

		m_spriteClips[ 5 ].x =   0; 
		m_spriteClips[ 5 ].y =  82;
		m_spriteClips[ 5 ].w =  21;
		m_spriteClips[ 5 ].h =  24;

		m_spriteClips[ 6 ].x =   0;
		m_spriteClips[ 6 ].y =   0;
		m_spriteClips[ 6 ].w =  23;
		m_spriteClips[ 6 ].h =  29;

		m_spriteClips[ 7 ].x =  32;
		m_spriteClips[ 7 ].y =   0;
		m_spriteClips[ 7 ].w =  23;
		m_spriteClips[ 7 ].h =  29;
		
		m_spriteClips[ 8 ].x =  64;
		m_spriteClips[ 8 ].y =   0;
		m_spriteClips[ 8 ].w =  23;
		m_spriteClips[ 8 ].h =  29;

		m_spriteClips[ 9 ].x =  96;
		m_spriteClips[ 9 ].y =   0;
		m_spriteClips[ 9 ].w =  23;
		m_spriteClips[ 9 ].h =  29;
	
		m_spriteClips[ 10 ].x = 128;
		m_spriteClips[ 10 ].y =   0;
		m_spriteClips[ 10 ].w =  23;
		m_spriteClips[ 10 ].h =  29;

		m_spriteClips[ 11 ].x = 128;
		m_spriteClips[ 11 ].y =  29; //0
		m_spriteClips[ 11 ].w =  23;
		m_spriteClips[ 11 ].h =  29;

		m_spriteClips[ 12 ].x =  96;
		m_spriteClips[ 12 ].y =  29; //0
		m_spriteClips[ 12 ].w =  23;
		m_spriteClips[ 12 ].h =  29;
		
		m_spriteClips[ 13 ].x =  64;
		m_spriteClips[ 13 ].y =  29; //0
		m_spriteClips[ 13 ].w =  23;
		m_spriteClips[ 13 ].h =  29;

		m_spriteClips[ 14 ].x =  32;
		m_spriteClips[ 14 ].y =  29; //0
		m_spriteClips[ 14 ].w =  23;
		m_spriteClips[ 14 ].h =  29;
		
		m_spriteClips[ 15 ].x =   0;
		m_spriteClips[ 15 ].y =  29; //0
		m_spriteClips[ 15 ].w =  23;
		m_spriteClips[ 15 ].h =  29;

		m_spriteClips[ 16 ].x =   0;
		m_spriteClips[ 16 ].y =  58;
		m_spriteClips[ 16 ].w =  21;
		m_spriteClips[ 16 ].h =  24;

		m_spriteClips[ 17 ].x =  88; 
		m_spriteClips[ 17 ].y =  82;
		m_spriteClips[ 17 ].w =  21;
		m_spriteClips[ 17 ].h =  24;
	}


}