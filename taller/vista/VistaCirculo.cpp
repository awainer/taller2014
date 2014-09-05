#include "VistaCirculo.h"
#include <math.h>
#include <iostream>
#include <stdlib.h> 

#define PI 3.14159265

VistaCirculo::VistaCirculo(SDL_Renderer* gRenderer , Pelota * pelota, float xratio, float yratio)
{
	this->pelota = pelota;
	m_renderer = gRenderer;
	this->xratio = xratio;
	this->yratio = yratio;
}

void VistaCirculo::render() {
	int m_x = this->pelota->getCentro().x * this->xratio;
	int m_y = this->pelota->getCentro().y * this->yratio;
	this->m_radio =(Sint16) (this->pelota->getRadio() * ((xratio+yratio)/2));
	//this->m_radio =20;
	//std::cout << " radio "<< this->m_radio << std::endl;
	//std::cout << " ref"<< this->pelota->getPuntoReferencia().x << this->pelota->getPuntoReferencia().x  << std::endl;
	//std::cout << " x "<< this->pelota->getCentro().x << " y " << this->pelota->getCentro().y << std::endl; 
	//int rotacion = 0;
	//int escala  = 1;
	//int ret = filledCircleColor(m_renderer, m_x, m_y, m_radio, );
	
	Uint8 r = this->pelota->color.r;   
	Uint8 g = this->pelota->color.g;   
	Uint8 b = this->pelota->color.b;   
	Uint8 a = this->pelota->color.a; 
	int ret = filledCircleRGBA(m_renderer,m_x,m_y,m_radio,r,g,b,a); //falta la clase color
	//std::cout << " x_r "<< this->pelota->getPuntoReferencia().x<< " y_r" << this->pelota->getPuntoReferencia().y << std::endl;
	//filledCircleRGBA(m_renderer,m_x,m_y,m_radio,255,255,0,255);
	Sint16 refx = (Sint16) (this->pelota->getPuntoReferencia().x * xratio);
	Sint16 refy = (Sint16) (this->pelota->getPuntoReferencia().y * yratio);
	filledCircleRGBA(m_renderer,refx,refy,m_radio/4, 255 - r, 255 - g, 255 - b, a); // color negativo al original
	//double res_cos, res_sin;
    //res_cos = cos ( rotacion * PI / 180.0 );
    //res_sin = sin ( rotacion * PI / 180.0 );
    //Uint32 colorTemp = 0xFF000FF0; // deberia ser un color mas oscuro que el propio de la figura
    //int a_x, a_y;
    //a_x = m_radio * res_sin * escala;
    //a_y = m_radio * res_cos * escala;
    //int ret2 = lineColor(m_renderer, m_x, m_y, m_x + a_x, m_y - a_y, colorTemp);
}

VistaCirculo::~VistaCirculo(void)
{
}
