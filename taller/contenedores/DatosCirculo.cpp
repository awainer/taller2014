#include "DatosCirculo.h"


DatosCirculo::DatosCirculo(Pelota* pelota)
{
	this->setPosicion(pelota->getCentro());
	this->m_radio = pelota->getRadio();
}

void DatosCirculo::setPosicion(CoordenadasR2 centro){

	this->m_x= centro.x;
	this->m_y= centro.y;

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
int DatosCirculo::getId(){
	return 1;
}

DatosCirculo::~DatosCirculo(void)
{

}
