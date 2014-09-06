#include "StdAfx.h"
#include "Funciones.h"
#include <fstream>
#include <sstream>
#include <algorithm>

struct colorRGB Funciones::hexToRGB(string color)
{
	
  
	stringstream temp;
	temp << color.substr(1);
	temp << hex;

	int colorHEX;
	temp >> colorHEX;

  struct colorRGB colorRGB;
  colorRGB.r = ((colorHEX >> 16) & 0xFF);
  colorRGB.g = ((colorHEX >> 8) & 0xFF); 
  colorRGB.b = ((colorHEX) & 0xFF);

  return colorRGB; 
}

bool Funciones::estaCreado(string pathC){
	bool estaCreado = false;
	const char *path = pathC.c_str();
	FILE*fp=NULL;
	
	errno_t en = fopen_s(&fp,path,"rb");
	
	if (!en) {
		estaCreado = true;
		fclose(fp);
	}
	return estaCreado;
}

string Funciones::getFileExtension(const std::string& file)
{
    if(file.find_last_of(".") != std::string::npos)
        return file.substr(file.find_last_of(".")+1);
    return "";
}

bool Funciones::tieneExtensionValida(string path, string extension) {
	
	
    string ext = getFileExtension(path) ;
	
	string extUpper = ext;
	transform(extUpper.begin(), extUpper.end(), extUpper.begin(), toupper);

	if ( ext == extension || ext == extUpper )
		return true;
	else
		return false;
}

bool Funciones::esHEXvalido(string colorHEX){


	if (colorHEX[0] != '#'){
		return false;
	}

	if (colorHEX.size() == 7){	
		bool esHex = false;
		for (int i =1; i<=(colorHEX.size()-1); i++){
			
			esHex = isxdigit( colorHEX[i] );
		}

		if (esHex) {
		return true;
		}else {
		return false;
		}



	} else {
		return false;
	}
	
	
  return true;

}

bool Funciones::esUnaImagenValida(string path){

	stringstream fullPath; 
	string extension;
	extension = getFileExtension(path) ;

	//fullPath << "imagenes\\"; 
	fullPath << path;
	
	if( estaCreado(fullPath.str()) && ( extension == "jpg" || extension == "JPG" ||extension == "png" ||extension == "PNG" || 
		extension == "bmp" || extension == "BMP" ) )
		return true;
	else
		return false;
}


string Funciones::intToString(int num){
	
	ostringstream convert; 
	string texto;
	convert << num ;   
	texto = convert.str();
	return texto;
}

string Funciones::floatToString(float num){
	ostringstream ss;
	string aux ;
	ss << num;
	aux =  ss.str();
	return aux;
}

float Funciones::redondear(float num){
	 return floor(num+0.5);
 }
 
int Funciones::randomNum( int cotaSuperior ){
	int random;
	random = rand() % cotaSuperior + 1;
	return random;
} 
 
list<string>* Funciones::getClavesMapa(map<string,string>* map){
	list<string>* claves = new list<string>(); 
	
	std::map<std::string, std::string>::iterator it;

	for (it = map->begin(); it != map->end(); it++){
		claves->push_back(it->first); 
	}

	return claves; 
}







							