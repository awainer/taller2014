#include "Escenario.h"
#include "Pared.h"
#include "Rectangulo.h"
#include "Poligono.h"
#include <Box2d/Box2d.h>
#include "CollisionHandler.h"
#include <iostream>
#include <string>
Escenario::Escenario(float largo, float alto,CoordenadasR2 gravedad, std::string fondo, b2World * mundo)
{
	if(mundo != NULL){
		this->world = mundo;
	}else{
		b2Vec2 gravity = b2Vec2(gravedad.x,gravedad.y);
		this-> world = new b2World(gravity);
	}

	// Piso
	this->paredes.push_back(new Pared(largo/2,0,largo,this->world,FLOOR));
	// Techo
	this->paredes.push_back(new Pared(largo/2,alto,largo,this->world,ROOF));
	// Pared izquierda
	this->paredes.push_back(new Pared(0,alto/2,alto,this->world,LEFT_WALL));
	// Pared derecha
	this->paredes.push_back(new Pared(largo,alto/2,alto,this->world,RIGHT_WALL));

	this->alto = alto;
	this->largo = largo;

	this->world->SetContactListener(new CollisionHandler());
}

void Escenario::agregarPelota(CoordenadasR2 centro, float radio, Color color, bool dinamica, float masa){
	this->pelotas.push_back(new Pelota(centro,color,radio,dinamica,masa,this->world));
}
void Escenario::agregarPoligono(CoordenadasR2 centro, float radio, unsigned int lados,unsigned int angulo, Color color, bool dinamica, float masa){
	this->cuerposEstaticos.push_back((Figura*) new Poligono(centro,color,radio,lados,angulo,dinamica,masa,this->world));
}

void Escenario::agregarRectangulo(CoordenadasR2 centro, float alto, float ancho,unsigned int angulo, Color color, bool dinamica, float masa){
	this->cuerposEstaticos.push_back((Figura*) new Rectangulo(centro,alto,ancho,dinamica,color,masa,angulo,this->world));
}


CoordenadasR2 Escenario::getSize(){
	return CoordenadasR2(this->largo,this->alto);
}
std::vector <Figura*> Escenario::getPoligonos(){
	return this->cuerposEstaticos;
}

std::vector <Pelota*> Escenario::getPelotas(){
	return this->pelotas;
}

void Escenario::agregarJugador(CoordenadasR2 centro){
	this->jugadores.push_back(new Jugador(centro.x,centro.y,this->world));
}

std::vector <Jugador *> Escenario::getJugadores(){
	return this->jugadores;
}

std::string Escenario::getPathFondo(){
	return this->fondo;
}

void Escenario::step(){
	this->world->Step(1.0f/60,10,10);
}
Escenario::~Escenario(void)
{
	std::cout << "Dstructor escenario" << std::cout;
	for (unsigned i=0; i< this->paredes.size(); i++)
		delete this->paredes[i];
	for (unsigned i=0; i< this->pelotas.size(); i++)
		delete this->pelotas[i];
	for (unsigned  i=0; i< this->cuerposEstaticos.size(); i++)
		delete this->cuerposEstaticos[i];	
	//for (i=0; i< this->jugadores.size(); i++)
	//	delete this->jugadores[i];	

	
	//this->paredes.clear();
	delete this->world;
	
	
}
