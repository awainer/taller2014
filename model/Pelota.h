#pragma once
#include "Figura.h"
#include <Box2D\Box2D.h>
class Pelota :
	public Figura
{
public:
	Pelota(float x, float y,float radio, b2World * world);
	~Pelota(void);
};

