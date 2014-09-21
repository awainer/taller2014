#include "Parser.h"
#include "EventLogger.h"
#include "Funciones.h"
#include "../model/Escenario.h"
#include "../model/Rectangulo.h"
#include "../model/Pelota.h"
#include "../model/Poligono.h"
#include "../model/CoordenadasR2.h"
#include "../model/Color.h"

Parser::Parser(void)
{
}

Parser::Parser(string path)
{
	jsonpath = path;
}

float Parser::parsearElementoFloatUnsigned(Json::Value elem, float defaultVal,string nombreElem){
	if(elem.isNull()){
		EventLogger::AgregarEvento("Se esperaba un valor para " + nombreElem + " pero no se encontro o era nulo, usando valor por defecto.",WARNING);
		return defaultVal;
	}

	 if(elem.isDouble())
          return elem.asFloat();
	 else{
		 EventLogger::AgregarEvento(nombreElem + " no es un valor real, usando valor por defecto.",WARNING);
	 }
}
float Parser::parsearElementoFloatPositivo(Json::Value elem, float defaultVal,string nombreElem){
	if(elem.isNull()){
		EventLogger::AgregarEvento("Se esperaba un valor para " + nombreElem + " pero no se encontro o era nulo, usando valor por defecto.",WARNING);
		return defaultVal;
	}

	 if(elem.isDouble()){
		 float result = elem.asFloat();
		 if (result > 0)
			 return result;
		 else{
			 EventLogger::AgregarEvento("El  valor para " + nombreElem + " debe ser positivo, usando valor por defecto.",WARNING);
			 return defaultVal;
		 }
	 } else{
		 EventLogger::AgregarEvento(nombreElem + " no es un valor real, usando valor por defecto.",WARNING);
		 return defaultVal;
	 }
}
bool Parser::parsearBoolean(Json::Value elem, bool defaultVal, string nombreElem){
	if(elem.isNull()){
		EventLogger::AgregarEvento("Se esperaba un booleano para " + nombreElem + " pero no se encontro o era nulo, usando valor por defecto.",WARNING);
		return defaultVal;
	}

	if(elem.isBool())
		return elem.asBool();
	else{
		EventLogger::AgregarEvento("Se esperaba un booleano para " + nombreElem + ", usando valor por defecto.",WARNING);
		return defaultVal;
	}


}
float Parser::parsearElementoIntPositivo(Json::Value elem, int defaultVal,string nombreElem){
	if(elem.isNull()){
		EventLogger::AgregarEvento("Se esperaba un valor para " + nombreElem + " pero no se encontro o era nulo, usando valor por defecto.",WARNING);
		return defaultVal;
	}

	 if(elem.isInt()){
		 int result = elem.asInt();
		 if (result > 0)
			 return result;
		 else{
			 EventLogger::AgregarEvento("El  valor para " + nombreElem + " debe ser positivo, usando valor por defecto.",WARNING);
			 return defaultVal;
		 }
	 } else{
		 EventLogger::AgregarEvento(nombreElem + " no es un valor entero, usando valor por defecto.",WARNING);
		 return defaultVal;
	 }
}
string Parser::parsearImagen(Json::Value elem, string defaultVal,string nombreElem){
	if(elem.isNull()){
		EventLogger::AgregarEvento("Se esperaba un valor para " + nombreElem + " pero no se encontro o era nulo, usando valor por defecto.",ERROR);
		return defaultVal;
	}
	if(elem.isString()){
		string result = elem.asString();
		if (!Funciones::esUnaImagenValida(result)){
			EventLogger::AgregarEvento(nombreElem + " NO existe o tiene una extension invalida, usando valor por defecto",ERROR);
			return defaultVal;
		} else {
			return result;
		}
	}else{ 
		EventLogger::AgregarEvento("Se esperaba un string " + nombreElem + " , usando valor por defecto.",ERROR);
		return defaultVal;
	}
}


