#include "DatosFigura.h"


DatosFigura::DatosFigura(void)
{
}




int DatosFigura::getId(){
	return this->id;
}

void DatosFigura::update(NewPosition * elem){
	this->setPosicion(elem->vertices);
}

void DatosFigura::setPosicion(CoordenadasR2 vertices[6]){
	this->m_vertices.clear();
	for (unsigned int i=0; i < MAX_VERTICES; i++ ){
		this->m_vertices.push_back(vertices[i]);
		//this->m_vertices[i].x = vertices[i].x;
		//this->m_vertices[i].y=vertices[i].y;
	}
		
}

void DatosFigura::iniciarVertices(){
	for (unsigned int i=0; i < MAX_VERTICES; i++ ){
		this->m_vertices.push_back(CoordenadasR2(0,0));
	}
}

CoordenadasR2 DatosFigura::getPosicion(){
	return this->m_vertices[0];
}
DatosFigura::~DatosFigura(void)
{

}
