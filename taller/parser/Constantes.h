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
		int x;
		int y;
		int ancho;
		int alto;
		colorRGB color;
		int rot;
		int masa;
		bool estatico;
};


struct rect {
		string tipo;
		int x;
		int y;
		int ancho;
		int alto;
		colorRGB color;
		int rot;
		int masa;
		bool estatico;
};

struct circ {
		string tipo;
		int radio;
		int x;
		int y;			
		colorRGB color;		
		int masa;
		bool estatico;
};



struct poli {
		string tipo;
		int lados;
		int x;
		int y;
		float escala;		
		colorRGB color;
		int rot;
		int masa;
		bool estatico;
};


struct StEscenario {
	  int altopx;
	  int anchopx;
	  int altoun;
	  int anchoun;
	  string imagen_fondo;
	  int personajeX;
	  int personajeY;

	  list <rect> rectangulos;	
	  list <poli> poligonos;
	  list <circ> circulos;
};

typedef char 	Char; 
typedef const Char * 	Location;

#define IMAGEN_DEFAULT "default.png"

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


#define CIRCULO_X_DEFAULT 5
#define CIRCULO_Y_DEFAULT 5
#define CIRCULO_RADIO_DEFAULT 3
#define CIRCULO_MASA_DEFAULT 15
#define CIRCULO_ESTATICO_DEFAULT 0

#define R_DEFAULT 5
#define G_DEFAULT 5
#define B_DEFAULT 5

