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
//#include <iostream>
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
	Pelota * p = NULL;
	if(!this->contiene(centro)){
			log("Escenario: No puedo agregar una pelota con centro de masa fuera del escenario:" + centro.str(),WARNING);
			return;
	}
	if (Pelota::validarParametros(radio)){
		p = new Pelota(centro,color,radio,dinamica,masa,this->world);
		if (!this->checkOverlap(p)){
			this->pelotas.push_back(p);
			log("Escenario: pelota agregada!",DEBUG);
		}else{			
			log("Escenario: No puedo agregar una pelota porque se superpone a otro cuerpo",WARNING);
			delete p;
		}
	}
	

}

void Escenario::agregarPoligono(CoordenadasR2 centro, float radio, unsigned int lados,unsigned int angulo, Color color, bool dinamica, float masa){
	Poligono * p = NULL;
	if(!this->contiene(centro)){
			log("No puedo agregar una poligono con centro de masa fuera del escenario:" + centro.str(),WARNING);
			return;
	}
	if (Poligono::validarParametros(lados,radio)){
		p =  new Poligono(centro,color,radio,lados,angulo,dinamica,masa,this->world);
		if (!this->checkOverlap(p)){
				this->cuerposEstaticos.push_back(p);
				log("Escenario: poligono agregado!",DEBUG);
			}else{
				log("Escenario: No puedo agregar un poligono porque se superpone a otro cuerpo",WARNING);
				delete p;
			}
	}
}

void Escenario::agregarRectangulo(CoordenadasR2 centro, float alto, float ancho,unsigned int angulo, Color color, bool dinamica, float masa){
	Rectangulo * r = NULL;
	if(!this->contiene(centro)){
			log("No puedo agregar una rectangulo con centro de masa fuera del escenario:" + centro.str(),WARNING);
			return;
	}
	if (Rectangulo::validarParametros(alto,ancho)){
		r = new Rectangulo(centro,alto,ancho,dinamica,color,masa,angulo,this->world);
		if (!this->checkOverlap((Figura *) r)){
			this->cuerposEstaticos.push_back((Figura * ) r);
			log("Escenario: rectangulo agregado!",DEBUG);
			//this->cuerposEstaticos.push_back((Figura*) new );
		}else{
			log("Escenario: No puedo agregar un Rectangulo porque se superpone a otro cuerpo",WARNING);
			delete r;
		}
	}
}

void Escenario::agregarParalelogramo(CoordenadasR2 centro,float longlado1, float longlado2, float altura, Color color, int angulorot,bool dinamico,float masa){
	Paralelogramo * p = NULL;
	if(!this->contiene(centro)){
			log("No puedo agregar un paralelogramo con centro de masa fuera del escenario:" + centro.str(),WARNING);
			return;
	}
	if (Paralelogramo::validarParametros(longlado1, longlado2, altura)){
		p = new Paralelogramo(centro,longlado1,longlado2, altura, color,angulorot,dinamico,masa, this->world);
		if (!this->checkOverlap((Figura *) p)){
			this->cuerposEstaticos.push_back((Figura * ) p);
			log("Escenario: Paralelogramo agregado!",DEBUG);
			//this->cuerposEstaticos.push_back((Figura*) new Paralelogramo(centro,longlado1,longlado2, altura, color,angulorot,dinamico,masa, this->world));
		}else{
			log("Escenario: No puedo agregar un Paralelogramo porque se superpone a otro cuerpo",WARNING);
			delete p;
		}

	}
	//this->checkOverlap();
}

void Escenario::agregarTrapecio(CoordenadasR2 centro,float longladoizq, float longtecho,float longladoder, float altura, Color color, int angulorot,bool dinamico,float masa){
	Trapecio * t = NULL;
	if(!this->contiene(centro)){
			log("No puedo agregar un trapecio con centro de masa fuera del escenario:" + centro.str(),WARNING);
			return;
	}
	if (Trapecio::validarParametros(longladoizq,longtecho,longladoder,altura)){
		t = new Trapecio(centro,longladoizq,longtecho,longladoder, altura, color,angulorot,dinamico,masa, this->world);
		if (!this->checkOverlap((Figura *) t)){
			this->cuerposEstaticos.push_back((Figura * ) t);
			log("Escenario: Trapecio agregado!",DEBUG);
		}else{
			log("Escenario: No puedo agregar un Trapecio porque se superpone a otro cuerpo",WARNING);
			delete t;
		}
	}
	//this->cuerposEstaticos.push_back((Figura*) new Trapecio(centro,longladoizq,longtecho,longladoder, altura, color,angulorot,dinamico,masa, this->world));
	//this->checkOverlap();
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
	if(!this->contiene(centro)){
		log("Centro de masa del jugador fuera del escenario:" + centro.str(),WARNING);
		this->jugadores.push_back(new Jugador(centro.x,centro.y,this->world));
	}
	else{
		this->jugadores.push_back(new Jugador(this->largo / 2,this->alto / 2 ,this->world));
	}
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

bool Escenario::checkOverlap(Figura * f){

	// Chequeo contra las paredes
	for(std::list<Figura*>::iterator it=this->paredes.begin(); it != this->paredes.end(); ++it){
		if ( f->seSolapaCon(*it))
			return true;
	}
	// Contra las pelotas
	for(std::list<Figura*>::iterator it=this->pelotas.begin(); it != this->pelotas.end(); ++it){
		if ( f->seSolapaCon(*it))
			return true;
	}
	
	// contra poligonos
	for(std::list<Figura*>::iterator it=this->cuerposEstaticos.begin(); it != this->cuerposEstaticos.end(); ++it){
		if ( f->seSolapaCon(*it))
			return true;
	}
	// contra jugadores
	for(std::list<Jugador*>::iterator it=this->jugadores.begin(); it != this->jugadores.end(); ++it){
		if ( f->seSolapaCon(*it))
			return true;
	}

	return false;
}

/*Figura * aux_decidir(Figura * figA, Figura * figB){
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
*/
Escenario::~Escenario(void)
{
	log("Dstructor escenario",WARNING);
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
