#pragma once
#include <SDL.h>
#include "SDL2_gfx/SDL2_gfxPrimitives.h"
#include <cmath>
#include "../model/Pelota.h"
class VistaCirculo
{
public:
	VistaCirculo( SDL_Renderer* gRenderer, Pelota * pelota );
	void render(); // x e y deberian ser float
	~VistaCirculo(void);
private:
	Sint16 m_radio;
	SDL_Renderer* m_renderer;
	Pelota * pelota;
};
