#pragma once
#include <SDL2/SDL.h>
#include <vista/SDL2_gfx/SDL2_gfxPrimitives.h>
#include <cmath>
#include <vista/VistaFigura.h>
#include "../model/Pelota.h"
#include <vista/DatosPantalla.h>
#include <vista/status/DatosCirculo.h>
class VistaCirculo : public VistaFigura
{
public:
	VistaCirculo( SDL_Renderer* gRenderer, Pelota * pelota, DatosPantalla* datos  );
	VistaCirculo( SDL_Renderer* gRenderer, DatosCirculo * pelota, DatosPantalla* datos  );
	void render() ;
	~VistaCirculo(void);
private:
	Sint16 m_radio;
	Pelota * pelota;
	DatosCirculo* d_pelota;
};
