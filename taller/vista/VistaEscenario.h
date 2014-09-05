#pragma once
#include <vector>
#include <SDL.h>
#include <SDL2\SDL_image.h>
#include "VistaFigura.h"
#include "VistaCirculo.h"
#include "VistaPoligono.h"
#include "..\model\Pelota.h"
#include "..\model\Poligono.h"
#include "../model/Escenario.h"

#include <iostream>
class VistaEscenario
{
public:
	VistaEscenario(Escenario* escenario, float xratio, float yratio);
	void agregarFondo(std::string path);	
	void mostrar();
	void resize(int ancho,int alto);
	~VistaEscenario(void);
private:
	void cargarFiguras();
	void agregarPelota(Pelota* pelota);
	void agregarPoligonos(Poligono* poligono);
	bool iniciarSDL();
	Escenario* m_escenario;
	std::vector <VistaFigura*> figuras;
	SDL_Renderer* m_renderer;
	SDL_Window* m_window;
	SDL_Texture* m_fondo;
	float m_xratio;
	float m_yratio;
	int m_ancho;
	int m_alto;
};

