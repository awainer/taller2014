#include "Pelota.h"
#include <iostream>
#include "../EventLogger.h"

Pelota::Pelota(CoordenadasR2 centro, Color color,float radio,bool dinamica,float masa, b2World * world){
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	b2CircleShape shape;

	this->world = world;
	shape.m_radius = radio;
	shape.m_p.Set(0,0); // respecto del body

	this->generateId();
	std::string msg =	"Agregando pelota con id "  + EventLogger::itos(this->id);
	log(msg, DEBUG);

	bodyDef.position.Set(centro.x,centro.y);
	if (dinamica){
		bodyDef.type = b2_dynamicBody;
		fixtureDef.density = 1.2f;
		fixtureDef.restitution = 0.7f;
		fixtureDef.friction = 0.3f;
		this->type = DYNAMIC_BODY;
	}else{
		bodyDef.type = b2_staticBody;
		this->type = STATIC_BODY;
	}

	bodyDef.userData = (void*)this;
	fixtureDef.shape = &shape;
	fixtureDef.isSensor = false;
	//fixtureDef.userData = (void*)this;
	this->body = this->world->CreateBody(&bodyDef);
	this->body->CreateFixture(&fixtureDef);
	this->setDensidad(masa);
	this->color = color;
	

	
}

float Pelota::getRadio(){
	b2CircleShape * circle = (b2CircleShape * )(this->body->GetFixtureList()->GetShape());
	return circle->m_radius;
}

CoordenadasR2 Pelota::getPuntoReferencia(){
	b2CircleShape * shape = (b2CircleShape *)(this->body->GetFixtureList()->GetShape());
	b2Vec2 p = this->body->GetWorldPoint(b2Vec2(0.0f, 0.75f *shape->m_radius));
		return CoordenadasR2(p.x,p.y);
}

CoordenadasR2 Pelota::getCentro(){
	return CoordenadasR2(this->body->GetWorldCenter().x,this->body->GetWorldCenter().y);
}

bool Pelota::validarParametros(float radio){
	if (radio > 0)
		return true;
	log("El radio de los circulos debe ser un numero positivo",WARNING);
	return false;
}
Pelota::~Pelota(void){
//	std::cout << "Destructor pelota" << std::endl;
	//this->body->GetWorld()->DestroyBody(this->body);
}