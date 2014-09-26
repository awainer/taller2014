#include "DatosPoligono.h"


DatosPoligono::DatosPoligono(Poligono* poligono)
{
	this->n_vertices = poligono->getVertexCount();
	std::vector<CoordenadasR2> vertices = poligono->getVertices();
	for(unsigned int i=0; i<n_vertices ;i++){
		m_vertices.push_back( CoordenadasR2(vertices[i].x,vertices[i].y));
	}
	
}

void DatosPoligono::setVertices(std::vector<CoordenadasR2>  vertices){
	for(unsigned int i=0; i<vertices.size() ;i++){
		m_vertices[i].x = vertices[i].x;
		m_vertices[i].y = vertices[i].y;
	}
}
std::vector<CoordenadasR2>  DatosPoligono::getVertices(){
	return m_vertices;
}
int  DatosPoligono::getVertexCount(){
	return n_vertices;
}

int DatosPoligono::getId(){
	return 1;
}

DatosPoligono::~DatosPoligono(void)
{
	m_vertices.clear();
}
