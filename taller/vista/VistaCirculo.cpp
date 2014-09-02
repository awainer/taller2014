#include "VistaCirculo.h"
#include <math.h>

#define PI 3.14159265

VistaCirculo::VistaCirculo(float radio, Uint32 color, SDL_Renderer* gRenderer )
{
	m_radio = radio;
	m_color = color;
	m_renderer = gRenderer;
}

void VistaCirculo::render(int x,int y, int rotacion, float escala){
	m_x = x;
	m_y = y;
	int ret = filledCircleColor(m_renderer, m_x, m_y, m_radio * escala, m_color);
	double res_cos, res_sin;
    res_cos = cos ( rotacion * PI / 180.0 );
    res_sin = sin ( rotacion * PI / 180.0 );
    Uint32 colorTemp = 0xFF000FF0; // deberia ser un color mas oscuro que el propio de la figura
    int a_x, a_y;
    a_x = m_radio * res_sin * escala;
    a_y = m_radio * res_cos * escala;
    int ret2 = lineColor(m_renderer, m_x, m_y, m_x + a_x, m_y - a_y, colorTemp);
}

VistaCirculo::~VistaCirculo(void)
{
}