colorRGB Parser::parsearColor(Json::Value elem, colorRGB defaultVal, string nombreElem){
	if(elem.isNull()){
		EventLogger::AgregarEvento("Se esperaba un valor para " + nombreElem + " pero no se encontro o era nulo, usando valor por defecto.",WARNING);
		return defaultVal;
	}
	if(!elem.isString()){
		EventLogger::AgregarEvento("Se esperaba un string para " + nombreElem + ", usando valor por defecto.",WARNING);
		return defaultVal;
	}
	string colorString = elem.asString();
	colorRGB result;
	if(Funciones::esHEXvalido(colorString)){
		//Si es un hex valido....
		result.r = Funciones::hexToRGB(colorString).r;
        result.g = Funciones::hexToRGB(colorString).g;
        result.b = Funciones::hexToRGB(colorString).b;
		return result;
	} else {
		EventLogger::AgregarEvento("Se esperaba un string HEXA valido para " + nombreElem + ", usando valor por defecto.",WARNING);
		return defaultVal;
	}
}

unsigned int Parser::parsearAngulo(Json::Value elem, unsigned int defaultVal, string nombreElem){
	if(elem.isNull()){
		EventLogger::AgregarEvento("Se esperaba un valor para " + nombreElem + " pero no se encontro o era nulo, usando valor por defecto.",WARNING);
		return defaultVal;
	}
	 if(elem.isInt()){
		 int result = elem.asInt();
		 if (result >= 0 && result <= 359)
			 return result;
		 else{
			 EventLogger::AgregarEvento("El  valor para " + nombreElem + " debe ser estar entre 0 y 359, usando valor por defecto.",WARNING);
			 return defaultVal;
		 }
	 } else{
		 EventLogger::AgregarEvento(nombreElem + " no es un valor entero, usando valor por defecto.",WARNING);
		 return defaultVal;
	 }

}

rect Parser::parsearRectangulo(Json::Value elem){
	rect result;
	colorRGB defaultColor;
	defaultColor.r = R_DEFAULT;
	defaultColor.g = G_DEFAULT;
	defaultColor.b = B_DEFAULT;
	result.ancho = this->parsearElementoFloatPositivo(elem["ancho"],RECTANGULO_ANCHO_DEFAULT, " ancho del rectangulo ");
	result.alto = this->parsearElementoFloatPositivo(elem["alto"],RECTANGULO_ALTO_DEFAULT, " alto del rectangulo ");
	result.masa = this->parsearElementoFloatPositivo(elem["masa"],RECTANGULO_MASA_DEFAULT, " masa del rectangulo ");
	result.color = this->parsearColor(elem["color"], defaultColor, " color del rectangulo ");
	result.estatico = this->parsearBoolean(elem["estatico"],POLIGONO_ESTATICO_DEFAULT, "estatico");
	result.rot = this->parsearAngulo(elem["rot"],POLIGONO_ROT_DEFAULT, " angulo de rotacion ");
	result.x = this->parsearElementoFloatPositivo(elem["x"],RECTANGULO_X_DEFAULT," posicion x del rectangulo");
	result.y = this->parsearElementoFloatPositivo(elem["y"],RECTANGULO_Y_DEFAULT," posicion y del rectangulo");
	return result;
}

poli Parser::parsearPoligono(Json::Value elem){
	poli result;
	colorRGB defaultColor;
	defaultColor.r = R_DEFAULT;
	defaultColor.g = G_DEFAULT;
	defaultColor.b = B_DEFAULT;
	result.tipo = elem['tipo'].asString();
	result.x = this->parsearElementoFloatPositivo(elem["x"],POLIGONO_X_DEFAULT," posicion x del poligono");
	result.y = this->parsearElementoFloatPositivo(elem["y"],POLIGONO_Y_DEFAULT," posicion y del poligono");
	result.escala = this->parsearElementoFloatPositivo(elem["escala"],POLIGONO_ESCALA_DEFAULT, " escala ");
	result.masa = this->parsearElementoFloatPositivo(elem["masa"],POLIGONO_MASA_DEFAULT, " masa ");
	result.lados = this->parsearElementoIntPositivo(elem["lados"],POLIGONO_LADOS_DEFAULT," cantidad de lados ");
	result.estatico = this->parsearBoolean(elem["estatico"],POLIGONO_ESTATICO_DEFAULT, "estatico");
	result.color = this->parsearColor(elem["color"], defaultColor, " color del poligono ");
	result.rot = this->parsearAngulo(elem["rot"],POLIGONO_ROT_DEFAULT, " angulo de rotacion ");
	return result;
}

