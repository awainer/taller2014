#include "VistaPoligono.h"
#include <iostream>



VistaPoligono::VistaPoligono(SDL_Renderer* gRenderer, Poligono * poligono,DatosPantalla* datos)
{
	m_renderer = gRenderer;
	this->poligono = poligono;
	this->n_vertices = poligono->getVertexCount();
	m_vx = new Sint16[n_vertices];
	m_vy = new Sint16[n_vertices];
	this->m_datos = datos;

	this->d_poligono = NULL;
	//Hard code de texturas
	x=0;
	y=0;
	std::string path;
	if ( n_vertices == 4){
		path = "imagenes/floor.jpg";
	}else{
		path = "imagenes/texture-07.jpg";
	}
	m_loadedSurface = IMG_Load( path.c_str()  );
	if( m_loadedSurface == NULL )
	{
		std::string msg =	"No se pudo cargar la imagen de fondo: " + path + " IMG_image Error: " + IMG_GetError() ;
		log(msg, ERROR);	
	}
	else
	{
		m_texture = NULL;
        m_texture = SDL_CreateTextureFromSurface( m_renderer, m_loadedSurface );
		if( m_texture == NULL )
		{
			std::string msg =	"No se pudo crear la textura desde " + path + " SDL Error: " + SDL_GetError() ;
			log(msg, ERROR);
		}else{
			std::string msg ="Se cargo correctamente textura con fondo: " + path ;
			log(msg, ERROR);
		}
		
	
		//SDL_FreeSurface( loadedSurface );
	}

}

VistaPoligono::VistaPoligono(SDL_Renderer* gRenderer, DatosPoligono * poligono,DatosPantalla* datos)
{
	m_renderer = gRenderer;
	this->poligono = NULL;
	this->d_poligono = poligono;
	this->n_vertices = poligono->getVertexCount();
	m_vx = new Sint16[n_vertices];
	m_vy = new Sint16[n_vertices];
	this->m_datos = datos;
	m_loadedSurface = NULL;
	m_texture = NULL;

}

void VistaPoligono::render(){
	if(poligono !=NULL){
	this->transformarSint16(this->poligono->getVertices());
	//x++;
	//y++;	
	texturedPolygon(m_texture,m_renderer, m_vx , m_vy ,n_vertices,m_loadedSurface, x,  y);
	//filledPolygonRGBA(m_renderer, m_vx , m_vy ,n_vertices,this->poligono->color.r,this->poligono->color.g,this->poligono->color.b,this->poligono->color.a);
	}
	if(d_poligono !=NULL){
		this->transformarSint16(this->d_poligono->getVertices());
		filledPolygonRGBA(m_renderer, m_vx , m_vy ,n_vertices,250,0,0,255);
	}
}

VistaPoligono::~VistaPoligono(void)
{
	delete[] m_vx;
	delete[] m_vy;
	if(m_loadedSurface != NULL)
		SDL_FreeSurface( m_loadedSurface );
	if( m_texture != NULL)
		SDL_DestroyTexture( m_texture );
}
void VistaPoligono::transformarSint16(std::vector<CoordenadasR2> vertices){

		for(int i = 0; i<n_vertices; i++){
			
			m_vx[i]=Sint16(vertices[i].x *  this->m_datos->getXratio());
			m_vy[i]=Sint16(this->m_datos->getAltoPixel() -(vertices[i].y *  this->m_datos->getYratio()));

		} 
		
}
