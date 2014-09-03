#include "VistaPoligono.h"




VistaPoligono::VistaPoligono(SDL_Renderer* gRenderer, Poligono * poligono)
{
	m_renderer = gRenderer;
	this->poligono = poligono;
	this->n_vertices = poligono->getVertexCount();
	m_vx = new Sint16[n_vertices];
	m_vy = new Sint16[n_vertices];
}
void VistaPoligono::render(){
	
	this->transformarSint16(this->poligono->getVertices());
	filledPolygonRGBA(m_renderer, m_vx , m_vy ,n_vertices,255,255,0,255);// color amarillo
}

VistaPoligono::~VistaPoligono(void)
{
	delete[] m_vx;
	delete[] m_vy;
}
