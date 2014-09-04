#pragma once
#include  <Box2d/Box2d.h>
#include <vector>
#include "constantes.h"
#include "CoordenadasR2.h"
#include "Color.h"

class Figura 
	
{
public:
	Figura(void);
	~Figura(void);
	std::vector <CoordenadasR2> getVertices();
	Color color;
protected:
	b2Body * body;
	b2World * world;
	int type;
	
};

