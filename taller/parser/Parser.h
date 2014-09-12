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

