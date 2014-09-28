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
	this->d_pelota = NULL;

}

VistaCirculo::VistaCirculo(SDL_Renderer* gRenderer , DatosCirculo * pelota, DatosPantalla* datos)
{
	this->pelota =NULL;
	this->d_pelota = pelota;
	m_renderer = gRenderer;
	this->m_datos = datos;

}


void VistaCirculo::render() {
	int m_x ;
	int m_y; 
	Sint16 rx;
	Sint16 ry;
	Uint8 r;   
	Uint8 g ;   
	Uint8 b;   
	Uint8 a; 
	Sint16 refx;
	Sint16 refy;
	if(pelota !=NULL){
		m_x = int(this->pelota->getCentro().x * this->m_datos->getXratio());
		m_y = int(this->m_datos->getAltoPixel() - (this->pelota->getCentro().y * this->m_datos->getYratio()));	
		rx = (Sint16) (this->pelota->getRadio() * this->m_datos->getXratio());
		ry = (Sint16) (this->pelota->getRadio() * this->m_datos->getYratio());

		r = this->pelota->color.r;   
		g = this->pelota->color.g;   
		b = this->pelota->color.b;   
		a = this->pelota->color.a; 

		int ret = filledEllipseRGBA(m_renderer,m_x,m_y,rx,ry,r,g,b,a); 

		refx = (Sint16) (this->pelota->getPuntoReferencia().x * this->m_datos->getXratio());
		refy = (Sint16)(this->m_datos->getAltoPixel() - (this->pelota->getPuntoReferencia().y * this->m_datos->getYratio()));

		pixelRGBA(m_renderer,refx,refy,255-r,255-g,255-b,a);
		pixelRGBA(m_renderer,refx+1,refy,255-r,255-g,255-b,a);
		pixelRGBA(m_renderer,refx,refy+1,255-r,255-g,255-b,a);	
	}
	if(d_pelota != NULL){
		m_x = int(this->d_pelota->getPosicion().x * this->m_datos->getXratio());
		m_y = int(this->m_datos->getAltoPixel() - (this->d_pelota->getPosicion().y * this->m_datos->getYratio()));	
		rx = (Sint16) (this->d_pelota->getRadio() * this->m_datos->getXratio());
		ry = (Sint16) (this->d_pelota->getRadio() * this->m_datos->getYratio());
		r = this->d_pelota->color.r;   
		g = this->d_pelota->color.g;   
		b = this->d_pelota->color.b;   
		a = this->d_pelota->color.a; 
		
		filledEllipseRGBA(m_renderer,m_x,m_y,rx,ry,r,g,b,a); 

		refx = (Sint16) (this->d_pelota->getPuntoReferencia().x * this->m_datos->getXratio());
		refy = (Sint16)(this->m_datos->getAltoPixel() - (this->d_pelota->getPuntoReferencia().y * this->m_datos->getYratio()));

		pixelRGBA(m_renderer,refx,refy,255-r,255-g,255-b,a);
		pixelRGBA(m_renderer,refx+1,refy,255-r,255-g,255-b,a);
		pixelRGBA(m_renderer,refx,refy+1,255-r,255-g,255-b,a);	
	}
}

VistaCirculo::~VistaCirculo(void)
{
}
