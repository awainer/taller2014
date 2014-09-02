#pragma once
#include  <Box2d/Box2d.h>
#include "constantes.h"

class Figura 
	
{
public:
	Figura(void);
	~Figura(void);
protected:
	b2Body * body;
	b2World * world;
	int type;
};