trap Parser::parsearTrapecio(Json::Value elem){
	trap result;
	colorRGB defaultColor;
	defaultColor.r = R_DEFAULT;
	defaultColor.g = G_DEFAULT;
	defaultColor.b = B_DEFAULT;
	result.tipo = elem['tipo'].asString();
	result.x = this->parsearElementoFloatPositivo(elem["x"],TRAPECIO_X_DEFAULT," posicion x del trapecio");
	result.y = this->parsearElementoFloatPositivo(elem["y"],TRAPECIO_Y_DEFAULT," posicion y del trapecio");
	result.lado1 = this->parsearElementoFloatPositivo(elem["lado1"],TRAPECIO_LONGLADO1_DEFAULT," longitud lado izquierdo del trapecio");
	result.lado2 = this->parsearElementoFloatPositivo(elem["lado2"],TRAPECIO_LONGLADO2_DEFAULT," longitud techo  del trapecio");
	result.lado3 = this->parsearElementoFloatPositivo(elem["lado3"],TRAPECIO_LONGLADO3_DEFAULT," longitud lado derecho  del trapecio");
	result.altura = this->parsearElementoFloatPositivo(elem["altura"],TRAPECIO_ALTURA_DEFAULT," altura del trapecio");
	result.masa = this->parsearElementoFloatPositivo(elem["masa"],TRAPECIO_MASA_DEFAULT, " masa ");	
	result.estatico = this->parsearBoolean(elem["estatico"],TRAPECIO_ESTATICO_DEFAULT, "estatico");
	result.color = this->parsearColor(elem["color"], defaultColor, " color del trapecio ");
	result.rot = this->parsearAngulo(elem["rot"],TRAPECIO_ROT_DEFAULT, " angulo de trapecio ");
	return result;
}

paralel Parser::parsearParalelogramo(Json::Value elem){
	paralel result;
	colorRGB defaultColor;
	defaultColor.r = R_DEFAULT;
	defaultColor.g = G_DEFAULT;
	defaultColor.b = B_DEFAULT;
	result.tipo = elem['tipo'].asString();
	result.x = this->parsearElementoFloatPositivo(elem["x"],PARALELOGRAMO_X_DEFAULT," posicion x del paralelogramo");
	result.y = this->parsearElementoFloatPositivo(elem["y"],PARALELOGRAMO_Y_DEFAULT," posicion y del paralelogramo");
	result.lado1 = this->parsearElementoFloatPositivo(elem["lado1"],PARALELOGRAMO_LONGLADO1_DEFAULT," longitud lado1 del paralelogramo");
	result.lado2 = this->parsearElementoFloatPositivo(elem["lado2"],PARALELOGRAMO_LONGLADO2_DEFAULT," longitud lado2  del paralelogramo");
	result.altura = this->parsearElementoFloatPositivo(elem["altura"],PARALELOGRAMO_ALTURA_DEFAULT," altura del paralelogramo");
	result.masa = this->parsearElementoFloatPositivo(elem["masa"],PARALELOGRAMO_MASA_DEFAULT, " masa ");	
	result.estatico = this->parsearBoolean(elem["estatico"],PARALELOGRAMO_ESTATICO_DEFAULT, "estatico");
	result.color = this->parsearColor(elem["color"], defaultColor, " color del paralelogramo ");
	result.rot = this->parsearAngulo(elem["rot"],PARALELOGRAMO_ROT_DEFAULT, " angulo de paralelogramo ");
	return result;
}



