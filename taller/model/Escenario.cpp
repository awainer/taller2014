#include "Escenario.h"
#include "Pared.h"
#include "Poligono.h"
#include <Box2d/Box2d.h>

Escenario::Escenario(float largo, float alto,b2World * mundo)
{
	if(mundo != NULL){
		this->world = mundo;
	}else{
		b2Vec2 gravity = b2Vec2(0,-5.0f);
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


}

void Escenario::agregarPelota(CoordenadasR2 centro){
	this->pelotas.push_back(new Pelota(centro.x,centro.y,0.5,this->world));
}
void Escenario::agregarPoligono(CoordenadasR2 centro, float radio, unsigned int lados, unsigned int angulo){
	this->cuerposEstaticos.push_back((Figura*) new Poligono(centro.x,centro.y,radio,lados,angulo,this->world));
}

std::vector <Figura*> Escenario::getPoligonos(){
	return this->cuerposEstaticos;
}

std::vector <Pelota*> Escenario::getPelotas(){
	return this->pelotas;
}

void Escenario::step(){
	this->world->Step(1.0f/60,3,3);
}
Escenario::~Escenario(void)
{
	//TODO destruir todas las figuras
	delete this->world;
	
}
