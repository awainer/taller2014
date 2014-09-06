#pragma once
#include  <Box2d/Box2d.h>
#include "Figura.h"
class Jugador : public Figura
{
public:
	Jugador(float x, float y,b2World * world);
	void moverDerecha();
	void moverIzquierda();
	CoordenadasR2 getSize();
	void saltar();
	void sumarContacto();
	void restarContacto();
	~Jugador(void);
private:
	void moverLateral(int lado);
	int contacts;
	int  puedeMover;
};

