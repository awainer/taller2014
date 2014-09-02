#pragma once
#include <SDL.h>
#include "SDL2_gfx\SDL2_gfxPrimitives.h"
class VistaPoligono
{
public:
	//recibe el renderer donde dibujar junto la cantidad de vertices.
	VistaPoligono(SDL_Renderer* gRenderer, int n_vertices );
	//cargar poligono, junto con vector con vertices
	void render(const int* vx,const int* vy);

	void transformarSint16(const int* vx,const int* vy){
		for(int i = 0; i<n_vertices; i++){
			m_vx[i]=vx[i];
			m_vy[i]=vy[i];
		} 
		
	}
	~VistaPoligono(void);
private:
	
	int n_vertices;
	SDL_Renderer* m_renderer;
	Sint16* m_vx;
	Sint16* m_vy;
	
	
};

