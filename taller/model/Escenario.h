#pragma once
#include <list>
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
	void agregarParalelogramo(CoordenadasR2 centro,float longlado1, float longlado2, float angulo, Color color, int angulorot,bool dinamico,float masa);
	void agregarTrapecio(CoordenadasR2 centro,float longladoizq, float longtecho,float longladoder, float altura, Color color, int angulorot,bool dinamico,float masa);
	void agregarJugador(CoordenadasR2 centro);
	void step();
	bool checkOverlap(Figura * f);
	void deleteFigura(Figura * f);
	CoordenadasR2 getSize();
	bool contiene(CoordenadasR2 punto);
	std::string getPathFondo();
	std::list <Figura*> getPoligonos();
	std::list <Figura*> getPelotas();
	std::list <Jugador *> getJugadores();
	~Escenario(void);
private:
	// TODO separar entre estaticos y dinamicos
	std::list <Figura*> cuerposEstaticos;
	std::list <Figura*> paredes;
	std::list <Figura*> pelotas;
	std::list <Jugador*> jugadores;
	b2World * world;
	float largo;
	float alto;
	std::string fondo;
	b2ContactListener * handler;
	Figura * decidirConflicto(b2Fixture * a, b2Fixture * b);
};

