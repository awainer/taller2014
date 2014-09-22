#include "Poligono.h"
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <vector>
#include "../EventLogger.h"

Poligono::Poligono(){
}

Poligono::Poligono(CoordenadasR2 centro, Color color, float radio, unsigned int lados, int angulorot,bool dinamico,float masa,  b2World * world)
{
	this->world = world;

	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	b2PolygonShape shape;
	float angulo = 2 * b2_pi / lados;
	float vx,vy;
	int i = 0;
	if (dinamico){
		bodyDef.type = b2_dynamicBody;
		this->type = DYNAMIC_BODY;

	}
	else{
		bodyDef.type = b2_staticBody;
		this->type = STATIC_BODY;
	}

	
	bodyDef.position.Set(centro.x,centro.y);
	bodyDef.angle = this->normalizarAngulo(angulorot);
	bodyDef.userData = (void*)this;
	b2Vec2 vertices[8]; 
	
	// http://stackoverflow.com/questions/3436453/calculate-coordinates-of-a-regular-polygons-vertices
	for (i=lados-1 ; i > -1; i--){
		    vx =  radio * cos(2*b2_pi*i/lados);
			vy =  radio * sin(2*b2_pi*i/lados);
			vertices[i].Set(vx,vy);
	}
	
	shape.Set(vertices,lados);
	
	this->body = this->world->CreateBody(&bodyDef);
	fixtureDef.friction=0.1f;
	fixtureDef.shape = (&shape);
	this->body->CreateFixture(&fixtureDef); 
	this->setDensidad(masa);
	this->color = color;
	this->generateId();
	std::string msg =	"Agregando poligono con id "  + EventLogger::itos(this->id);
	log(msg, DEBUG);

}


bool Poligono::validarParametros(unsigned int lados, float radio){
	if (lados <= 2 || lados > 6){
		log("Los poligonos admiten entre 3 y 6 lados",WARNING);
		return false;
	}
	
	if ( radio < 0 ){
		log("El radio debe ser un numero positivo",WARNING);
		return false;
	}

	return true;
}
unsigned int Poligono::getVertexCount(){
	b2PolygonShape * shape = (b2PolygonShape *)this->body->GetFixtureList()[0].GetShape();
	return shape->GetVertexCount();

}
Poligono::~Poligono(void){
//	std::cout << "Destructor poligono" << std::endl;
//	this->body->GetWorld()->DestroyBody(this->body);


}