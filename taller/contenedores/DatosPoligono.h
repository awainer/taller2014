#pragma once
#pragma once
#include "model\Poligono.h"
#include "model\CoordenadasR2.h"
#include <vector>

class DatosPoligono
{
public:
	DatosPoligono(Poligono* poligono);
	void setVertices(std::vector<CoordenadasR2>  vertices);
	std::vector<CoordenadasR2>  getVertices();
	int getVertexCount();
	int getId();
	~DatosPoligono(void);
private:
	int n_vertices;
	std::vector<CoordenadasR2> m_vertices;
	int id;
};

