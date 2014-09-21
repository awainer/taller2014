#pragma once
#include <json/json.h>

#include <stdio.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 
#include "../model/Escenario.h"
#include "Constantes.h"
#include "vista\VistaEscenario.h"
#include "vista\DatosPantalla.h"

using namespace std;

class Parser
{
private:
	StEscenario miEscenario;
	string jsonpath;
	float parsearElementoFloatUnsigned(Json::Value elem, float defaultVal,string nombreElem);
	float parsearElementoFloatPositivo(Json::Value elem, float defaultVal,string nombreElem);
	float parsearElementoIntPositivo(Json::Value elem, int defaultVal,string nombreElem);
	string parsearImagen(Json::Value elem, string defaultVal,string nombreElem);
	bool parsearBoolean(Json::Value elem, bool defaultVal, string nombreElem);
	poli parsearPoligono(Json::Value elem);
	rect parsearRectangulo(Json::Value elem);
	circ parsearCirculo(Json::Value elem);
	colorRGB parsearColor(Json::Value elem, colorRGB defaultVal, string nombreElem);
	unsigned int parsearAngulo(Json::Value elem, unsigned int defaultVal, string nombreElem);

public:
	Parser(string path);
	Parser(void);
	~Parser(void);
	void Inicializar();
	Escenario * CrearObjetos();
	void CargarDefault();
	VistaEscenario * CrearVista();
	DatosPantalla CargarDatosPantalla();
};

