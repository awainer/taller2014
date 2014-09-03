#pragma once
#include "Figura.h"
#include <Box2D\Box2D.h>
#include "CoordenadasR2.h"
class Pelota :
	public Figura
{
public:
	Pelota(float x, float y,float radio, b2World * world);
	CoordenadasR2 getCentro();
	CoordenadasR2 getPuntoReferencia();
	float getRadio();
	~Pelota(void);
};

