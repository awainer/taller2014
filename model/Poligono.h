#pragma once
#include "Figura.h"
class Poligono : Figura
{
public:
	/*
	x,y es la posicion del centro de masa del poligono regular
	radio es la distancia desde el centro de masa a cualquier vertice
	lados es la cantidad de lados (y vertices)
	*/

	Poligono(unsigned int x, unsigned int y, unsigned int radio, unsigned int lados, b2World * world);
	~Poligono(void);
};

