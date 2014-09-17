#include "model\Escenario.h"
#include "model\Pelota.h"
#include "model\CoordenadasR2.h"
#include "model\Color.h"


void pruebaSuper(){

	Escenario * esc = new Escenario(10,10,CoordenadasR2(0,-10),"",NULL);
	esc->agregarPelota(CoordenadasR2(1,1),0.49f,Color(9,9,9),false,1);
	esc->agregarPelota(CoordenadasR2(1,2),0.5f,Color(9,9,9),false,1);
	//esc->agregarPoligono(CoordenadasR2(4,1),1.45,5,0,Color(1,1,1),false,4);
	//esc->agregarPoligono(CoordenadasR2(4,1),1.45,5,359,Color(1,1,1),false,4);
	//esc->agregarPoligono(CoordenadasR2(4,1),1.45,5,90,Color(1,1,1),false,4);
	/*list<Figura*> l = esc->getPelotas();
	list<Figura*> k = esc->getPoligonos();
	Figura * f1 = *(l.begin());
	Figura * f2 = *(k.begin());

	bool s = f1->seSolapaCon(f2);
	*/
	delete esc;
}