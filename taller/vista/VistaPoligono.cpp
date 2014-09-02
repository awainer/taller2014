#include "VistaPoligono.h"



VistaPoligono::VistaPoligono(SDL_Renderer* gRenderer, int vertices)
{
	m_renderer = gRenderer;
	n_vertices = vertices;
	m_vx = new Sint16[n_vertices];
	m_vy = new Sint16[n_vertices];
}
void VistaPoligono::render(CoordenadasR2* vectorVertices[]){
	
	this->transformarSint16(vectorVertices);
	filledPolygonRGBA(m_renderer, m_vx , m_vy ,n_vertices,255,255,0,255);// color amarillo
}

VistaPoligono::~VistaPoligono(void)
{
	delete[] m_vx;
	delete[] m_vy;
}