circ Parser::parsearCirculo(Json::Value elem){
	circ result;
	colorRGB defaultColor;
	defaultColor.r = R_DEFAULT;
	defaultColor.g = G_DEFAULT;
	defaultColor.b = B_DEFAULT;
	result.tipo = elem['tipo'].asString();
	result.x = this->parsearElementoFloatPositivo(elem["x"],CIRCULO_X_DEFAULT," posicion x del circulo");
	result.y = this->parsearElementoFloatPositivo(elem["y"],CIRCULO_X_DEFAULT," posicion y del circulo");
	result.radio = this->parsearElementoFloatPositivo(elem["radio"],CIRCULO_RADIO_DEFAULT," radio del circulo");
	result.estatico = this->parsearBoolean(elem["estatico"],CIRCULO_ESTATICO_DEFAULT, "estatico");
	result.masa = this->parsearElementoFloatPositivo(elem["masa"],CIRCULO_MASA_DEFAULT, " masa ");
	result.color = this->parsearColor(elem["color"], defaultColor, " color del circulo ");
	return result;
}
void Parser::Inicializar()
{
    bool pxSonDefault = false;
    bool unSonDefault = false;
    bool personajeSonDefault = false;

	Json::Features features;
    Json::Reader reader = Json::Reader(features.strictMode());  
    Json::Value root;    

    //Ubicacion Archivo

    //const char* filename= "parser/test.json";
	const char* filename= jsonpath.c_str();

	

    std::ifstream archivoJson;  
    
	bool errorpath = false;
	bool parseadoOK;


	if( Funciones::estaCreado(filename) ) {
		
		archivoJson.open (filename, std::ios::binary );
		// Devuelvo si hubo error en el parseado a nivel de la libreria!
		parseadoOK = reader.parse(archivoJson, root, false);
		errorpath = false;

	} else {

		EventLogger::AgregarEvento("PATH INVALIDO: El archivo en formato JSON especificado no existe, se cargaran los valores por defecto.",ERROR);
		errorpath = true;
		parseadoOK = true;
		this->CargarDefault();
	}
   


    if(!parseadoOK){

		string errormsg = reader.getFormattedErrorMessages();
		errormsg.erase(std::remove(errormsg.begin(), errormsg.end(), '\n'), errormsg.end());
		string error;
		error = "ERROR EN ARCHIVO JSON: ";
		error.append(errormsg);
		error.append(" Se cargara la configuracion por defecto.");

        EventLogger::AgregarEvento(error,ERROR);
		
        //TODO:CARGAR JSON POR DEFECTO   
		this->CargarDefault();


    }

    if (parseadoOK && !errorpath)  
    { 
		try{
        miEscenario.gravedad = this->parsearElementoFloatUnsigned(root["escenario"]["gravedad"],GRAVEDAD_DEFAULT,"gravedad");
		miEscenario.altopx  =  this->parsearElementoIntPositivo(root["escenario"]["alto-px"],ALTO_PX_DEFAULT,"alto en px");
		miEscenario.anchopx  =  this->parsearElementoIntPositivo(root["escenario"]["ancho-px"],ANCHO_PX_DEFAULT,"ancho en px");
		miEscenario.altoun  = this->parsearElementoFloatPositivo(root["escenario"]["alto-un"],ALTO_UN_DEFAULT, " alto en unidades");
		miEscenario.anchoun = this->parsearElementoFloatPositivo(root["escenario"]["ancho-un"],ANCHO_UN_DEFAULT, " alto en unidades");
		miEscenario.imagen_fondo = this->parsearImagen(root["escenario"]["imagen_fondo"],IMAGEN_DEFAULT," path de imagen de fondo");
		miEscenario.personajeX = this->parsearElementoFloatPositivo(root["escenario"]["personaje"]["x"],PERSONAJE_X_DEFAULT,"coordenada X del personaje");
		miEscenario.personajeY = this->parsearElementoFloatPositivo(root["escenario"]["personaje"]["y"],PERSONAJE_Y_DEFAULT,"coordenada X del personaje");

        //OBJETOS
        if (root["escenario"]["objetos"].isNull()){
            EventLogger::AgregarEvento("no hay objetos declarados",WARNING);
        }

        // Si entra es porque tiene/Existe objetos 
        if (!root["escenario"]["objetos"].isNull())  {

            int objetos_size = root["escenario"]["objetos"].size();  

            string notice = "NOTICE: Hay ";
            notice.append(Funciones::intToString(objetos_size));
            notice.append(" objetos declarados.");
            EventLogger::AgregarEvento(notice,WARNING);

            //   Recorro la lista de objetos
            for(int i = 0; i < objetos_size; ++i)  
            {  
                if(root["escenario"]["objetos"][i]["tipo"].isNull()){
                    EventLogger::AgregarEvento("No es un objeto valido, no se cargara",ERROR);
                }
                else {

                    if(!root["escenario"]["objetos"][i]["tipo"].isString()){
                        EventLogger::AgregarEvento("tipo DEBE ser un string",ERROR);
                    } else {

                        string tipo = root["escenario"]["objetos"][i]["tipo"].asString();


                        if( tipo == "poli"){
							poli poli = this->parsearPoligono(root["escenario"]["objetos"][i]);
							miEscenario.poligonos.push_back(poli);
                        }else if( tipo=="rect"){
							rect rect = this->parsearRectangulo(root["escenario"]["objetos"][i]);
							miEscenario.rectangulos.push_back(rect);
                        }
                        else if( tipo=="circ"){
                            circ circulo = this->parsearCirculo(root["escenario"]["objetos"][i]);
							miEscenario.circulos.push_back(circulo);
                        }
                        else if( tipo=="paralel"){
                            
                            paralel paralel = this->parsearParalelogramo(root["escenario"]["objetos"][i]);                         
                            miEscenario.paralelogramos.push_back(paralel);
							
                        }
                        else if( tipo=="trap"){
                            trap trap = this->parsearTrapecio(root["escenario"]["objetos"][i]);                                                    
                            miEscenario.trapecios.push_back(trap);
							
                        }else{
                            EventLogger::AgregarEvento("ERROR: se quiso cargar un objeto invalido: " + tipo );
                        }


                    }  
                }
            }

        }
    } 
	catch( exception e) {
		EventLogger::AgregarEvento("ERROR: error en la lectura del archivo JSON");
		this->CargarDefault();

	}

	}


    archivoJson.close();  













}

