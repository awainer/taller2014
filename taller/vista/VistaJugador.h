#pragma once
#include "..\model\Jugador.h"
#include "../model/constantes.h"
#include "SDL2_gfx\SDL2_gfxPrimitives.h"
#include "VistaFigura.h"
#include "../model/CoordenadasR2.h"
#include <SDL.h>
#include <SDL2\SDL_image.h>
#include "DatosPantalla.h"
#include <vector>
class VistaJugador: public VistaFigura
{
public: 
	VistaJugador(SDL_Renderer* renderer ,Jugador* jugador,DatosPantalla* datos);
	void render();
	void agregarSprite(std::string path);
	~VistaJugador(void);
private:
	void transformarSint16(std::vector<CoordenadasR2> vertices);
	void cargarSprites(int dire, int x, int y, int w, int h);
	Jugador* m_jugador;
	SDL_Rect m_spriteClips[ 5 ];
	SDL_Texture* m_sprite;
	Sint16* m_vx;
	Sint16* m_vy;
	int ms_ancho;
	int ms_alto;
	int m_dirAnterior;
};
