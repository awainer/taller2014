#include "Poligono.h"
#include <math.h>
#include <stdio.h>
#include <vector>

Poligono::Poligono(float x, float y, float radio, unsigned int lados, int angulorot, b2World * world)
{
	this->world = world;

	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	b2PolygonShape shape;
	
	float vx=x-radio;
	float vy=y;
	int i = 0;

	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(x,y);
	b2Vec2 vertices[8]; 

	float angulo = 2 * b2_pi / lados;
	// http://stackoverflow.com/questions/3436453/calculate-coordinates-of-a-regular-polygons-vertices
	for (i=lados-1 ; i > -1; i--){
		    vx = x + radio * cos(2*b2_pi*i/lados);
			vy = y + radio * sin(2*b2_pi*i/lados);
			vertices[i].Set(vx,vy);
	}
	for(int i=0; i<lados; i++)
		printf("x: %f y: %f \n", vertices[i].x,vertices[i].y);

	shape.Set(vertices,lados);
	shape.Validate();
	this->body = this->world->CreateBody(&bodyDef);
	this->body->SetTransform(this->body->GetWorldCenter(),angulorot* b2_pi /180);

	fixtureDef.shape = (&shape);
	this->body->CreateFixture(&fixtureDef);
	
}


 Poligono::~Poligono(void){
 }