void Parser::CargarDefault()
{
	//UNA OPCION 
	//SE DEBERIAN LLENAR BIEN LAS CONSTANTES DEFAULT DESPUES y usar algunas de esas aca
	//CREAR MAS ESCENARIOS DEFAULT
		miEscenario.gravedad=-14;
		miEscenario.anchopx=600;
		miEscenario.altopx=600;
        
        miEscenario.altoun=10;
        miEscenario.anchoun=10;
        miEscenario.imagen_fondo="imagenes/default.jpg";
        miEscenario.personajeX=1;
        miEscenario.personajeY=1;


		// UN POLI
		
		poli objetoActualPoli;
		objetoActualPoli.lados = 5;
		objetoActualPoli.escala =1;
		objetoActualPoli.color.r = 0;
		objetoActualPoli.color.g = 250;
		objetoActualPoli.color.b = 250;
		objetoActualPoli.estatico=true;
		objetoActualPoli.masa=1;
		objetoActualPoli.rot=90;
		objetoActualPoli.tipo="poli";
		objetoActualPoli.x=5;
		objetoActualPoli.y=6;
		
		miEscenario.poligonos.push_back(objetoActualPoli);
		

		// UN CIRCULO
		 
			circ unCirculo;
			unCirculo.x = 2;
			unCirculo.y = 8;
			unCirculo.radio = 0.5;
			unCirculo.color.r = 200;
			unCirculo.color.g = 232;
			unCirculo.color.b = 100;
			unCirculo.estatico = false;
			unCirculo.masa = 1;

			miEscenario.circulos.push_back(unCirculo);
		
		// UN RECT
		rect objetoActualRect;
		objetoActualRect.alto=0.5;
		objetoActualRect.ancho=3;
		objetoActualRect.color.r=134;
		objetoActualRect.color.g=134;
		objetoActualRect.color.b=255;
		objetoActualRect.estatico=true;
		objetoActualRect.masa=3;
		objetoActualRect.rot=0;		
		objetoActualRect.x=5;
		objetoActualRect.y=1.45f;
		miEscenario.rectangulos.push_back(objetoActualRect);

		objetoActualRect.alto=0.5;
		objetoActualRect.ancho=3;
		objetoActualRect.color.r=134;
		objetoActualRect.color.g=134;
		objetoActualRect.color.b=255;
		objetoActualRect.estatico=true;
		objetoActualRect.masa=3;
		objetoActualRect.rot=0;		
		objetoActualRect.x=1.5;
		objetoActualRect.y=3;
		miEscenario.rectangulos.push_back(objetoActualRect);

		objetoActualRect.alto=0.5;
		objetoActualRect.ancho=3;
		objetoActualRect.color.r=134;
		objetoActualRect.color.g=134;
		objetoActualRect.color.b=255;
		objetoActualRect.estatico=true;
		objetoActualRect.masa=3;
		objetoActualRect.rot=0;		
		objetoActualRect.x=8.5;
		objetoActualRect.y=3;
		miEscenario.rectangulos.push_back(objetoActualRect);

		objetoActualRect.alto=0.5;
		objetoActualRect.ancho=3;
		objetoActualRect.color.r=134;
		objetoActualRect.color.g=134;
		objetoActualRect.color.b=255;
		objetoActualRect.estatico=true;
		objetoActualRect.masa=3;
		objetoActualRect.rot=225;		
		objetoActualRect.x=2;
		objetoActualRect.y=6;
		miEscenario.rectangulos.push_back(objetoActualRect);

}

