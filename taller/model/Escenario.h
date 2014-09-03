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
	void agregarPoligono(CoordenadasR2 centro, float radio, unsigned int lados,unsigned int angulo);
	std::vector <Figura*> getPoligonos();
	~Escenario(void);
private:
	std::vector <Figura*> cuerposEstaticos;
	std::vector <Figura*> paredes;
	std::vector <Pelota*> pelotas;
	b2World * world;
};

