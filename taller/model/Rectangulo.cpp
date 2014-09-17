#include "Rectangulo.h"
#include "../EventLogger.h"
#include  <Box2d/Box2d.h>

// x e y se refieren a la posicion del centro de masa
Rectangulo::Rectangulo(CoordenadasR2 centro, float alto, float ancho, bool dinamico,Color color,float masa,unsigned int angulo,b2World * world)
{
	this->world = world;

	b2BodyDef bd;
	b2FixtureDef fixtureDef;
	bd.bullet = false;
	bd.position.Set(centro.x,centro.y);
	bd.angle = this->normalizarAngulo(angulo);
	if (dinamico){
		bd.type = b2_dynamicBody;
        fixtureDef.friction = 0.8f;
		this->type = DYNAMIC_BODY;
        //fixtureDef.restitution = 0.4f;
	}
	else{
		bd.type = b2_staticBody;
		this->type = STATIC_BODY;
	}
	bd.userData = (void*)this;	
	this->body = this->world->CreateBody(&bd);
	b2PolygonShape shape;
	shape.SetAsBox(ancho/2,alto/2,b2Vec2(0,0),this->normalizarAngulo(angulo)); 
	fixtureDef.shape = &shape;
	this->body->CreateFixture(&fixtureDef);
	this->setDensidad(masa);
	this->color = color;
	this->generateId();
	std::string msg =	"Agregando rectangulo con id "  + EventLogger::itos(this->id);
	EventLogger::AgregarEvento(msg, DEBUG);

}

