#pragma once
class DatosPantalla
{
public:
	DatosPantalla(int ancho_pixeles, int alto_pixeles, float ancho_metros, float alto_metros);

	float getXratio();
	float getYratio();
	int getAnchoPixel();
	int getAltoPixel();
	~DatosPantalla(void);
private:
	int m_ancho_px;
	int m_alto_px;
	float m_ancho_mt;
	float m_alto_mt;

};

