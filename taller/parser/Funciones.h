#include <string> 
#include <list>
#include <map>
#include "Constantes.h"

using namespace std;

class Funciones {

	public:

		static bool esHEXvalido(string colorHEX);
		

		static struct colorRGB hexToRGB(string color);

		static bool estaCreado(string path);
		
		static string getFileExtension(const std::string& file);
		
		static bool tieneExtensionValida(string path, string extension);
		
		static bool esUnaImagenValida(string path);
		
		static bool ArchivoValido(string pathfile);
		
		static string intToString(int num);
		
		static string floatToString(float num);
		
		static float redondear(float num);
		
		static int randomNum( int  cotaSuperior ) ;		
		
		static list<string>* getClavesMapa(map<string,string>* map);
};