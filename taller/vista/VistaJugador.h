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
#include "VistaPoligono.h"
#include "status\DatosJugador.h"
class VistaJugador: public VistaFigura
{
public: 
	VistaJugador(SDL_Renderer* renderer ,Jugador* jugador,DatosPantalla* datos);
	VistaJugador(SDL_Renderer* renderer,DatosJugador* jugador,DatosPantalla* datos);
	void render();
	void agregarSprite(std::string path);
	bool spriteOk();
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
	DatosJugador* d_jugador;
	CoordenadasR2 size;
	//variables para ver cuadrado real del personaje.
	Sint16* m_vx;
	Sint16* m_vy;
	void transformarSint16(std::vector<CoordenadasR2> vertices);
};
