#pragma once
#include "model\Jugador.h"
#include <SDL.h>
class ControladorJugador
{
public:
	ControladorJugador(Jugador* jugador);
	void actualizar();
	~ControladorJugador(void);
private:
	Jugador* m_jugador;
	const Uint8* m_keys;
	
};

