#pragma once
#include <vista/DatosPantalla.h>
#include <SDL2/SDL.h>
class VistaFigura
{
public:
	VistaFigura(void);
	virtual void render() = 0;
	virtual ~VistaFigura(void) = 0;
protected:
	DatosPantalla* m_datos;
	SDL_Renderer* m_renderer;
};

