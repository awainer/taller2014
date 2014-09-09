#include "Trapecio.h"
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <vector>


Trapecio::Trapecio(CoordenadasR2 centro,float longpiso, float longtecho, float altura, Color color, int angulorot,bool dinamico,float masa,  b2World * world)
{
	this->world = world;

	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	b2PolygonShape shape;
	// Los lados siempre son 4
	//float angulo = 2 * b2_pi / lados;
	CoordenadasR2 vertice1(0,0), vertice2(0,0), vertice3(0,0), vertice4(0,0);

	if (dinamico){
		bodyDef.type = b2_dynamicBody;
	}
	else
		bodyDef.type = b2_staticBody;

	
	/*          techo
	        V2 ________ V3
	          /  |     \
	  lado1  /   | C    \  lado3
	        /    | H     \
	       /_____|________\
	      V1    piso       V4
	*/
	// Sacar
	std::cout << "Centro.x: " << centro.x << " Centro.y: " << centro.y << std::endl;

	bodyDef.position.Set(centro.x,centro.y);
	bodyDef.angle=angulorot * b2_pi /180;
	b2Vec2 vertices[8]; 

	vertice1.y = -altura / 2;
	vertice4.y = vertice1.y;
	vertice2.y = altura / 2;
	vertice3.y = vertice2.y;

	// Sacar
	std::cout << "vertice1.y: " << vertice1.y + centro.y << std::endl;
	std::cout << "vertice2.y: " << vertice2.y + centro.y << std::endl;
	std::cout << "vertice3.y: " << vertice3.y + centro.y << std::endl;
	std::cout << "vertice4.y: " << vertice4.y + centro.y << std::endl;


	vertice1.x = - (longpiso / 2);
	vertice2.x = - (longtecho / 2);
	vertice3.x = + (longtecho / 2);
	vertice4.x = + (longpiso / 2);

	// Sacar
	std::cout << "vertice1.x: " << vertice1.x + centro.x<< std::endl;
	std::cout << "vertice2.x: " << vertice2.x + centro.x<< std::endl;
	std::cout << "vertice3.x: " << vertice3.x + centro.x<< std::endl;
	std::cout << "vertice4.x: " << vertice4.x + centro.x<< std::endl;

	// Paso los vertices en sentido anti-horario
	vertices[3].Set(vertice1.x,vertice1.y);
	vertices[2].Set(vertice2.x,vertice2.y);
	vertices[1].Set(vertice3.x,vertice3.y);
	vertices[0].Set(vertice4.x,vertice4.y);

	shape.Set(vertices,4);
	
	this->body = this->world->CreateBody(&bodyDef);
	fixtureDef.shape = (&shape);
	this->body->CreateFixture(&fixtureDef); 
	this->setDensidad(masa);
	this->color = color;
}


 Trapecio::~Trapecio(void){
 }