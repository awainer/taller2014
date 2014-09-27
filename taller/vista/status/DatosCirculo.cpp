#include "DatosCirculo.h"

DatosCirculo::DatosCirculo(NewElement* elem){
	this->setPosicion(elem->vertices);
	this->m_radio = elem->radio;
}
DatosCirculo::DatosCirculo(Pelota* pelota)
{
	CoordenadasR2 vec[6];
	vec[0] = pelota->getCentro();
	this->setPosicion(vec);
	this->m_radio = pelota->getRadio();
}

void DatosCirculo::setPosicion(CoordenadasR2 centro[6]){

	this->m_x= centro[0].x;
	this->m_y= centro[0].y;

}
CoordenadasR2 DatosCirculo::getPosicion(){
	CoordenadasR2 pos = CoordenadasR2(0,0);
	pos.x = m_x;
	pos.y = m_y;
	return pos;
}

float DatosCirculo::getRadio(){
	return m_radio;
}


DatosCirculo::~DatosCirculo(void)
{

}
