#pragma once
#include <vector>
#include <SDL.h>
#include "VistaFigura.h"
#include "VistaCirculo.h"
#include "VistaPoligono.h"
#include "..\model\Pelota.h"
#include "..\model\Poligono.h"
class VistaEscenario
{
public:
	VistaEscenario(SDL_Renderer* renderer, float xratio, float yratio);
	//TODO: falta implementar
	void agregarFondo();
	void agregarPelota(Pelota* pelota);
	void agregarPoligonos(Poligono* poligono);
	void mostrar();
	~VistaEscenario(void);
private:
	std::vector <VistaFigura*> figuras;
	SDL_Renderer* m_renderer;
	float m_xratio;
	float m_yratio;
};

