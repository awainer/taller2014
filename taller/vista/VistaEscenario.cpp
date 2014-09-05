#include "VistaEscenario.h"


VistaEscenario::VistaEscenario(SDL_Renderer* renderer , float xratio, float yratio)
{
	m_renderer = renderer;
	m_xratio = xratio;
	m_yratio = yratio;
}

void VistaEscenario::agregarPelota(Pelota* pelota){
	this->figuras.push_back(new VistaCirculo(m_renderer,pelota,m_xratio,m_yratio));
}

void VistaEscenario::agregarPoligonos(Poligono* poligono){
	this->figuras.push_back(new VistaPoligono(m_renderer,poligono,m_xratio,m_yratio));
}

//TODO: falta implementar, recordar q hay q borrar la textura una vez se borra el escenario
void VistaEscenario::agregarFondo(){

}

void VistaEscenario::mostrar(){
	//Clear screen		
	SDL_SetRenderDrawColor( m_renderer, 255, 255, 255, 255 );
	SDL_RenderClear( m_renderer );
	//TODO:falta cargar fondo en pantalla antes
	
	//cargo figuras en el pantalla
	for(int i=0; i<figuras.size() ;i++){
		figuras[i]->render();
	}
	SDL_RenderPresent(m_renderer);
}
VistaEscenario::~VistaEscenario(void)
{
	for(int i=0; i<figuras.size() ;i++){
		delete figuras[i];
	}
}
