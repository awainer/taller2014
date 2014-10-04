#pragma once
#include "packet.h"
#include "../model/CoordenadasR2.h"
class NewPosition :
	public Packet
{
public:
	NewPosition(void);
	~NewPosition(void);
	unsigned int id_figura;
	unsigned int tipo_figura;
	CoordenadasR2 vertices[6];
	unsigned int direccion;
};

