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
	float angulo = 2 * b2_pi / lados;
	float vx,vy;
	int i = 0;

	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(x,y);
	bodyDef.angle=angulorot * b2_pi /180;
//	printf("bodyDef.position x: %f y: %f \n", bodyDef.position.x,bodyDef.position.y);
	b2Vec2 vertices[8]; 

	
	// http://stackoverflow.com/questions/3436453/calculate-coordinates-of-a-regular-polygons-vertices
	for (i=lados-1 ; i > -1; i--){
		    vx =  radio * cos(2*b2_pi*i/lados);
			vy =  radio * sin(2*b2_pi*i/lados);
			vertices[i].Set(vx,vy);
	}
//	for(int i=0; i<lados; i++)
//		printf("x: %f y: %f \n", vertices[i].x,vertices[i].y);
	
	shape.Set(vertices,lados);
	this->body = this->world->CreateBody(&bodyDef);
	fixtureDef.shape = (&shape);
	this->body->CreateFixture(&fixtureDef);
//	printf("Rotando alrededor de %f ; %f", this->body->GetWorldPoint(shape.m_centroid).x, this->body->GetWorldPoint(shape.m_centroid).y);
//	this->body->SetTransform(this->body->GetPosition(),angulorot* b2_pi /180);

}

unsigned int Poligono::getVertexCount(){
	b2PolygonShape * shape = (b2PolygonShape *)this->body->GetFixtureList()[0].GetShape();
	return shape->GetVertexCount();

}
 Poligono::~Poligono(void){
 }