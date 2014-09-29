#include "NewElement.h"



NewElement::NewElement(Pelota * pelota){
	this->id = pelota->id;
	this->type = NEW_ELEMENT;
	this->color = pelota->color;
	this->tipo_figura = CIRCULO;
	this->radio = pelota->getRadio();
	this->vertices[0] = pelota->getCentro();
	this->vertices[1] = pelota->getPuntoReferencia();
}

NewElement::NewElement(Jugador * jugador){
	this->type = NEW_ELEMENT;
	this->id = jugador->id;
	this->tipo_figura = JUGADOR;
	this->alto = jugador->getSize().y;
	this->ancho = jugador->getSize().x;
	this->direccion = jugador->getDireccion();
}

NewElement::NewElement(Poligono * poligono){
	this->type = NEW_ELEMENT;
	this->id = poligono->id;
	this->color = poligono->color;
	this->tipo_figura = POLIGONO;
	this->lados = poligono->getVertexCount();
	std::vector<CoordenadasR2> aux_vec = poligono->getVertices();
	for (unsigned int i = 0; i < this->lados; i++)
		this->vertices[i] = aux_vec[i];
}

std::string NewElement::str(){
	std::string s = "[id figura=" + std::to_string((long long)this->id) + " tipo_figura=" + std::to_string((long long)this->tipo_figura) + "]"; //" alto=" + std::to_string((long long)this->alto) 
	return s;
}

NewElement::NewElement(void)
{
}



NewElement::~NewElement(void)
{
}
