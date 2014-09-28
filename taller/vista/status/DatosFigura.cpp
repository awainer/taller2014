#include "DatosFigura.h"


DatosFigura::DatosFigura(void)
{
}

int DatosFigura::getId(){
	return 1;
}

void DatosFigura::setPosicion(CoordenadasR2 vertices[6]){
	for (unsigned int i=0; i < MAX_VERTICES; i++ )
		this->m_vertices[i]=vertices[i];
}

CoordenadasR2 DatosFigura::getPosicion(){
	return this->m_vertices[0];
}
DatosFigura::~DatosFigura(void)
{

}
