#pragma once
#include <string>
#include <time.h>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

#define ERROR	3
#define WARNING 2
#define DEBUG	1
#define LOGLEVEL 1

class EventLogger {

public:
	static string pathArchivo;
	static void InicializarArchivo();
	static void RecrearArchivo();
	static void Append(string msg);
	static void AgregarEvento(string msgEvento);
	static void AgregarEvento(string msgEvento,int prioridad);
	static string itos(int i);
	static string levelSring(int level);
};