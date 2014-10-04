#include "DatosCirculo.h"

DatosCirculo::DatosCirculo(NewElement* elem){
	
	this->iniciarVertices();
	this->setPosicion(elem->vertices);
	this->m_radio = elem->radio;
	this->color = elem->color;
	this->id = elem->id;

}


DatosCirculo::DatosCirculo(Pelota* pelota)
{
	CoordenadasR2 vec[6];
	vec[0] = pelota->getCentro();
	vec[1] = pelota->getPuntoReferencia();
	this->setPosicion(vec);
	this->color = pelota->color;
	this->m_radio = pelota->getRadio();
	this->id = pelota->id;
	
}

CoordenadasR2 DatosCirculo::getPuntoReferencia(){
	return this->m_vertices[1];
}
CoordenadasR2 DatosCirculo::getPosicion(){
	return this->m_vertices[0];
}

float DatosCirculo::getRadio(){
	return m_radio;
}


DatosCirculo::~DatosCirculo(void)
{

}
