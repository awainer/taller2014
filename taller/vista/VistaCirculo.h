#pragma once
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <cmath>

class VistaCirculo
{
public:
	VistaCirculo(float radio, Uint32 color, SDL_Renderer* gRenderer );
	
	// carga el circulo en posicion (x,y) 
	void render(int x,int y, int rotacion, float escala); // x e y deberian ser float
	
	float getRadio(){return m_radio;}
	int getX(){return m_x;} //deberia ser float
	int getY(){return m_y;} //deberia ser float
	float getEscala(){return m_escala;}
	int getRotacion(){return m_rotacion;}
	Uint32 getColor(){return m_color;}
	~VistaCirculo(void);
private:
	float m_radio;
	int m_x; //deberia ser float
	int m_y; //deberia ser float
	float m_escala;
	int m_rotacion;
	Uint32 m_color;
	SDL_Renderer* m_renderer;
};
