#include "VistaRectangulo.h"


VistaRectangulo::VistaRectangulo(int alto, int ancho, SDL_Renderer* gRenderer )
{
	m_alto = alto;
	m_ancho = ancho;
	m_renderer = gRenderer;
//	m_textura = SDL_CreateTexture(gRenderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_STREAMING,m_ancho,m_alto);
	
}

void VistaRectangulo::render(int x,int y){
	m_x = x;
	m_y = y;
	SDL_Rect rectangulo;
	rectangulo.h = m_alto;
	rectangulo.w = m_ancho;
	rectangulo.x = m_x;
	rectangulo.y = m_y;
	
	// color rojo
	SDL_SetRenderDrawColor( m_renderer, 0xFF, 0x00, 0x00, 0xFF );		
	SDL_RenderFillRect( m_renderer, &rectangulo );
//	SDL_RenderCopy( m_renderer, m_textura, NULL, &rectangulo );


}

VistaRectangulo::~VistaRectangulo(void)
{
	//SDL_DestroyTexture(this->m_textura);
}
