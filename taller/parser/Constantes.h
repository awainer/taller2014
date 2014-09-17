#pragma once

#include <list>
#include <string>
#include <sstream> 

using namespace std;


struct colorRGB {
  int r;
  int g;
  int b; 
};

struct StObjeto {
		string tipo;
		float x;
		float y;
		float ancho;
		float alto;
		colorRGB color;
		int rot;
		float masa;
		bool estatico;
};


struct rect {
		string tipo;
		float x;
		float y;
		float ancho;
		float alto;
		colorRGB color;
		int rot;
		float masa;
		bool estatico;
};

struct paralel {
		string tipo;
		float x;
		float y;
		float lado1;
		float lado2;
		float altura;
		colorRGB color;
		int rot;
		float masa;
		bool estatico;
};

struct trap {
		string tipo;
		float x;
		float y;
		float lado1;
		float lado2;
		float lado3;
		float altura;
		colorRGB color;
		int rot;
		float masa;
		bool estatico;
};

struct circ {
		string tipo;
		float radio;
		float x;
		float y;			
		colorRGB color;		
		float masa;
		bool estatico;
};



struct poli {
		string tipo;
		int lados;
		float x;
		float y;
		float escala;		
		colorRGB color;
		int rot;
		float masa;
		bool estatico;
};


struct StEscenario {
	  float altopx;
	  float anchopx;
	  float altoun;
	  float anchoun;
	  string imagen_fondo;
	  float personajeX;
	  float personajeY;

	  list <rect> rectangulos;	
	  list <poli> poligonos;
	  list <circ> circulos;
	  list <paralel> paralelogramos;
	  list <trap> trapecios;
};

typedef char 	Char; 
typedef const Char * 	Location;

#define IMAGEN_DEFAULT "imagenes/default.jpg"

#define ALTO_PX_DEFAULT 100
#define ANCHO_PX_DEFAULT 100

#define ALTO_UN_DEFAULT 50
#define ANCHO_UN_DEFAULT 50

#define PERSONAJE_X_DEFAULT 10
#define PERSONAJE_Y_DEFAULT 10

#define POLIGONO_X_DEFAULT 5
#define POLIGONO_Y_DEFAULT 5
#define POLIGONO_LADOS_DEFAULT 3
#define POLIGONO_ESCALA_DEFAULT 5
#define POLIGONO_ROT_DEFAULT 0
#define POLIGONO_MASA_DEFAULT 15
#define POLIGONO_ESTATICO_DEFAULT 0

#define RECTANGULO_X_DEFAULT 5
#define RECTANGULO_Y_DEFAULT 5
#define RECTANGULO_ANCHO_DEFAULT 5
#define RECTANGULO_ALTO_DEFAULT 5
#define RECTANGULO_ROT_DEFAULT 0
#define RECTANGULO_MASA_DEFAULT 15
#define RECTANGULO_ESTATICO_DEFAULT 0


#define PARALELOGRAMO_X_DEFAULT 5
#define PARALELOGRAMO_Y_DEFAULT 5

#define PARALELOGRAMO_LONGLADO1_DEFAULT 5
#define PARALELOGRAMO_LONGLADO2_DEFAULT 5
#define PARALELOGRAMO_ALTURA_DEFAULT 5

#define PARALELOGRAMO_ROT_DEFAULT 0
#define PARALELOGRAMO_MASA_DEFAULT 15
#define PARALELOGRAMO_ESTATICO_DEFAULT 0



#define TRAPECIO_X_DEFAULT 5
#define TRAPECIO_Y_DEFAULT 5

#define TRAPECIO_LONGLADO1_DEFAULT 5
#define TRAPECIO_LONGLADO2_DEFAULT 5
#define TRAPECIO_LONGLADO3_DEFAULT 5
#define TRAPECIO_ALTURA_DEFAULT 5

#define TRAPECIO_ROT_DEFAULT 0
#define TRAPECIO_MASA_DEFAULT 15
#define TRAPECIO_ESTATICO_DEFAULT 0


#define CIRCULO_X_DEFAULT 5
#define CIRCULO_Y_DEFAULT 5
#define CIRCULO_RADIO_DEFAULT 0.4f
#define CIRCULO_MASA_DEFAULT 15
#define CIRCULO_ESTATICO_DEFAULT 0

#define R_DEFAULT 5
#define G_DEFAULT 5
#define B_DEFAULT 5

