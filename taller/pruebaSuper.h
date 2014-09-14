#include "model\Escenario.h"
#include "model\Pelota.h"
#include "model\CoordenadasR2.h"
#include "model\Color.h"


void pruebaSuper(){

	Escenario * esc = new Escenario(10,10,CoordenadasR2(0,-10),"",NULL);
	esc->agregarPelota(CoordenadasR2(1,1),1,Color(9,9,9),true,1);
	esc->agregarPoligono(CoordenadasR2(2,1),1.5,5,0,Color(1,1,1),true,4);



	delete esc;
}