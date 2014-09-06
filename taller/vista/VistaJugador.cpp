#include "VistaJugador.h"


VistaJugador::VistaJugador(SDL_Renderer* renderer,Jugador* jugador,DatosPantalla* datos)
{
	this->m_jugador= jugador;
	this->m_renderer = renderer;
	m_vx = new Sint16[4];
	m_vy = new Sint16[4];
	this->m_datos = datos;
}

void VistaJugador::render(){
	this->transformarSint16(this->m_jugador->getVertices());
	filledPolygonRGBA(m_renderer, m_vx , m_vy ,4,0,100,255,255);
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