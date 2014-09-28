#pragma once
#include "../../model/CoordenadasR2.h"
#include "../../net/NewElement.h"
#include "../../constantes.h"
#include "../../model/Color.h"
#include <vector>
class DatosFigura
{
public:
	DatosFigura(void);
	void setPosicion(CoordenadasR2  vertices[6]);
	CoordenadasR2 getPosicion();
	~DatosFigura(void);
	int getId();
	Color color;
protected:
	std::vector<CoordenadasR2> m_vertices;
	int id;
};

