#include "VistaCirculo.h"
#include <math.h>
#include <iostream>

#define PI 3.14159265

VistaCirculo::VistaCirculo(SDL_Renderer* gRenderer , Pelota * pelota)
{
	this->pelota = pelota;
	m_renderer = gRenderer;
}

void VistaCirculo::render(){
	int m_x = this->pelota->getCentro().x;
	int m_y = this->pelota->getCentro().y;
	this->m_radio =(Sint16) this->pelota->getRadio();
	//this->m_radio =20;
	std::cout << " radio "<< this->pelota->getRadio() << std::endl;
	std::cout << " x "<< this->pelota->getCentro().x << " y " << this->pelota->getCentro().y << std::endl; 
	//int rotacion = 0;
	//int escala  = 1;
	//int ret = filledCircleColor(m_renderer, m_x, m_y, m_radio, );
	int ret = filledCircleRGBA(m_renderer,m_x,m_y,m_radio,255,255,0,255);
	std::cout << " x_r "<< this->pelota->getPuntoReferencia().x<< " y_r" << this->pelota->getPuntoReferencia().y << std::endl;
	//filledCircleRGBA(m_renderer,m_x,m_y,m_radio,255,255,0,255);
	filledCircleRGBA(m_renderer,(Sint16)this->pelota->getPuntoReferencia().x,(Sint16)this->pelota->getPuntoReferencia().y,m_radio/4,255,0,0,255);
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
