#pragma once
#include "..\model\Jugador.h"
#include "SDL2_gfx\SDL2_gfxPrimitives.h"
#include "VistaFigura.h"
#include "../model/CoordenadasR2.h"
#include <SDL.h>
#include "DatosPantalla.h"
#include <vector>
class VistaJugador: public VistaFigura
{
public: 
	VistaJugador(SDL_Renderer* renderer ,Jugador* jugador,DatosPantalla* datos);
	void render();
	~VistaJugador(void);
private:
	void transformarSint16(std::vector<CoordenadasR2> vertices);
	Jugador* m_jugador;
	Sint16* m_vx;
	Sint16* m_vy;
};

