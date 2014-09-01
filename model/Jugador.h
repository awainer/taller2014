#pragma once
#include  <Box2d/Box2d.h>
class Jugador
{
public:
	Jugador(float x, float y,b2World * world);
	void moverDerecha();
	void moverIzquierda();
	void saltar();
	~Jugador(void);
private:
	b2Body * body;
	void moverLateral(int lado);
};

