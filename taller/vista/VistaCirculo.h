#pragma once
#include <SDL.h>
#include "SDL2_gfx/SDL2_gfxPrimitives.h"
#include <cmath>
#include "../model/Pelota.h"
class VistaCirculo
{
public:
	VistaCirculo(Pelota * pelota, SDL_Renderer* gRenderer );
	void render(); // x e y deberian ser float
	~VistaCirculo(void);
private:
	float m_radio;
	SDL_Renderer* m_renderer;
	Pelota * pelota;
};
