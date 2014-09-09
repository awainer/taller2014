#pragma once
#include "Poligono.h"
#include "CoordenadasR2.h"
#include "Color.h"

class Trapecio : public Poligono
{
public:
	/*
	x,y es la posicion del centro de masa del poligono regular
	Datos a proporcionar: longitud lado1, longitud lado2 y altura.

	            techo
	        V2 ________ V3
	          /  |     \
	  lado1  /   | C    \  lado3
	        /    | H     \
	       /_____|________\
	      V1     piso     V4
	*/
	Trapecio();
	Trapecio(CoordenadasR2 centro,float longpiso, float longtecho, float altura, Color color, int angulorot,bool dinamico,float masa,  b2World * world);
	~Trapecio(void);
};

