#include "Figura.h"


Figura::Figura(void)
{
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

}

Figura::~Figura(void)
{
	this->world->DestroyBody(this->body);
}
