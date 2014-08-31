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

	Poligono(float x, float  y, float radio, unsigned int lados, int angulorot, b2World * world);
	~Poligono(void);
};

