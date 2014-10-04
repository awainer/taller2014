#pragma once
#include <map>
#include "VistaFigura.h"
#include "../net/NewPosition.h"
#include "../net/NewElement.h"
#include "status\DatosFigura.h"
#include "status\DatosCirculo.h"
#include "status\DatosPoligono.h"
#include "status\DatosJugador.h"
#include "VistaEscenario.h"


class PositionHandler
{
public:
	PositionHandler(void);
	PositionHandler(VistaEscenario* escenario);
	~PositionHandler(void);
	void updateData(NewPosition *pos);
	void addData(NewElement *data);
private:
	std::map<int, DatosFigura*> data;
	VistaEscenario* m_escenario;
};

