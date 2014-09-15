#include "Escenario.h"
#include "Pared.h"
#include "Rectangulo.h"
#include "Poligono.h"
#include "Paralelogramo.h"
#include "Trapecio.h"
#include <Box2d/Box2d.h>
#include "../EventLogger.h"
#include "CollisionHandler.h"
#include "constantes.h"
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
	this->handler = new CollisionHandler();
	this->world->SetContactListener(handler);
	this->fondo = fondo;
}

bool Escenario::contiene(CoordenadasR2 punto){
	return (punto.x > 0 && punto.y > 0 && punto.x < this->largo && punto.y < this->alto);
}

void Escenario::agregarPelota(CoordenadasR2 centro, float radio, Color color, bool dinamica, float masa){
	if(!this->contiene(centro)){
			EventLogger::AgregarEvento("No puedo agregar una pelota con centro de masa fuera del escenario:" + centro.str(),WARNING);
			return;
	}
	this->pelotas.push_back(new Pelota(centro,color,radio,dinamica,masa,this->world));
	this->checkOverlap();
}

void Escenario::agregarPoligono(CoordenadasR2 centro, float radio, unsigned int lados,unsigned int angulo, Color color, bool dinamica, float masa){
	if(!this->contiene(centro)){
			EventLogger::AgregarEvento("No puedo agregar una poligono con centro de masa fuera del escenario:" + centro.str(),WARNING);
			return;
	}
	this->cuerposEstaticos.push_back((Figura*) new Poligono(centro,color,radio,lados,angulo,dinamica,masa,this->world));
	this->checkOverlap();
}

void Escenario::agregarRectangulo(CoordenadasR2 centro, float alto, float ancho,unsigned int angulo, Color color, bool dinamica, float masa){
	if(!this->contiene(centro)){
			EventLogger::AgregarEvento("No puedo agregar una rectangulo con centro de masa fuera del escenario:" + centro.str(),WARNING);
			return;
	}
	
		this->cuerposEstaticos.push_back((Figura*) new Rectangulo(centro,alto,ancho,dinamica,color,masa,angulo,this->world));
}

void Escenario::agregarParalelogramo(CoordenadasR2 centro,float longlado1, float longlado2, float altura, Color color, int angulorot,bool dinamico,float masa){
	if(!this->contiene(centro)){
			EventLogger::AgregarEvento("No puedo agregar un paralelogramo con centro de masa fuera del escenario:" + centro.str(),WARNING);
			return;
	}

	this->cuerposEstaticos.push_back((Figura*) new Paralelogramo(centro,longlado1,longlado2, altura, color,angulorot,dinamico,masa, this->world));
	this->checkOverlap();
}

void Escenario::agregarTrapecio(CoordenadasR2 centro,float longpiso, float longtecho, float altura, Color color, int angulorot,bool dinamico,float masa){
	if(!this->contiene(centro)){
			EventLogger::AgregarEvento("No puedo agregar un trapecio con centro de masa fuera del escenario:" + centro.str(),WARNING);
			return;
	}

	this->cuerposEstaticos.push_back((Figura*) new Trapecio(centro,longpiso,longtecho, altura, color,angulorot,dinamico,masa, this->world));
	this->checkOverlap();
}

CoordenadasR2 Escenario::getSize(){
	return CoordenadasR2(this->largo,this->alto);
}
std::list <Figura*> Escenario::getPoligonos(){
	return this->cuerposEstaticos;
}

std::list  <Figura*> Escenario::getPelotas(){
	return this->pelotas;
}
std::list <Jugador *> Escenario::getJugadores(){
	return this->jugadores;
}

void Escenario::agregarJugador(CoordenadasR2 centro){
	this->jugadores.push_back(new Jugador(centro.x,centro.y,this->world));
}



std::string Escenario::getPathFondo(){
	return this->fondo;
}

void Escenario::step(){
	this->world->Step(1.0f/60,10,10);
}

void Escenario::deleteFigura(Figura * f){
	bool terminar = false;
	std::list<Figura*>::iterator j;
	for ( j = this->cuerposEstaticos.begin(); j != this->cuerposEstaticos.end(); j++){
		if ( *j == f){
			terminar = true;
			break;
		}
	}
	if(terminar){
		delete *j;
		this->cuerposEstaticos.erase(j);
		return;
	}
	

	std::list<Figura*>::iterator i;
	if(!terminar){
		for (i = this->pelotas.begin(); i != this->pelotas.end(); i++){
			if ( *i == f)
				break;
		}
		delete *i;
		this->pelotas.erase(i);
	}

}

void Escenario::checkOverlap(){
	// Un step es necesario para que el contact list no sea NULL
	this->step();
	b2Contact * c = this->world->GetContactList();
	Figura * figuraConflictiva;
	while(c){
		if(c->IsTouching()){
			//b2Fixture *fa,*fb;
			figuraConflictiva = this->decidirConflicto(c->GetFixtureA(), c->GetFixtureB());
			EventLogger::AgregarEvento("Borrando cuerpo superpuesto de id " + EventLogger::itos(figuraConflictiva->id));

			this->deleteFigura(figuraConflictiva);
			this->step();
			c = this->world->GetContactList();
		}
	}


}

Figura * aux_decidir(Figura * figA, Figura * figB){
	int typeA = figA->getType();
	int typeB = figB->getType();
	//enum  BODY_TYPE { STATIC_BODY, DYNAMIC_BODY, CHARACTER, PLATFORM, FLOOR, ROOF, RIGHT_WALL, LEFT_WALL, FOOT_SENSOR};
	if ( typeA == DYNAMIC_BODY){
		if (typeB == DYNAMIC_BODY)
			return figB;
		else
			return figA;
	}
	if (typeA == STATIC_BODY){
		if (typeB == DYNAMIC_BODY)
			return figB;
		else
			return figA;
	}
	if (typeA == CHARACTER)
		return figB;
	return NULL;
}

Figura *  Escenario::decidirConflicto(b2Fixture * a, b2Fixture * b){
	Figura * figA = (Figura*)(a->GetBody()->GetUserData());
	Figura * figB = (Figura*)(b->GetBody()->GetUserData());
	Figura * result;
	result = aux_decidir(figA,figB);
	if (result)
		return result;
	else{
		result = aux_decidir(figB,figA);
		if (result)
			return result;
		else
			return figA; // un default, si no pudimos identificar el caso
	}
}

Escenario::~Escenario(void)
{
	std::cout << "Dstructor escenario" << std::cout;
	for(std::list<Figura*>::iterator it=this->paredes.begin(); it != this->paredes.end(); ++it)
		delete (*it);
	for(std::list<Figura*>::iterator it=this->pelotas.begin(); it != this->pelotas.end(); ++it)
		delete (*it);
	for(std::list<Figura*>::iterator it=this->cuerposEstaticos.begin(); it != this->cuerposEstaticos.end(); ++it)
		delete (*it);
	for(std::list<Jugador*>::iterator it=this->jugadores.begin(); it != this->jugadores.end(); ++it)
		delete (*it);
	
	
		
	

	delete this->world;
	delete this->handler; //world deberia encargarse de esto, pero no lo hace...
	
}
