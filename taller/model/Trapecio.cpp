#include "Trapecio.h"
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "../EventLogger.h"


Trapecio::Trapecio(CoordenadasR2 centro,float longladoizq, float longtecho, float longladoder,  float altura, Color color, float angulorot,bool dinamico,float masa,  b2World * world)
{
	this->world = world;

	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	b2PolygonShape shape;
	// Los lados siempre son 4
	CoordenadasR2 vertice1(0,0), vertice2(0,0), vertice3(0,0), vertice4(0,0);

	if (dinamico){
		bodyDef.type = b2_dynamicBody;
		this->type = DYNAMIC_BODY;
	}
	else{
		bodyDef.type = b2_staticBody;
		this->type = STATIC_BODY;
	}

	
	/*          techo
	        V2 ________ V3
	          /|       |\
	ladoizq  / |   C   | \  ladoder
	        /  |H     H|  \
	       /___|_______|___\
	      V1     piso      V4
	*/
	// Sacar
	std::cout << "Centro.x: " << centro.x << " Centro.y: " << centro.y << std::endl;

	bodyDef.position.Set(centro.x,centro.y);
	bodyDef.angle= this->normalizarAngulo(angulorot);
	bodyDef.userData = (void*)this;
	b2Vec2 vertices[8]; 

	vertice1.y = -altura / 2;
	vertice4.y = vertice1.y;
	vertice2.y = altura / 2;
	vertice3.y = vertice2.y;
	/*
	// Sacar
	std::cout << "vertice1.y: " << vertice1.y << std::endl;
	std::cout << "vertice2.y: " << vertice2.y << std::endl;
	std::cout << "vertice3.y: " << vertice3.y << std::endl;
	std::cout << "vertice4.y: " << vertice4.y<< std::endl;
	*/
	float longadicizq, longadicder;
	/*
	// Trapecio Rectángulo
	if (longladoizq == altura){
		vertice1.x = - (longtecho / 2);
		vertice2.x = - (longtecho / 2);
		
		//Calculo el adicional del piso del lado derecho con pitágoras
		longadicder = sqrt( pow(longladoder,2) - pow(altura,2));
		
		vertice3.x = (longtecho / 2);
		vertice4.x = ((longtecho / 2) + longadicder);
	}
	// Trapecio Isósceles y Escaleno
	else{
		//Calculo el adicional del piso del lado izquierdo con pitágoras
		longadicder = sqrt( pow(longladoizq,2) - pow(altura,2));

		vertice1.x = - (longtecho / 2);
		vertice2.x = - ((longtecho / 2) + longadicizq);
		
		//Calculo el adicional del piso del lado derecho con pitágoras
		longadicder = sqrt( pow(longladoder,2) - pow(altura,2));
		
		vertice3.x = (longtecho / 2);
		vertice4.x = ((longtecho / 2) + longadicder);
	}
	*/

		//Calculo el adicional del piso del lado izquierdo con pitágoras
		longadicizq = sqrt( pow(longladoizq,2) - pow(altura,2));

		//Calculo el adicional del piso del lado derecho con pitágoras
		longadicder = sqrt( pow(longladoder,2) - pow(altura,2));

		float longpiso = longtecho + longadicder + longadicizq;

		vertice1.x = - (longpiso / 2);
		vertice2.x = (-longpiso / 2) + longadicizq;
		vertice3.x = (longpiso / 2) - longadicder;
		vertice4.x = (longpiso / 2);

	/*
	// Sacar
	std::cout << "vertice1.x: " << vertice1.x << std::endl;
	std::cout << "vertice2.x: " << vertice2.x << std::endl;
	std::cout << "vertice3.x: " << vertice3.x << std::endl;
	std::cout << "vertice4.x: " << vertice4.x << std::endl;
	*/
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
	this->generateId();
	std::string msg =	"Agregando Trapecio con id "  + EventLogger::itos(this->id) + " angulo rot: " + to_string(long long (this->body->GetAngle()));
	EventLogger::AgregarEvento(msg, DEBUG);
}


bool Trapecio::validarParametros(float longladoizq, float longtecho, float longladoder,  float altura){
	if (longladoizq > 0){
		if (longtecho > 0){
			if (longladoder > 0){
				if (altura > 0) {
					return validarDimensiones(longladoizq, longtecho, longladoder, altura);
				}
				else {
					EventLogger::AgregarEvento("La altura del Trapecio debe ser un numero positivo",WARNING);
					return false;
				}
			}
			else{
				EventLogger::AgregarEvento("La longitud del lado derecho del Trapecio debe ser un numero positivo",WARNING);
				return false;
			}
		}
		else {
			EventLogger::AgregarEvento("La longitud del techo del trapecio debe ser un numero positivo",WARNING);
			return false;
		}
	}
	else {
		EventLogger::AgregarEvento("La longitud del izquierdo del Trapecio debe ser un numero positivo",WARNING);
		return false;
	}
}



bool Trapecio::validarDimensiones(float longladoizq, float longtecho, float longladoder,  float altura){
	if ((longladoder < altura) || (longladoizq < altura)){
		EventLogger::AgregarEvento("Los lados izquierdo y derecho de un trapecio no pueden ser menores a la altura",WARNING);
		return false;
	}
	
	if ((longladoizq == longladoder) && (longladoizq == altura)){
		EventLogger::AgregarEvento("Al menos 1 de las 2 longitudes de los lados deben ser mayores a la altura de un trapecio",WARNING);
		return false;
	}
	else {
		return true;
	}

}

 Trapecio::~Trapecio(void){
 }