#include "Figura.h"


Figura::Figura(void)
{
}

std::vector <CoordenadasR2> Figura::getVertices(){
	std::vector <CoordenadasR2>  result;
	b2PolygonShape * shape = (b2PolygonShape *)this->body->GetFixtureList();
	for(int i = 0; i< shape->GetVertexCount(); i++)
		result.push_back(CoordenadasR2(shape->GetVertex(i).x,shape->GetVertex(i).y));
	return result;
	

}

Figura::~Figura(void)
{
	this->world->DestroyBody(this->body);
}
