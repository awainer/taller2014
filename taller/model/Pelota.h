#pragma once
#include "Figura.h"
#include <Box2D\Box2D.h>
#include "CoordenadasR2.h"
#include "Color.h"
class Pelota :
	public Figura

{
public:
	Pelota(CoordenadasR2 centro, Color color,float radio,bool dinamica,float masa, b2World * world);
	~Pelota(void);
	CoordenadasR2 getCentro();
	CoordenadasR2 getPuntoReferencia();
	b2Shape * getShape();
	float getRadio();
};

