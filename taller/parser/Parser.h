#pragma once
#include <json/json.h>

#include <stdio.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 

#include "Constantes.h"


using namespace std;

class Parser
{
private:
	StEscenario miEscenario;

public:
	Parser(void);
	~Parser(void);
	void Inicializar();
	void CrearObjetos();


};

