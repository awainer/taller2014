#pragma once
#include <SDL.h>
#include "SDL2_gfx/SDL2_gfxPrimitives.h"
#include <cmath>
#include "VistaFigura.h"
#include "../model/Pelota.h"
#include "DatosPantalla.h"
class VistaCirculo : public VistaFigura
{
public:
	VistaCirculo( SDL_Renderer* gRenderer, Pelota * pelota, DatosPantalla* datos  );
	void render() ;
	~VistaCirculo(void);
private:
	Sint16 m_radio;
	Pelota * pelota;
};
