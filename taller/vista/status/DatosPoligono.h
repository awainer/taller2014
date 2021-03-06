#pragma once
#pragma once
#include "model\Poligono.h"
#include "model\CoordenadasR2.h"
#include "DatosFigura.h"
#include <vector>

class DatosPoligono: public DatosFigura
{
public:
	DatosPoligono(Poligono* poligono);
	DatosPoligono(NewElement* poligono);
	std::vector<CoordenadasR2>  getVertices();
	int getVertexCount();
	int getId();
	~DatosPoligono(void);
private:
	unsigned int n_vertices;
};

