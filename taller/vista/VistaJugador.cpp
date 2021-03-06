#include "VistaJugador.h"
#include <iostream>

VistaJugador::VistaJugador(SDL_Renderer* renderer,Jugador* jugador,DatosPantalla* datos)
{
	this->m_jugador= jugador;
	this->m_renderer = renderer;
	this->m_datos = datos;
	this->m_sprite = NULL;
	this->agregarSprite("imagenes/sprite.png");
	paso=0;
	delay=0;
	m_vx = new Sint16[4];
	m_vy = new Sint16[4];

	this->size = jugador->getSize(); //ancho,alto
	this->d_jugador = NULL;

}
VistaJugador::VistaJugador(SDL_Renderer* renderer,DatosJugador* jugador,DatosPantalla* datos){
	this->m_jugador= NULL;
	this->m_renderer = renderer;
	this->m_datos = datos;
	this->m_sprite = NULL;
	this->agregarSprite("imagenes/sprite.png");
	paso=0;
	delay=0;
	m_vx = new Sint16[4];
	m_vy = new Sint16[4];

	this->size = jugador->getSize(); //ancho,alto
	this->d_jugador = jugador;
}
void VistaJugador::render(){
	//CoordenadasR2 size = m_jugador->getSize(); //ancho,alto
	CoordenadasR2 pos;//x,y
	int direccion;
	int x,y,w,h;
	//Descomentar para ver recuadro real del personaje
	//this->transformarSint16(m_jugador->getVertices());
	//filledPolygonRGBA(m_renderer, m_vx , m_vy ,4,250,0,0,255);
	if(this->m_jugador != NULL){
		pos = m_jugador->getPosicion();
		direccion = m_jugador->getDireccion();	
	}
	if(this->d_jugador != NULL){
		pos = d_jugador->getPosicion();
		direccion = d_jugador->getDireccion();	
	}
	x = int(( pos.x - ( size.x * 0.8 ) ) * this->m_datos->getXratio());
	y = int(this->m_datos->getAltoPixel() - ( (pos.y + ( size.y * 0.5 ) ) * this->m_datos->getYratio()));
	w = int(1.75* size.x * this->m_datos->getXratio());
	h = int(1.05*size.y * this->m_datos->getYratio());
	this->cargarSprites(direccion, x, y, w, h);
	if ((direccion == IZQUIERDA) || (direccion == ARRIBA_IZQUIERDA) ){
		m_dirAnterior = IZQUIERDA;
	}else if ((direccion == DERECHA) || (direccion == ARRIBA_DERECHA) ){
		m_dirAnterior = DERECHA;
	}

}

void VistaJugador::dibujar(int numSprite,int x, int y, int w, int h){
	SDL_Rect* renderQuad = new SDL_Rect;
	renderQuad->x = x;
	renderQuad->y = y;
	renderQuad->h = h;
	renderQuad->w = w;
	SDL_RenderCopy( this->m_renderer, this->m_sprite, &m_spriteClips[numSprite], renderQuad );
	if( delay == 5){
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
	delete[] m_vx;
	delete[] m_vy;
}

void VistaJugador::agregarSprite(std::string path){
	
	//Levanto los sprites
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		std::string msg =	"No se pudo levantar la imagen de sprite " + path + " SDL_image Error: " + IMG_GetError() ;
		log(msg, LOG_ERROR);
	}
	else
	{
		// Asigno el color clave de la imagen
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 186, 254, 202 ) );

		//Creo textura a partir de la surface
        m_sprite = SDL_CreateTextureFromSurface( m_renderer, loadedSurface );
		if( m_sprite == NULL )
		{
			std::string msg =	"No se pudo crear la textura desde " + path + " SDL Error: " + SDL_GetError() ;
			log(msg, LOG_ERROR);
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

bool VistaJugador::spriteOk(){
	if(m_sprite == NULL){
		return false;
	}else{
		return true;
	}
}

void VistaJugador::transformarSint16(std::vector<CoordenadasR2> vertices){

		for(int i = 0; i<4; i++){
			
			m_vx[i]=Sint16(vertices[i].x *  this->m_datos->getXratio());
			m_vy[i]=Sint16(this->m_datos->getAltoPixel() -(vertices[i].y *  this->m_datos->getYratio()));

		} 
		
}