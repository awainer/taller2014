#pragma once
#include <SDL2/SDL.h>
#include <vista/SDL2_gfx/SDL2_gfxPrimitives.h>
#include "../model/CoordenadasR2.h"
#include "../model/Poligono.h"
#include "../model/Figura.h"
#include <vector>
class VistaPoligono
{
public:
	//recibe el renderer donde dibujar junto la cantidad de vertices.
	VistaPoligono(SDL_Renderer* gRenderer, Poligono * poligono);
	//cargar poligono, junto con vector con vertices
	void render();

	void transformarSint16(std::vector<CoordenadasR2> vertices){

		for(int i = 0; i<n_vertices; i++){
			m_vx[i]=vertices[i].x;
			m_vy[i]=vertices[i].y;
		} 
		
	}
	~VistaPoligono(void);
private:
	
	int n_vertices;
	SDL_Renderer* m_renderer;
	Sint16* m_vx;
	Sint16* m_vy;
	Poligono * poligono;
	
	
};

