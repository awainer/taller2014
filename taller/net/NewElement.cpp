#include "NewElement.h"



NewElement::NewElement(Pelota * pelota){
	this->id = pelota->id;
	this->color = pelota->color;
	this->type = CIRCULO;
	this->radio = pelota->getRadio();
	this->vertices[0] = pelota->getCentro();
	this->vertices[1] = pelota->getPuntoReferencia();
}

NewElement::NewElement(Jugador * jugador){
	this->id = jugador->id;
	this->type = JUGADOR;
	this->alto = jugador->getSize().y;
	this->ancho = jugador->getSize().x;
	this->direccion = jugador->getDireccion();
}

NewElement::NewElement(Poligono * poligono){
	this->id = poligono->id;
	this->color = poligono->color;
	this->type = POLIGONO;
	this->lados = poligono->getVertexCount();
	std::vector<CoordenadasR2> aux_vec = poligono->getVertices();
	for (unsigned int i = 0; i < this->lados; i++)
		this->vertices[i] = aux_vec[i];
}

NewElement::NewElement(void)
{
}



NewElement::~NewElement(void)
{
}
