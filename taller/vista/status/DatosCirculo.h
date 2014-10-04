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
	CoordenadasR2 getPuntoReferencia();
	float getRadio();

	~DatosCirculo(void);
private:
	float m_radio;
};

