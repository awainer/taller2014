#pragma once
#include "datosfigura.h"
class DatosJugador :
	public DatosFigura
{
public:
	DatosJugador(void);
	DatosJugador(NewElement * elem);
	CoordenadasR2 getSize();
	int getDireccion();
	//void setPosicion(CoordenadasR2  vertices[6]);
	~DatosJugador(void);
private:
	int direccion;
	CoordenadasR2 size;
	
};

