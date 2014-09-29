#include "PositionHandler.h"


PositionHandler::PositionHandler(void)
{
}
PositionHandler::PositionHandler(VistaEscenario* escenario){
	this->m_escenario = escenario;
}

void PositionHandler::addData(NewElement * data){
	TipoFigura tipo  = data->tipo_figura;
	DatosFigura * nuevoDatosFigura =NULL;
	switch(tipo){
		case JUGADOR: 
			nuevoDatosFigura = new DatosJugador(data);
			this->m_escenario->agregarJugador((DatosJugador*)nuevoDatosFigura);
			break;
		case CIRCULO: 
			nuevoDatosFigura = new DatosCirculo(data);
			this->m_escenario->agregarPelota((DatosCirculo*)nuevoDatosFigura);
			break;
		case POLIGONO: 
			nuevoDatosFigura = new DatosPoligono(data);
			this->m_escenario->agregarPoligonos((DatosPoligono*)nuevoDatosFigura);
			break;
		default: break;
	}

	this->data.insert(std::pair<int,DatosFigura*>(nuevoDatosFigura->getId(),nuevoDatosFigura));
}

void PositionHandler::updateData(NewPosition * pos){
	DatosFigura * datos = this->data[ pos->id_figura ];
	datos->update(pos);
}

PositionHandler::~PositionHandler(void)
{
	this->data.clear();
}
