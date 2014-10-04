#include "Jugador.h"
#include "constantes.h"
#include "../EventLogger.h"
#include <iostream>
//Constantes del Jugador
#define ALTO_JUGADOR     0.8f
#define ANCHO_JUGADOR    0.3f
#define IMPULSO_CAMINAR  1.0f
#define	IMPULSO_SALTAR	 8.0f
#define VELOCIDAD_MAXIMA 8.0f
#define UMBRAL_SALTO 0.1f// velocidad vertical maxima para iniciar salto
#define UMBRAL_ESTATICO 0.5f
#define IZQ -1
#define DER  1

Jugador::Jugador(float x, float y,b2World * world)
{
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	b2PolygonShape shape,shapeSensor;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x,y);
	bodyDef.fixedRotation = true;
	//bodyDef.bullet = true;
	bodyDef.linearDamping = 0.8f;
	this->body = world->CreateBody(&bodyDef);

	// sensor de piso
	shapeSensor.SetAsBox(0.48f * ANCHO_JUGADOR, 0.1f * ANCHO_JUGADOR, b2Vec2(0.0f,0-ALTO_JUGADOR/2.0f), 0.0f);
	fixtureDef.isSensor = true;
	fixtureDef.shape = &shapeSensor;
	fixtureDef.userData = (void*) FOOT_SENSOR;
	this->body->CreateFixture(&fixtureDef);

	// jugador propiamente dicho
	shape.SetAsBox(ANCHO_JUGADOR/2.0f,ALTO_JUGADOR/2.0f);
	fixtureDef.shape = &shape;
	fixtureDef.isSensor = false;
	fixtureDef.friction = 1.0f;
	fixtureDef.restitution = 0.1f;
	fixtureDef.userData = NULL;
	
	fixtureDef.density = 12;
	this->body->CreateFixture(&fixtureDef);
	this->body->SetUserData((void*)this);
	this->type = CHARACTER;
	
	this->puedeMover = 0;
	this->generateId();
	std::string msg =	"Agregando jugador con id "  + EventLogger::itos(this->id);
	log(msg, DEBUG);

}

void Jugador::moverLateral(int lado){
	//std::cout << "lateral puedemover: " << this->puedeMover << std::endl;
	double factor = 1;
	if (this->puedeMover == 0)
		factor = 0.1;

	b2Vec2 velocidad = this->body->GetLinearVelocity();
	float nuevaVelocidadX = float(velocidad.x	+ lado * IMPULSO_CAMINAR * factor);
	if (abs(nuevaVelocidadX) <= VELOCIDAD_MAXIMA)
		velocidad.x = nuevaVelocidadX;
	//else
	//	velocidad.x = VELOCIDAD_MAXIMA;

	this->body->SetLinearVelocity(velocidad);
		//this->body->ApplyForceToCenter(b2Vec2(lado * IMPULSO_CAMINAR,0),true);
		//this->body->ApplyLinearImpulse(b2Vec2(intensidad,0),this->body->GetWorldCenter(),true);
}
void Jugador::moverDerecha(){
	this->moverLateral(DER);
	
}

void Jugador::moverIzquierda(){
	this->moverLateral(IZQ);
}

void Jugador::saltar(){
	//std::cout << "salto puedemover: " << this->puedeMover << std::endl;
	if (this->puedeMover == 0)
		return;
	//float verticalVelocity = this->body->GetLinearVelocity().y;
	//if( (abs(verticalVelocity) < UMBRAL_SALTO))
	//	this->body->ApplyLinearImpulse(b2Vec2(0,IMPULSO_SALTAR),this->body->GetWorldCenter(),true);
	b2Vec2 velocity = this->body->GetLinearVelocity();
	velocity.y = IMPULSO_SALTAR;
	this->body->SetLinearVelocity(velocity);
}

CoordenadasR2 Jugador::getSize(){
	return CoordenadasR2(float(ANCHO_JUGADOR),float(ALTO_JUGADOR));
}

void Jugador::sumarContacto(){
	this->puedeMover += 1;
}

void Jugador::restarContacto(){
	this->puedeMover -= 1;
}

int Jugador::getDireccion(){
	b2Vec2 vel = this->body->GetLinearVelocity();
	//std::cout << vel.y << " " <<vel.y << std::endl;
	if(abs(vel.x)  < UMBRAL_ESTATICO && abs(vel.y) < UMBRAL_ESTATICO)
		return ESTATICO;
	if(vel.x == 0 && vel.y != 0)
		return ARRIBA;
	if(vel.y == 0  || this->puedeMover > 0){ //cuando esta resbalando tiene velocidad en y, pero no esta en el aire
		if (vel.x > 0)
			return DERECHA;
		else
			return IZQUIERDA;
	}
	// vel.y != 0 => en el aire
	if (vel.x > 0)
		return ARRIBA_DERECHA;
	else
		return ARRIBA_IZQUIERDA;

}
Jugador::~Jugador(void)
{
}
