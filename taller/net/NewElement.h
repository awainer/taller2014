#pragma once
#include "Packet.h"
#include "../constantes.h"
#include "../model/CoordenadasR2.h"
#include "../model/Color.h"

class NewElement :
	public Packet
{
public:
	NewElement(void);
	~NewElement(void);
	unsigned int id, lados;
	TipoFigura tipo;
	CoordenadasR2 vertices[6];
	Color color;
	float radio,alto,ancho;
	int direccion;
	
};

