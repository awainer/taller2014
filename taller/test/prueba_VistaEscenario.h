#include <string>
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include "..\vista\VistaCirculo.h"
#include "..\vista\VistaPoligono.h"
#include "..\model\CoordenadasR2.h"
#include "..\model\Escenario.h"
#include "..\model\Poligono.h"
#include "..\model\Color.h"
#include "vista\VistaEscenario.h"
#include "vista\DatosPantalla.h"
#include "control\ControladorJugador.h"
#include "../contenedores/DatosCirculo.h"
#include "../contenedores/DatosPoligono.h"

#include <vld.h>
int  prueba_vistaEscenario(){
	Color  rojo = Color(255,0,0);
	Color  azul = Color(0,0,255);
	Color  verde = Color(0,255,0);
	Color violeta = Color(100,100,0);
	SDL_Event evento;
//	SDL_Scancode sc;
	bool juegoEnMarcha = true;
	//creo la pantalla
	Escenario * esc = new Escenario(10.0f, 10.0f,CoordenadasR2(0.0f,-10.0f),std::string("pathfondo"),NULL);
	
	// cambio de escala segun Box2D a SDL, necesaria para dibujar en el pixel correcto
	//float xratio = 640 / 6.4f;
	//float yratio = 480 / 4.8f;
	DatosPantalla datos = DatosPantalla(800,800,10.0f,10.0f);
	//esc->agregarPelota(  CoordenadasR2(4,4),0.5,azul,true,1);
	//esc->agregarPoligono(CoordenadasR2(4,2),1,5,0,rojo,false,2);
	esc->agregarPoligono(CoordenadasR2(6,1),1,5,90,verde,false,2);
	//esc->agregarPelota(  CoordenadasR2(2,2),0.2,verde,true,1);
	//esc->agregarPelota(  CoordenadasR2(1,0),0.2,violeta,true,1);
	//esc->agregarPelota(  CoordenadasR2(1,0),4.3,azul,true,6);
	//esc->agregarRectangulo(CoordenadasR2(1.5,2),1,1.9,50,rojo,true,0.05);
	//esc->agregarPoligono(CoordenadasR2(1.5,2),1.5,4,90,verde,true,2);
	esc->agregarJugador(CoordenadasR2(4.0f,2.0f));
	//Pelota* pelota_esc = (Pelota*)(*(esc->getPelotas().begin()));
	//DatosCirculo* datos_pelota = new DatosCirculo((Pelota*)(*(esc->getPelotas().begin())));
	Poligono* poligono = (Poligono*)(*(esc->getPoligonos().begin()));
	DatosPoligono* datos_poligono = new DatosPoligono((Poligono*)(*(esc->getPoligonos().begin())));
	//creo vista del escenario
	VistaEscenario escenario_vista = VistaEscenario(esc,&datos);
	Jugador* jugador = *(esc->getJugadores().begin());
	escenario_vista.agregarJugador(jugador);
	
	//escenario_vista.agregarPelota(datos_pelota);
	//escenario_vista.agregarPoligonos(datos_poligono);
	escenario_vista.agregarFondo("imagenes/homero.png");
	ControladorJugador control_jugador = ControladorJugador(jugador);
	
	while( juegoEnMarcha ){
					
		//Dibujo figuras
		datos_poligono->setVertices(poligono->getVertices());
		escenario_vista.mostrar();
		
		control_jugador.actualizar();
		SDL_PollEvent( &evento);
		esc->step();
		//datos_pelota->setPosicion(pelota_esc->getCentro());
		//datos_poligono->setVertices(poligono->getVertices());
		SDL_Delay(20);
		switch(evento.type)
		{
		case SDL_QUIT:
			juegoEnMarcha= false;
			break;
		}
	}

	delete esc;
	delete datos_poligono;
	return 0;
}