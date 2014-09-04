#pragma once
#include "Figura.h"
#include "CoordenadasR2.h"
#include "Color.h"
class Poligono : public Figura
{
public:
	/*
	x,y es la posicion del centro de masa del poligono regular
	radio es la distancia desde el centro de masa a cualquier vertice
	lados es la cantidad de lados (y vertices)
	*/

	Poligono(CoordenadasR2 centro, Color color, float radio, unsigned int lados, int angulorot,bool dinamico,float masa,  b2World * world);
	unsigned int getVertexCount();
	~Poligono(void);
};

