#include "VistaCirculo.h"
#include <math.h>

#define PI 3.14159265

VistaCirculo::VistaCirculo(Pelota * pelota, SDL_Renderer* gRenderer )
{
	this->pelota = pelota;
	m_renderer = gRenderer;
}

void VistaCirculo::render(){
	int m_x = this->pelota->getCentro().x;
	int m_y = this->pelota->getCentro().y;
	int rotacion = 0;
	int escala  = 1;
	//int ret = filledCircleColor(m_renderer, m_x, m_y, m_radio, );
	int ret = filledCircleRGBA(m_renderer,m_x,m_y,m_radio,255,255,0,255,0);
	filledCircleRGBA(m_renderer,m_x,m_y,m_radio,255,255,0,255,0);
	filledCircleRGBA(m_renderer,this->pelota->getPuntoReferencia().x,this->pelota->getPuntoReferencia().y,m_radio,255,255,0,255,0);
	double res_cos, res_sin;
    res_cos = cos ( rotacion * PI / 180.0 );
    res_sin = sin ( rotacion * PI / 180.0 );
    Uint32 colorTemp = 0xFF000FF0; // deberia ser un color mas oscuro que el propio de la figura
    int a_x, a_y;
    a_x = m_radio * res_sin * escala;
    a_y = m_radio * res_cos * escala;
    int ret2 = lineColor(m_renderer, m_x, m_y, m_x + a_x, m_y - a_y, colorTemp);
}

VistaCirculo::~VistaCirculo(void)
{
}
