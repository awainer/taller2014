#include "Pared.h"
#include "constantes.h"
#include <iostream>
Pared::Pared(float x, float y, float largo, b2World * world, int tipo)
{

	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	b2EdgeShape edge;

	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(x,y);
	bodyDef.userData = (void*)this;
	bodyDef.bullet = true;

	this->type = tipo;

	this->body = world->CreateBody(&bodyDef);


	if((tipo == FLOOR) || (tipo == ROOF)){ //paredes horizontales
		edge.Set(b2Vec2(-largo/2,0),b2Vec2(largo/2,0));
			fixtureDef.friction = 1.0f;
	}else{  // paredes verticales
		edge.Set(b2Vec2(0,largo/2),b2Vec2(0,-largo/2));
		fixtureDef.friction = 0;
	}
	fixtureDef.shape = &edge;
	fixtureDef.userData = (void*)tipo;
	this->body->CreateFixture(&fixtureDef);

}

Pared::~Pared(){
}

