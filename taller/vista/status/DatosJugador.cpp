#include "DatosJugador.h"


DatosJugador::DatosJugador(void)
{
	
}
DatosJugador::DatosJugador(NewElement * elem)
{
	this->setPosicion(elem->vertices);
	this->id = elem->id;
	this->direccion = elem->direccion;
	this->size.y = elem->alto;
	this->size.x = elem->ancho;
	
}

CoordenadasR2 DatosJugador::getSize(){
	return this->size;
}

int DatosJugador::getDireccion(){
	return this->direccion;
}


DatosJugador::~DatosJugador(void)
{
}