DatosPantalla Parser::CargarDatosPantalla() {
	
	DatosPantalla datos = DatosPantalla(miEscenario.anchopx,miEscenario.altopx,miEscenario.anchoun,miEscenario.altoun);

	return datos;

}

VistaEscenario * Parser::CrearVista() {


	//REVISARRRR
	Escenario * esc = this->CrearObjetos();
	
	//REVISARRRR
	DatosPantalla datos = DatosPantalla(miEscenario.altopx,miEscenario.anchopx,miEscenario.altoun , miEscenario.anchoun);

	VistaEscenario * escenario_vista = new VistaEscenario(esc,&datos);

	return escenario_vista;

}

Escenario * Parser::CrearObjetos()
{
	
	EventLogger::AgregarEvento("Parser: creando escenario:",DEBUG);
	EventLogger::AgregarEvento("	Dimensiones:" + to_string(long double(miEscenario.anchoun)) + "x" + to_string(long double(miEscenario.altoun)) ,DEBUG);
	EventLogger::AgregarEvento("	Gravedad:" + to_string(long double(miEscenario.gravedad)),DEBUG);	
	EventLogger::AgregarEvento("	Path fondo:" + miEscenario.imagen_fondo,DEBUG);
	Escenario * esc = new Escenario(miEscenario.anchoun,miEscenario.altoun,CoordenadasR2(0,miEscenario.gravedad),miEscenario.imagen_fondo,NULL);
	EventLogger::AgregarEvento("Parser: creando jugador:",DEBUG);
	EventLogger::AgregarEvento("	Posicion:" + to_string(long double(miEscenario.personajeX)) + "," + to_string(long double(miEscenario.personajeY)),DEBUG);
	esc->agregarJugador(CoordenadasR2(miEscenario.personajeX,miEscenario.personajeY));
	// CREAR POLIGONOS
	list <poli> objetosPoli;
	poli objetoActualPoli;
	objetosPoli = miEscenario.poligonos;

	for (list <poli> ::iterator it= objetosPoli.begin(); it!= objetosPoli.end(); it++) {
		objetoActualPoli =  *it;
		objetoActualPoli.lados;
		objetoActualPoli.escala;
		objetoActualPoli.color;
		objetoActualPoli.estatico;
		objetoActualPoli.masa;
		objetoActualPoli.rot;
		objetoActualPoli.tipo;
		objetoActualPoli.x;
		objetoActualPoli.y;
		EventLogger::AgregarEvento("Parser: creando poligono regular:",DEBUG);
		EventLogger::AgregarEvento("	Lados: " + to_string(long long(objetoActualPoli.lados)),DEBUG);
		EventLogger::AgregarEvento("	Radio: " + to_string(long double(objetoActualPoli.escala)),DEBUG);
		EventLogger::AgregarEvento("	Color: " + to_string(long long(objetoActualPoli.color.r)) + " " + to_string(long long(objetoActualPoli.color.g)) + " " + to_string(long long(objetoActualPoli.color.b)) ,DEBUG);	  
		EventLogger::AgregarEvento("	Estatico: " + to_string(long long(objetoActualPoli.estatico)),DEBUG);
		EventLogger::AgregarEvento("	Masa: " + to_string(long double(objetoActualPoli.masa)),DEBUG);
		EventLogger::AgregarEvento("	Rotacion: " + to_string(long long(objetoActualPoli.rot)),DEBUG);
		EventLogger::AgregarEvento("	Centro de masa: (" + to_string(long double(objetoActualPoli.x))  + ","+  to_string(long double(objetoActualPoli.y)) +")" ,DEBUG);

		esc->agregarPoligono(CoordenadasR2(objetoActualPoli.x,objetoActualPoli.y),
							objetoActualPoli.escala,
							objetoActualPoli.lados,
							objetoActualPoli.rot,
							Color(objetoActualPoli.color.r,objetoActualPoli.color.g,objetoActualPoli.color.b),
							!objetoActualPoli.estatico,
							objetoActualPoli.masa);

	}

	//CREAR RECTANGULOS
	list <rect> objetosRect;
	rect objetoActualRect;
	objetosRect = miEscenario.rectangulos;
	for (list <rect> ::iterator it= objetosRect.begin(); it!= objetosRect.end(); it++) {
		objetoActualRect =  *it;
		EventLogger::AgregarEvento("Parser: creando rectangulo:",DEBUG);
		EventLogger::AgregarEvento("	Alto: " + to_string(long double (objetoActualRect.alto)),DEBUG);
		EventLogger::AgregarEvento("	Ancho: " + to_string(long double (objetoActualRect.ancho)),DEBUG);
		EventLogger::AgregarEvento("	Color: " + to_string(long long(objetoActualRect.color.r)) + " " + to_string(long long(objetoActualRect.color.g)) + " " + to_string(long long(objetoActualRect.color.b)) ,DEBUG);
		EventLogger::AgregarEvento("	Estatico: " + to_string(long long(objetoActualRect.estatico)),DEBUG);
		EventLogger::AgregarEvento("	Masa: " + to_string(long double(objetoActualRect.masa)),DEBUG);
		EventLogger::AgregarEvento("	Rotacion: " + to_string(long long(objetoActualRect.rot)),DEBUG);
		EventLogger::AgregarEvento("	Centro de masa: (" + to_string(long double(objetoActualRect.x))  + ","+  to_string(long double(objetoActualRect.y)) +")" ,DEBUG);

		esc->agregarRectangulo(CoordenadasR2(objetoActualRect.x,objetoActualRect.y),
			objetoActualRect.alto,
			objetoActualRect.ancho,
			objetoActualRect.rot,
			Color(objetoActualRect.color.r,objetoActualRect.color.g,objetoActualRect.color.b),
			!objetoActualRect.estatico,
			objetoActualRect.masa);


	}

	list <circ> objetosCirc;
	circ objetoActualCirc;
	objetosCirc = miEscenario.circulos;
	for (list <circ> ::iterator it= miEscenario.circulos.begin(); it!= miEscenario.circulos.end(); it++) {
		circ unCirculo= *it;
		EventLogger::AgregarEvento("Parser: creando circulo:",DEBUG);
		EventLogger::AgregarEvento("	Radio: " + to_string(long double (unCirculo.radio)),DEBUG);
		EventLogger::AgregarEvento("	Color: " + to_string(long long(unCirculo.color.r)) + " " + to_string(long long(unCirculo.color.g)) + " " + to_string(long long(unCirculo.color.b)) ,DEBUG);
		EventLogger::AgregarEvento("	Estatico: " + to_string(long long(unCirculo.estatico)),DEBUG);
		EventLogger::AgregarEvento("	Masa: " + to_string(long double(unCirculo.masa)),DEBUG);
		EventLogger::AgregarEvento("	Centro de masa: (" + to_string(long double(unCirculo.x))  + ","+  to_string(long double(unCirculo.y)) +")" ,DEBUG);


		esc->agregarPelota(CoordenadasR2(unCirculo.x,unCirculo.y),
			unCirculo.radio,
			Color(unCirculo.color.r, unCirculo.color.g, unCirculo.color.b),
			!unCirculo.estatico,
			unCirculo.masa);

	}

	list <paralel> objetosParalel;
	objetosParalel = miEscenario.paralelogramos;
	for (list <paralel> ::iterator it= miEscenario.paralelogramos.begin(); it!= miEscenario.paralelogramos.end(); it++) {
		paralel unParalelogramo= *it;
		EventLogger::AgregarEvento("Parser: creando paralelogramo:",DEBUG);
		EventLogger::AgregarEvento("	Lado 1: " + to_string(long double(unParalelogramo.lado1)),DEBUG);
		EventLogger::AgregarEvento("	Lado 2: " + to_string(long double(unParalelogramo.lado2)),DEBUG);
		EventLogger::AgregarEvento("	Altura: " + to_string(long double(unParalelogramo.altura)),DEBUG);
		EventLogger::AgregarEvento("	Color: " + to_string(long long(unParalelogramo.color.r)) + " " + to_string(long long(unParalelogramo.color.g)) + " " + to_string(long long(unParalelogramo.color.b)) ,DEBUG);
		EventLogger::AgregarEvento("	Estatico: " + to_string(long long(unParalelogramo.estatico)),DEBUG);
		EventLogger::AgregarEvento("	Masa: " + to_string(long double(unParalelogramo.masa)),DEBUG);
		EventLogger::AgregarEvento("	Centro de masa: (" + to_string(long double(unParalelogramo.x))  + ","+  to_string(long double(unParalelogramo.y)) +")" ,DEBUG);
		EventLogger::AgregarEvento("	Rotacion: " + to_string(long long(unParalelogramo.rot)),DEBUG);

		esc->agregarParalelogramo(CoordenadasR2(unParalelogramo.x,unParalelogramo.y),unParalelogramo.lado1,unParalelogramo.lado2,unParalelogramo.altura,Color(unParalelogramo.color.r, unParalelogramo.color.g, unParalelogramo.color.b),unParalelogramo.rot,!unParalelogramo.estatico,unParalelogramo.masa);


	}

	

	list <trap> objetosTrap;	
	objetosTrap = miEscenario.trapecios;
	for (list <trap> ::iterator it= miEscenario.trapecios.begin(); it!= miEscenario.trapecios.end(); it++) {
		trap unTrapecio= *it;
		EventLogger::AgregarEvento("Parser: creando trapecio:",DEBUG);
		EventLogger::AgregarEvento("	Lado 1: " + to_string(long double(unTrapecio.lado1)),DEBUG);
		EventLogger::AgregarEvento("	Lado 2: " + to_string(long double(unTrapecio.lado2)),DEBUG);
		EventLogger::AgregarEvento("	Lado 3: " + to_string(long double(unTrapecio.lado3)),DEBUG);
		EventLogger::AgregarEvento("	Color: " + to_string(long long(unTrapecio.color.r)) + " " + to_string(long long(unTrapecio.color.g)) + " " + to_string(long long(unTrapecio.color.b)) ,DEBUG);
		EventLogger::AgregarEvento("	Estatico: " + to_string(long long(unTrapecio.estatico)),DEBUG);
		EventLogger::AgregarEvento("	Masa: " + to_string(long double(unTrapecio.estatico)),DEBUG);
		EventLogger::AgregarEvento("	Centro de masa: (" + to_string(long double(unTrapecio.x))  + ","+  to_string(long double(unTrapecio.y)) +")" ,DEBUG);
		EventLogger::AgregarEvento("	Rotacion: " + to_string(long long(unTrapecio.rot)),DEBUG);

		esc->agregarTrapecio(CoordenadasR2(unTrapecio.x,unTrapecio.y),unTrapecio.lado1,unTrapecio.lado2,unTrapecio.lado3,unTrapecio.altura,Color(unTrapecio.color.r, unTrapecio.color.g, unTrapecio.color.b),unTrapecio.rot,!unTrapecio.estatico,unTrapecio.masa);


	}

	return esc;

}


Parser::~Parser(void)
{
}
