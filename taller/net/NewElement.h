#pragma once
#include "Packet.h"
#include "../constantes.h"
#include "../model/CoordenadasR2.h"
#include "../model/Color.h"
#include "../model/Pelota.h"
#include "../model/Jugador.h"
#include "../model/Poligono.h"
#include <string>
class NewElement :
	public Packet
{
public:
	NewElement(void);
	NewElement(Pelota * pelota);
	NewElement(Jugador * jugador);
	NewElement(Poligono * poligono);
	~NewElement(void);
	unsigned int id, lados;
	TipoFigura tipo_figura;
	CoordenadasR2 vertices[6];
	Color color;
	float radio,alto,ancho;
	int direccion;
	std::string str();
};

