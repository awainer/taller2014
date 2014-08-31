#pragma once
#include "Figura.h"
#include  <Box2d/Box2d.h>

class Rectangulo: Figura
{
public:
	Rectangulo(unsigned int x, unsigned int y, unsigned int alto, unsigned int ancho, b2World * world, bool dinamico);
	~Rectangulo(void);
};

