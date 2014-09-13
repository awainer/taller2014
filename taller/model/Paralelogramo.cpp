#include "Paralelogramo.h"
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <vector>


Paralelogramo::Paralelogramo(CoordenadasR2 centro,float longlado1, float longlado2, float altura, Color color, int angulorot,bool dinamico,float masa,  b2World * world)
{
	this->world = world;

	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	b2PolygonShape shape;
	this->generateId();
	// Los lados siempre son 4
	//float angulo = 2 * b2_pi / lados;
	CoordenadasR2 vertice1(0,0), vertice2(0,0), vertice3(0,0), vertice4(0,0);

	if (dinamico){
		bodyDef.type = b2_dynamicBody;
	}
	else
		bodyDef.type = b2_staticBody;

	// http://www.calculatorsoup.com/calculators/geometry-plane/parallelogram.php
	//
	//              lado2
	//        V2 _____________ V3
	//          /  |         /
	//  lado1  /   | C      /  lado3
	//        /    | H     /
	//       /_____|______/
	//      V1    lado4    V4
	//  
	//  angulo V1 = arcsin(H/lado1)
	//  p (diagonal V2 V4) = Raíz cuadrada(( lado1^2 + lado4^2 - 2 * lado1 * lado4 cos(angulo V1) ))
    //  q (diagonal V1 V3) = Raíz cuadrada(( lado1^2 + lado4^2 + 2 * lado1 * lado4 cos(angulo V1) )) -> esta no la estamos usando
	//  angulo V4 = 180° - angulo V1
	//  angulo V3 = angulo V1
	//  angulo V2 = angulo V4

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

	//  angulo V1 = arcsin(H/lado1)
	// resultado en radianes
	float anguloV1 = asin(altura/longlado1);

	//  p (diagonal V2 V4) = Raíz cuadrada(( lado1^2 + lado4^2 - 2 * lado1 * lado4 cos(angulo V1) ))
	float p = sqrt( pow(longlado1,2) + pow(longlado2,2) - 2 * longlado1 * longlado2 * cos(anguloV1) );
	
	// Sacar
	//std::cout << "p: " << p << std::endl;

	// Auxiliares para calcular los x para los vertices superiores e inferiores
	// Saco diferencia izquierda y derecha en base a suponer que la (altura/2) y la mitad de p
	float diferinfizq = sqrt ( pow(p/2,2) + pow(altura/2,2));

	// Sacar
	//std::cout << "diferinfizq: " << diferinfizq << std::endl;

	float diferinfder = longlado2 - diferinfizq;

	// Sacar
	//std::cout << "diferinfder: " << diferinfder << std::endl;
	vertice1.x = - diferinfizq;
	vertice2.x = - diferinfder;
	vertice3.x = diferinfizq;
	vertice4.x = diferinfder;


	// Sacar
	std::cout << "vertice1.x: " << vertice1.x + centro.x<< std::endl;
	std::cout << "vertice2.x: " << vertice2.x + centro.x<< std::endl;
	std::cout << "vertice3.x: " << vertice3.x + centro.x<< std::endl;
	std::cout << "vertice4.x: " << vertice4.x + centro.x<< std::endl;

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
}

/*
unsigned int Paralelogramo::getVertexCount(){
//	b2PolygonShape * shape = (b2PolygonShape *)this->body->GetFixtureList()[0].GetShape();
//	return shape->GetVertexCount();
	return 4;
}
*/

 Paralelogramo::~Paralelogramo(void){
 }