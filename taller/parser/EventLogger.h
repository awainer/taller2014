#include <string>
#include <time.h>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class EventLogger {

public:
	static string pathArchivo;
	static void InicializarArchivo();
	static void RecrearArchivo();
	static void Append(string msg);
	static void AgregarEvento(string msgEvento);

};