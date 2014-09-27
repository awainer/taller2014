#pragma once
#include "model\Pelota.h"
#include "model\CoordenadasR2.h"
#include "DatosFigura.h"
#include "../../net/NewElement.h"

class DatosCirculo: public DatosFigura
{
public:
	DatosCirculo(Pelota* pelota);
	DatosCirculo(NewElement* elem);
	CoordenadasR2 getPosicion();
	void setPosicion(CoordenadasR2  vertices[6]);
	float getRadio();

	~DatosCirculo(void);
private:
	float m_x;
	float m_y;
	int m_id;
	float m_radio;
	

};

