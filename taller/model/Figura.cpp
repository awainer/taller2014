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

Figura::~Figura(void)
{
	this->world->DestroyBody(this->body);
}
