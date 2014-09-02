#pragma once
#include  <Box2d/Box2d.h>
#include <vector>
#include "constantes.h"
#include "CoordenadasR2.h"

class Figura 
	
{
public:
	Figura(void);
	~Figura(void);
	std::vector <CoordenadasR2> getVertices();
protected:
	b2Body * body;
	b2World * world;
	int type;
};

