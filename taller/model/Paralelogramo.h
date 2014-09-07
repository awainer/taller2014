#pragma once
#include "Poligono.h"
#include "CoordenadasR2.h"
#include "Color.h"

class Paralelogramo : public Poligono
{
public:
	/*
	x,y es la posicion del centro de masa del poligono regular
	radio es la distancia desde el centro de masa a cualquier vertice
	lados es la cantidad de lados (y vertices)
	*/
	Paralelogramo();
	Paralelogramo(CoordenadasR2 centro,float longlado1, float longlado2, float altura, Color color, int angulorot,bool dinamico,float masa,  b2World * world);
	unsigned int getVertexCount();
	~Paralelogramo(void);
};

