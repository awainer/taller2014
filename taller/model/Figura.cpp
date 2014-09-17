#include "Figura.h"
#include <iostream>
#include "../EventLogger.h"
Figura::Figura(void)
{
}

CoordenadasR2 Figura::getPosicion(){
	return CoordenadasR2(this->body->GetPosition().x, this->body->GetPosition().y);
}

int Figura::getType(){
	return this->type;
}
std::vector <CoordenadasR2> Figura::getVertices(){
	std::vector <CoordenadasR2>  result;
	b2Fixture * fix = this->body->GetFixtureList();
	b2PolygonShape * shape = (b2PolygonShape *) fix->GetShape();
	int vertexCount = shape->GetVertexCount();
	for(int i = 0; i< vertexCount; i++){
		b2Vec2 vert = this->body->GetWorldPoint(shape->GetVertex(i));
		result.push_back(CoordenadasR2(vert.x,vert.y));
	}
	return result;
	

}

// Setea la densidad del fixture para que la masa resultante sea la pasada por parametro
// esto solo funciona si  this->body ya tiene un fixture.
void Figura::setDensidad(float masa){
	b2MassData  m;
	b2Fixture * fix;
	fix = this->body->GetFixtureList(); 
	// Si la densidad del cuerpo es 1 kg/m**2 entonces la masa en magnitud es igual al area, o no?
	fix->SetDensity(1);
	fix->GetMassData(&m);
	float area = m.mass;
	fix->SetDensity(masa/area);
	this->body->ResetMassData();
	//std::cout << "Masa: " << masa << " area: "<< area << " densidad " << fix->GetDensity() << std::endl; 
}


b2Fixture * Figura::getFixture(){
	// Si hay mas de un fixture va a devolver el primer shape asociado, en general es lo que queremos.
	return this->body->GetFixtureList();
}


float Figura::normalizarAngulo(int angulo){
	float result = 0;
	if (angulo < 0 || angulo > 359){
		EventLogger::AgregarEvento("El angulo debe estar entre 0 y 359, se usa angulo 0.",WARNING);
		return result;
	}
	// Le tengo que restar 180 porque box2d maneja angulos normalizados entre -pi y pi.
	result = (angulo - 180)* b2_pi /180;
	EventLogger::AgregarEvento("El angulo " + to_string(long double(angulo)) + " normalizado en radianes resulta: " + to_string(long double(result)), DEBUG);
	return result;
}

bool Figura::seSolapaCon(Figura * otra){
	b2Shape * shape1 = this->getFixture()->GetShape();
	b2Shape * shape2 = otra->getFixture()->GetShape();
	return b2TestOverlap(shape1,
						0,
						shape2,
						0,
						this->getFixture()->GetBody()->GetTransform(),
						otra->getFixture()->GetBody()->GetTransform());

}
void Figura::activar(){
	this->body->GetFixtureList()->SetSensor(false);
}
Figura::~Figura(void)
{
	std::cout << "Lllamando destructor de figura" << std::endl;
	//this->world->DestroyBody(this->body);
	this->body->GetWorld()->DestroyBody(this->body);

}
int Figura::nextId = 0;
int Figura::generateId(){
	
	this->nextId++;
	this->id = this->nextId;
	return this->id;
}