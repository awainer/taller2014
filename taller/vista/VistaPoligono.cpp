#include "VistaPoligono.h"




VistaPoligono::VistaPoligono(SDL_Renderer* gRenderer, Poligono * poligono,float xratio, float yratio)
{
	m_renderer = gRenderer;
	this->poligono = poligono;
	this->n_vertices = poligono->getVertexCount();
	m_vx = new Sint16[n_vertices];
	m_vy = new Sint16[n_vertices];
	this->xratio = xratio;
	this->yratio = xratio;
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
void VistaPoligono::transformarSint16(std::vector<CoordenadasR2> vertices){
	//Sint16 posY_SDL;
	//int ancho;
	//int alto;
	//int result = SDL_GetRendererOutputSize(m_renderer,&ancho,&alto);
		for(int i = 0; i<n_vertices; i++){
			m_vx[i]=vertices[i].x * xratio;
			
			//posY_SDL= alto - vertices[i].y;
			//m_vy[i]=posY_SDL;
			m_vy[i]=vertices[i].y * yratio;
		} 
		
}