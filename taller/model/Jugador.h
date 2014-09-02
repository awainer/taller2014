#pragma once
#include  <Box2d/Box2d.h>
#include "Figura.h"
class Jugador : Figura
{
public:
	Jugador(float x, float y,b2World * world);
	void moverDerecha();
	void moverIzquierda();
	void saltar();
	~Jugador(void);
private:
	void moverLateral(int lado);
};

