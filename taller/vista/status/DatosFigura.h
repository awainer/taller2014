#pragma once
#include "../../model/CoordenadasR2.h"
#include "../../net/NewElement.h"

class DatosFigura
{
public:
	DatosFigura(void);
	void setPosicion(CoordenadasR2  vertices[6]);
	~DatosFigura(void);
	int getId();
};

