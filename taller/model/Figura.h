#pragma once
#include  <Box2d/Box2d.h>
#include "../Box2D/Collision/b2Collision.h"
#include <vector>
#include "constantes.h"
#include "CoordenadasR2.h"
#include "Color.h"


class Figura 
	
{
public:
	Figura(void);
	virtual ~Figura(void) = 0;
	std::vector <CoordenadasR2> getVertices();
	CoordenadasR2 getPosicion();
	Color color;
	void activar();
	int getType();
	int id;
	static int nextId;
	b2Fixture * getFixture();
	bool seSolapaCon(Figura * otra);
	float normalizarAngulo(int angulo);
protected:
	void setDensidad(float masa);
	b2Body * body;
	b2World * world;
	int type;
	int generateId();
	
};

