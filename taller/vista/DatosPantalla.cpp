#include "DatosPantalla.h"


DatosPantalla::DatosPantalla(int ancho_pixeles, int alto_pixeles, float ancho_metros, float alto_metros)
{
	this->m_ancho_px = ancho_pixeles;
	this->m_alto_px = alto_pixeles;
	this->m_ancho_mt = ancho_metros;
	this->m_alto_mt = alto_metros;
}

int DatosPantalla::getAnchoPixel(){
	return this->m_ancho_px;
}

int DatosPantalla::getAltoPixel(){
	return this->m_alto_px;
}

float DatosPantalla::getXratio(){
	return ((this->m_ancho_px)/(this->m_ancho_mt));
}


float DatosPantalla::getYratio(){
	return ((this->m_alto_px)/(this->m_alto_mt));
}

DatosPantalla::~DatosPantalla(void)
{
}
