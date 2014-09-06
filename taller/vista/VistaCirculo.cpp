#include "VistaCirculo.h"
#include <math.h>
#include <iostream>
#include <stdlib.h> 

#define PI 3.14159265

VistaCirculo::VistaCirculo(SDL_Renderer* gRenderer , Pelota * pelota, DatosPantalla* datos)
{
	this->pelota = pelota;
	m_renderer = gRenderer;
	this->m_datos = datos;

}

void VistaCirculo::render() {
	
	int m_x = this->pelota->getCentro().x * this->m_datos->getXratio();
	int m_y = this->m_datos->getAltoPixel() - (this->pelota->getCentro().y * this->m_datos->getYratio());
	//this->m_radio =(Sint16) this->pelota->getRadio();
	Sint16 rx = (Sint16) (this->pelota->getRadio() * this->m_datos->getXratio());
	Sint16 ry = (Sint16) (this->pelota->getRadio() * this->m_datos->getYratio());

	Uint8 r = this->pelota->color.r;   
	Uint8 g = this->pelota->color.g;   
	Uint8 b = this->pelota->color.b;   
	Uint8 a = this->pelota->color.a; 
	int ret = filledEllipseRGBA(m_renderer,m_x,m_y,rx,ry,r,g,b,a); 

	Sint16 refx = (Sint16) (this->pelota->getPuntoReferencia().x * this->m_datos->getXratio());
	Sint16 refy = (Sint16)(this->m_datos->getAltoPixel() - (this->pelota->getPuntoReferencia().y * this->m_datos->getYratio()));
	pixelRGBA(m_renderer,refx,refy,255-r,255-g,255-b,a);
	pixelRGBA(m_renderer,refx+1,refy,255-r,255-g,255-b,a);
	pixelRGBA(m_renderer,refx,refy+1,255-r,255-g,255-b,a);
	//filledCircleRGBA(m_renderer,refx,refy,m_radio/4, 255 - r, 255 - g, 255 - b, a); // color negativo al original

}

VistaCirculo::~VistaCirculo(void)
{
}
