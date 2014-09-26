#pragma once
#include "model\Pelota.h"
#include "model\CoordenadasR2.h"
class DatosCirculo
{
public:
	DatosCirculo(Pelota* pelota);
	void setPosicion(CoordenadasR2 centro);
	CoordenadasR2 getPosicion();
	float getRadio();
	int getId();
	~DatosCirculo(void);
private:
	float m_x;
	float m_y;
	int m_id;
	float m_radio;
	

};

