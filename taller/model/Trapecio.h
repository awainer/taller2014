#pragma once
#include "Poligono.h"
#include "CoordenadasR2.h"
#include "Color.h"

class Trapecio : public Poligono
{
public:
	/*
	Datos a proporcionar: longitud ladoizq, longitud techo, longitud ladoder y altura.

	            techo
	        V2 ________ V3
	          /  |     \
	ladoizq  /   | C    \  ladoder
	        /    | H     \
	       /_____|________\
	      V1     piso     V4
	*/
	Trapecio();
	Trapecio(CoordenadasR2 centro,float longladoizq, float longtecho, float longladoder,  float altura, Color color, float angulorot,bool dinamico,float masa,  b2World * world);
	static bool validarParametros(float longladoizq, float longtecho, float longladoder,  float altura);
	~Trapecio(void);
private:
	static bool validarDimensiones(float longladoizq, float longtecho, float longladoder,  float altura);
};

