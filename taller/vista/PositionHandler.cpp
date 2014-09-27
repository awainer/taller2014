#include "PositionHandler.h"


PositionHandler::PositionHandler(void)
{
}


void PositionHandler::addData(NewElement * data){
	TipoFigura tipo  = data->tipo;
	DatosFigura * nuevoDatosFigura =NULL;
	switch(tipo){
		case JUGADOR: nuevoDatosFigura = new DatosJugador(data);
			break;
		case CIRCULO: nuevoDatosFigura = new DatosCirculo(data);
			break;
		case POLIGONO: nuevoDatosFigura = new DatosPoligono(data);
			break;
		default: break;
	}

	this->data.insert(std::pair<int,DatosFigura*>(nuevoDatosFigura->getId(),nuevoDatosFigura));
}



PositionHandler::~PositionHandler(void)
{
}
