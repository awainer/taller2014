#pragma once
#include "Figura.h"
#include "constantes.h"
class Pared :
	public Figura
{
public:
	Pared(float x, float y, float largo, b2World * world, int tipo);
	~Pared(void);
};

