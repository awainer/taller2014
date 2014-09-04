#pragma once
#include <SDL.h>
#include "SDL2_gfx/SDL2_gfxPrimitives.h"
#include <cmath>
#include "VistaFigura.h"
#include "../model/Pelota.h"
class VistaCirculo : public VistaFigura
{
public:
	VistaCirculo( SDL_Renderer* gRenderer, Pelota * pelota,float xratio, float yratio );
	void render() ; // x e y deberian ser float
	~VistaCirculo(void);
private:
	Sint16 m_radio;
	SDL_Renderer* m_renderer;
	Pelota * pelota;
	float xratio;
	float yratio;
};
