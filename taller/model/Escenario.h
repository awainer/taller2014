#pragma once
#include <vector>
#include "Figura.h"
#include "Pelota.h"
#include "CoordenadasR2.h"
#include <Box2D/Box2D.h>

class Escenario
{
public:
	Escenario(float largo, float alto, b2World * mundo);
	void agregarPelota(CoordenadasR2 centro);
	~Escenario(void);
private:
	std::vector <Figura*> cuerposEstaticos;
	std::vector <Pelota*> pelotas;
	b2World * world;
};

