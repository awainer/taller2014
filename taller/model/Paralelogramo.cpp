#include "Paralelogramo.h"
#include "../EventLogger.h"
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <vector>


Paralelogramo::Paralelogramo(CoordenadasR2 centro,float longlado1, float longlado2, float angulo, Color color, int angulorot,bool dinamico,float masa,  b2World * world)
{
	this->world = world;
	float altura;

	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	b2PolygonShape shape;
	this->generateId();
	// Los lados siempre son 4
	CoordenadasR2 vertice1(0,0), vertice2(0,0), vertice3(0,0), vertice4(0,0);

	if (dinamico){
		bodyDef.type = b2_dynamicBody;
		this->type = STATIC_BODY;
	}
	else{
		bodyDef.type = b2_staticBody;
		this->type = DYNAMIC_BODY;
	}

	// http://www.calculatorsoup.com/calculators/geometry-plane/parallelogram.php
	//
	//              lado2
	//        V2 _____________ V3
	//          /  |         /
	//  lado1  /   | C      /  lado3
	//        /)&  | H     /
	//       /_)___|______/
	//      V1    lado4    V4
	//  

	bodyDef.position.Set(centro.x,centro.y);
	bodyDef.angle= this->normalizarAngulo(angulorot);
	b2Vec2 vertices[8]; 
	
	// resultado en radianes
	float anguloV1rad = this->normalizarAngulo(angulo);
	
	altura = longlado1 * sin(anguloV1rad);
	
	vertice1.y = -altura / 2;
	vertice4.y = vertice1.y;
	vertice2.y = altura / 2;
	vertice3.y = vertice2.y;
	
	float diferinfizq = sqrt ( pow(longlado1/2,2) - pow(altura/2,2));

	float diferinfder = diferinfizq;
	
	if (angulo < 90){
		vertice1.x = - (longlado2 / 2);
		vertice2.x = - (longlado2 / 2) + diferinfizq;
		vertice3.x = (longlado2 / 2) + diferinfder;
		vertice4.x = (longlado2 / 2);
	}
	else
	{
		vertice1.x = - (longlado2 / 2);
		vertice2.x = - (longlado2 / 2) - diferinfizq;
		vertice3.x = (longlado2 / 2) - diferinfder;
		vertice4.x = (longlado2 / 2);
	}

	// Paso los vertices en sentido anti-horario
	vertices[0].Set(vertice4.x,vertice4.y);
	vertices[1].Set(vertice3.x,vertice3.y);
	vertices[2].Set(vertice2.x,vertice2.y);
	vertices[3].Set(vertice1.x,vertice1.y);	

	shape.Set(vertices,4);
	
	this->body = this->world->CreateBody(&bodyDef);
	fixtureDef.shape = (&shape);
	this->body->CreateFixture(&fixtureDef); 
	this->setDensidad(masa);
	this->color = color;
	this->generateId();
	std::string msg = "Agregando pelota con id "  + EventLogger::itos(this->id);
	log(msg, DEBUG);

}


bool Paralelogramo::validarParametros(float longlado1, float longlado2, float angulo){
	if (longlado1 > 0){
		if (longlado2 > 0){
			if (angulo > 0) {
				if (angulo < 180){
					if (angulo != 90){
						return true;
					}
					else{
						log("El angulo del paralelogramo no puede ser 90",WARNING);
						return false;
					}
				}
				else {
					log("El angulo del paralelogramo debe ser un menor a 180",WARNING);
					return false;
				}
			}
			else{
				log("El angulo del paralelogramo debe ser un mayor a cero",WARNING);
				return false;
			}
		}
		else {
			log("La longitud de la base y el techo del paralelogramo debe ser un numero positivo",WARNING);
			return false;
		}
	}
	else {
		log("La longitud del lado 1 del paralelogramo debe ser un numero positivo",WARNING);
		return false;
	}
}


 Paralelogramo::~Paralelogramo(void){
 }