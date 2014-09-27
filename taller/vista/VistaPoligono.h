#pragma once
#include <SDL2/SDL.h>
#include <SDL2\SDL_image.h>
#include <vista/SDL2_gfx/SDL2_gfxPrimitives.h>
#include "../model/CoordenadasR2.h"
#include "../model/Poligono.h"
#include "../model/Figura.h"
#include "VistaFigura.h"
#include "DatosPantalla.h"
#include "../EventLogger.h"
#include <vector>
#include "status/DatosPoligono.h"
class VistaPoligono: public VistaFigura
{
public:
	
	VistaPoligono(SDL_Renderer* gRenderer, Poligono * poligono,DatosPantalla* datos);
	VistaPoligono(SDL_Renderer* gRenderer, DatosPoligono * poligono,DatosPantalla* datos);
	void render() ;
	void transformarSint16(std::vector<CoordenadasR2> vertices);
	~VistaPoligono(void);
private:
	
	int n_vertices;
	Sint16* m_vx;
	Sint16* m_vy;
	Poligono * poligono;
	SDL_Surface* m_loadedSurface;
	SDL_Texture* m_texture;
	int x;
	int y;
	DatosPoligono* d_poligono;
};

