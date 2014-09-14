#pragma once
#include "..\model\Jugador.h"
#include "../model/constantes.h"
#include "SDL2_gfx\SDL2_gfxPrimitives.h"
#include "VistaFigura.h"
#include "../model/CoordenadasR2.h"
#include <SDL.h>
#include <SDL2\SDL_image.h>
#include "DatosPantalla.h"
#include "../EventLogger.h"
#include <vector>
class VistaJugador: public VistaFigura
{
public: 
	VistaJugador(SDL_Renderer* renderer ,Jugador* jugador,DatosPantalla* datos);
	void render();
	void agregarSprite(std::string path);
	~VistaJugador(void);
private:
	
	void cargarSprites(int dire, int x, int y, int w, int h);
	void dibujar(int numSprite,int x, int y, int w, int h);
	Jugador* m_jugador;
	SDL_Rect m_spriteClips[ 18 ];
	SDL_Texture* m_sprite;
	int ms_ancho;
	int ms_alto;
	int m_dirAnterior;
	int paso;
	int delay;
};
