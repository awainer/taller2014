#include "Jugador.h"
#include "constantes.h"

//Constantes del Jugador
#define ALTO_JUGADOR     1.5
#define ANCHO_JUGADOR    0.25
#define IMPULSO_CAMINAR  6
#define	IMPULSO_SALTAR	 20
#define VELOCIDAD_MAXIMA 8
#define UMBRAL_SALTO 0.1// velocidad vertical maxima para iniciar salto
#define IZQUIERDA -1
#define DERECHA    1

Jugador::Jugador(float x, float y,b2World * world)
{
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	b2PolygonShape shape;

	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x,y);
	//bodyDef.angularDamping = 200;
	bodyDef.fixedRotation = true;
	bodyDef.bullet = true;
	this->body = world->CreateBody(&bodyDef);
	shape.SetAsBox(ANCHO_JUGADOR/2,ALTO_JUGADOR/2);
	fixtureDef.shape = &shape;
	fixtureDef.friction=5;
	
	fixtureDef.density = 7;
	this->body->CreateFixture(&fixtureDef);
	this->body->SetUserData((void*)this);
	this->type = CHARACTER;



}

void Jugador::moverLateral(int lado){
	float intensidad = 1;
	b2Vec2 velocidad = this->body->GetLinearVelocity();
	if (abs(velocidad.y) > 0.5) //estamos en el aire, que el impulso sea menor
		intensidad = 0.25 * intensidad;
		//return;
		
	if (abs(velocidad.x) < VELOCIDAD_MAXIMA){
			velocidad.x = velocidad.x	+ lado * IMPULSO_CAMINAR * intensidad;
			this->body->SetLinearVelocity(velocidad);
		}

	
		//this->body->ApplyForceToCenter(b2Vec2(lado * IMPULSO_CAMINAR,0),true);
		//this->body->ApplyLinearImpulse(b2Vec2(intensidad,0),this->body->GetWorldCenter(),true);
}
void Jugador::moverDerecha(){
	this->moverLateral(DERECHA);
	
}

void Jugador::moverIzquierda(){
	this->moverLateral(IZQUIERDA);
}

void Jugador::saltar(){
	float verticalVelocity = this->body->GetLinearVelocity().y;
	// Solo se puede saltar cuando estas en el piso.
	if(abs(verticalVelocity) < UMBRAL_SALTO)
		this->body->ApplyLinearImpulse(b2Vec2(0,IMPULSO_SALTAR),this->body->GetWorldCenter(),true);
}

CoordenadasR2 Jugador::getSize(){
	return CoordenadasR2(ANCHO_JUGADOR,ALTO_JUGADOR);
}
Jugador::~Jugador(void)
{
	b2World* world= this->body->GetWorld();
	world->DestroyBody(this->body);
}
