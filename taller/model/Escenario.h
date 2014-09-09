#pragma once
#include <vector>
#include "Figura.h"
#include "Pelota.h"
#include "CoordenadasR2.h"
#include <Box2D/Box2D.h>
#include "Jugador.h"
#include <string>
class Escenario
{
public:
	Escenario(float largo, float alto,CoordenadasR2 gravedad, std::string fondo, b2World * mundo);
	void agregarPelota(CoordenadasR2 centro, float radio, Color color, bool dinamica, float masa);
	void agregarPoligono(CoordenadasR2 centro, float radio, unsigned int lados,unsigned int angulo, Color color, bool dinamica, float masa);
	void agregarRectangulo(CoordenadasR2 centro, float alto, float ancho,unsigned int angulo, Color color, bool dinamica, float masa);
	void agregarParalelogramo(CoordenadasR2 centro,float longlado1, float longlado2, float altura, Color color, int angulorot,bool dinamico,float masa);
	void agregarTrapecio(CoordenadasR2 centro,float longpiso, float longtecho, float altura, Color color, int angulorot,bool dinamico,float masa);
	void agregarJugador(CoordenadasR2 centro);
	void step();
	CoordenadasR2 getSize();
	std::string getPathFondo();
	std::vector <Figura*> getPoligonos();
	std::vector <Pelota*> getPelotas();
	std::vector <Jugador *> getJugadores();
	~Escenario(void);
private:
	// TODO separar entre estaticos y dinamicos
	std::vector <Figura*> cuerposEstaticos;
	std::vector <Figura*> paredes;
	std::vector <Pelota*> pelotas;
	std::vector <Jugador*> jugadores;
	b2World * world;
	float largo;
	float alto;
	std::string fondo;
	b2ContactListener * handler;
};

