#pragma once
#include "datosfigura.h"
class DatosJugador :
	public DatosFigura
{
public:
	DatosJugador(void);
	DatosJugador(NewElement * elem);
	//void setPosicion(CoordenadasR2  vertices[6]);
	~DatosJugador(void);
};

