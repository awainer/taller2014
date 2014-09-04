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
	void agregarPelota(CoordenadasR2 centro, float radio, Color color, bool dinamica, float masa);
	void agregarPoligono(CoordenadasR2 centro, float radio, unsigned int lados,unsigned int angulo, Color color, bool dinamica, float masa);
	void step();
	CoordenadasR2 getSize();
	std::vector <Figura*> getPoligonos();
	std::vector <Pelota*> getPelotas();
	~Escenario(void);
private:
	std::vector <Figura*> cuerposEstaticos;
	std::vector <Figura*> paredes;
	std::vector <Pelota*> pelotas;
	b2World * world;
	float largo;
	float alto;
};

