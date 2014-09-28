#include "DatosPoligono.h"

DatosPoligono::DatosPoligono(NewElement* elem){
	this->iniciarVertices();
	this->setPosicion(elem->vertices);
	this->color = elem->color;
	this->id = elem->id;
	this->n_vertices = elem->lados;
}

DatosPoligono::DatosPoligono(Poligono* poligono)
{
	this->n_vertices = poligono->getVertexCount();
	std::vector<CoordenadasR2> vertices = poligono->getVertices();
	for(unsigned int i=0; i<n_vertices ;i++){
		m_vertices[i]=  CoordenadasR2(vertices[i].x,vertices[i].y);
	}
	
}

std::vector<CoordenadasR2>  DatosPoligono::getVertices(){
	return this->m_vertices;
}

int  DatosPoligono::getVertexCount(){
	return n_vertices;
}


DatosPoligono::~DatosPoligono(void)
{
}
