#pragma once
#include <SDL.h>
class VistaRectangulo
{
public:
	VistaRectangulo(int alto, int ancho,SDL_Renderer* gRenderer );
	
	// carga un el rectango en posicion (x,y) 
	void render(int x,int y);
	
	int getX(){return m_x;}
	int getY(){return m_y;}
	int getAlto(){return m_alto;}
	int getAncho(){return m_ancho;}
	~VistaRectangulo(void);
private:
	int m_alto;
	int m_ancho;
	int m_x;
	int m_y;
	int color;
	SDL_Renderer* m_renderer;
	
};

