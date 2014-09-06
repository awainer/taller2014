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
}
void VistaPoligono::render(){
	
	this->transformarSint16(this->poligono->getVertices());
	filledPolygonRGBA(m_renderer, m_vx , m_vy ,n_vertices,this->poligono->color.r,this->poligono->color.g,this->poligono->color.b,this->poligono->color.a);
}

VistaPoligono::~VistaPoligono(void)
{
	delete[] m_vx;
	delete[] m_vy;
}
void VistaPoligono::transformarSint16(std::vector<CoordenadasR2> vertices){

		for(int i = 0; i<n_vertices; i++){
			m_vx[i]=vertices[i].x *  this->m_datos->getXratio();
			m_vy[i]= this->m_datos->getAltoPixel() -(vertices[i].y *  this->m_datos->getYratio());
		} 
		
}