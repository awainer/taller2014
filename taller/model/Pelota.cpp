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

		
	//((b2CircleShape*)this->body->GetFixtureList()[1].GetShape())->
}

float Pelota::getRadio(){
	b2CircleShape * circle = (b2CircleShape * )this->body->GetFixtureList();
	return circle->m_radius;
}

CoordenadasR2 Pelota::getPuntoReferencia(){
	b2Vec2 p = this->body->GetWorldPoint(b2Vec2(0,0.4));
		return CoordenadasR2(p.x,p.y);
}

CoordenadasR2 Pelota::getCentro(){
	return CoordenadasR2(this->body->GetWorldCenter().x,this->body->GetWorldCenter().y);
}

Pelota::~Pelota(void)
{
}
