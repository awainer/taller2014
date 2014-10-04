#pragma once
#include "Poligono.h"
#include "CoordenadasR2.h"
#include "Color.h"

class Paralelogramo : public Poligono
{
public:
	/*
	x,y es la posicion del centro de masa del poligono regular
	Datos a proporcionar: longitud lado1, longitud lado2 y angulo &.

	              lado2
	        V2 _____________ V3
	          /  |         /
	  lado1  /   |        /  lado3
	        /)&  | H     /
	       /_)___|______/
	      V1    lado4    V4
	*/
	Paralelogramo();
	Paralelogramo(CoordenadasR2 centro,float longlado1, float longlado2, float angulo, Color color, int angulorot,bool dinamico,float masa,  b2World * world);
	unsigned int getVertexCount();
	static bool validarParametros(float longlado1, float longlado2, float angulo);
	~Paralelogramo(void);
};

