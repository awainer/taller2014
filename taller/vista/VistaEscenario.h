#pragma once
#include <vector>
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <vista\VistaFigura.h>
#include <vista\VistaCirculo.h>
#include <vista\VistaPoligono.h>
#include <model\Pelota.h>
#include <model\Poligono.h>
#include <model\Escenario.h>
#include <vista\DatosPantalla.h>
#include <vista\VistaJugador.h>
#include <list>
#include <iostream>

class VistaEscenario
{
public:
	VistaEscenario(Escenario* escenario, DatosPantalla* datos);
	VistaEscenario(DatosPantalla* datos);
	void agregarFondo(std::string path);	
	void mostrar();
	void resize(int ancho,int alto);
	bool agregarJugador(Jugador* jugador);//devuelve bool en el caso q no pueda cargar el sprite
	void agregarPelota(DatosCirculo* pelota);
	void agregarPoligonos(DatosPoligono* poligono);
	bool agregarJugador(DatosJugador* jugador);//devuelve bool en el caso q no pueda cargar el sprite
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

