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
#include "DatosPantalla.h"
#include "VistaJugador.h"
#include <list>
#include <iostream>

class VistaEscenario
{
public:
	VistaEscenario(Escenario* escenario, DatosPantalla* datos);
	void agregarFondo(std::string path);	
	void mostrar();
	void resize(int ancho,int alto);
	bool agregarJugador(Jugador* jugador);
	void agregarPelota(DatosCirculo* pelota);
	void agregarPoligonos(DatosPoligono* poligono);
	~VistaEscenario(void);
private:
	void cargarFiguras();
	void agregarPelota(Pelota* pelota);
	void agregarPoligonos(Poligono* poligono);
	bool iniciarVentana();
	Escenario* m_escenario;
	std::vector <VistaFigura*> figuras;
	SDL_Renderer* m_renderer;
	SDL_Window* m_window;
	SDL_Texture* m_fondo;
	DatosPantalla* m_datos_pantalla;
	int m_ancho;
	int m_alto;
};

