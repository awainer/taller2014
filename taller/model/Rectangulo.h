#pragma once
#include "Poligono.h"
#include "Color.h"
#include "CoordenadasR2.h"
#include  <Box2d/Box2d.h>

class Rectangulo: Poligono
{
public:
	Rectangulo(CoordenadasR2 centro, float alto, float ancho, bool dinamico,Color color,float masa,unsigned int angulo, b2World * world);
};

