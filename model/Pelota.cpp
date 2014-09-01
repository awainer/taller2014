#include "Pelota.h"


Pelota::Pelota(float x, float y,float radio, b2World * world){
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	b2CircleShape shape;

	this->world = world;
	shape.m_radius = radio;
	shape.m_p.Set(0,0); // respecto del body
	bodyDef.position.Set(x,y);
	bodyDef.type = b2_dynamicBody;
	fixtureDef.density = 1.2f;
	fixtureDef.restitution = 0.3;
	fixtureDef.friction = 0.3;
	fixtureDef.shape = &shape;
	this->body = this->world->CreateBody(&bodyDef);
	this->body->CreateFixture(&fixtureDef);

	//pelotita chiquita para trackear el movimiento
	shape.m_radius = radio / 4;
	shape.m_p.Set(0,radio/2); // respecto del body
	fixtureDef.density = 0;
	this->body->CreateFixture(&fixtureDef);

		

}


Pelota::~Pelota(void)
{
}
