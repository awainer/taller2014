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
		log("Se esperaba un valor para " + nombreElem + " pero no se encontro o era nulo, usando valor por defecto.",WARNING);
		return defaultVal;
	}

	 if(elem.isDouble())
          return elem.asFloat();
	 else{
		 log(nombreElem + " no es un valor real, usando valor por defecto.",WARNING);
		 return defaultVal;
	 }
}
float Parser::parsearElementoFloatPositivo(Json::Value elem, float defaultVal,string nombreElem){
	if(elem.isNull()){
		log("Se esperaba un valor para " + nombreElem + " pero no se encontro o era nulo, usando valor por defecto.",WARNING);
		return defaultVal;
	}

	 if(elem.isDouble()){
		 float result = elem.asFloat();
		 if (result > 0)
			 return result;
		 else{
			 log("El  valor para " + nombreElem + " debe ser positivo, usando valor por defecto.",WARNING);
			 return defaultVal;
		 }
	 } else{
		 log(nombreElem + " no es un valor real, usando valor por defecto.",WARNING);
		 return defaultVal;
	 }
}
bool Parser::parsearBoolean(Json::Value elem, bool defaultVal, string nombreElem){
	if(elem.isNull()){
		log("Se esperaba un booleano para " + nombreElem + " pero no se encontro o era nulo, usando valor por defecto.",WARNING);
		return defaultVal;
	}

	if(elem.isBool())
		return elem.asBool();
	else{
		log("Se esperaba un booleano para " + nombreElem + ", usando valor por defecto.",WARNING);
		return defaultVal;
	}


}
int Parser::parsearElementoIntPositivo(Json::Value elem, int defaultVal,string nombreElem){
	if(elem.isNull()){
		log("Se esperaba un valor para " + nombreElem + " pero no se encontro o era nulo, usando valor por defecto.",WARNING);
		return defaultVal;
	}

	 if(elem.isInt()){
		 int result = elem.asInt();
		 if (result > 0)
			 return result;
		 else{
			 log("El  valor para " + nombreElem + " debe ser positivo, usando valor por defecto.",WARNING);
			 return defaultVal;
		 }
	 } else{
		 log(nombreElem + " no es un valor entero, usando valor por defecto.",WARNING);
		 return defaultVal;
	 }
}
string Parser::parsearImagen(Json::Value elem, string defaultVal,string nombreElem){
	if(elem.isNull()){
		log("Se esperaba un valor para " + nombreElem + " pero no se encontro o era nulo, usando valor por defecto.",LOG_ERROR);
		return defaultVal;
	}
	if(elem.isString()){
		string result = elem.asString();
		if (!Funciones::esUnaImagenValida(result)){
			log(nombreElem + " NO existe o tiene una extension invalida, usando valor por defecto",LOG_ERROR);
			return defaultVal;
		} else {
			return result;
		}
	}else{ 
		log("Se esperaba un string " + nombreElem + " , usando valor por defecto.",LOG_ERROR);
		return defaultVal;
	}
}
colorRGB Parser::parsearColor(Json::Value elem, colorRGB defaultVal, string nombreElem){
	if(elem.isNull()){
		log("Se esperaba un valor para " + nombreElem + " pero no se encontro o era nulo, usando valor por defecto.",WARNING);
		return defaultVal;
	}
	if(!elem.isString()){
		log("Se esperaba un string para " + nombreElem + ", usando valor por defecto.",WARNING);
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
		log("Se esperaba un string HEXA valido para " + nombreElem + ", usando valor por defecto.",WARNING);
		return defaultVal;
	}
}
unsigned int Parser::parsearAngulo(Json::Value elem, unsigned int defaultVal, string nombreElem){
	if(elem.isNull()){
		log("Se esperaba un valor para " + nombreElem + " pero no se encontro o era nulo, usando valor por defecto.",WARNING);
		return defaultVal;
	}
	 if(elem.isInt()){
		 int result = elem.asInt();
		 if (result >= 0 && result <= 359)
			 return result;
		 else{
			 log("El  valor para " + nombreElem + " debe ser estar entre 0 y 359, usando valor por defecto.",WARNING);
			 return defaultVal;
		 }
	 } else{
		 log(nombreElem + " no es un valor entero, usando valor por defecto.",WARNING);
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
	//result.tipo = elem['tipo'].asString();
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
	//result.tipo = elem['tipo'].asString();
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
	//result.tipo = elem['tipo'].asString();
	result.x = this->parsearElementoFloatPositivo(elem["x"],PARALELOGRAMO_X_DEFAULT," posicion x del paralelogramo");
	result.y = this->parsearElementoFloatPositivo(elem["y"],PARALELOGRAMO_Y_DEFAULT," posicion y del paralelogramo");
	result.lado1 = this->parsearElementoFloatPositivo(elem["lado1"],PARALELOGRAMO_LONGLADO1_DEFAULT," longitud lado1 del paralelogramo");
	result.lado2 = this->parsearElementoFloatPositivo(elem["lado2"],PARALELOGRAMO_LONGLADO2_DEFAULT," longitud lado2  del paralelogramo");
	result.angulo = this->parsearElementoFloatPositivo(elem["angulo"],PARALELOGRAMO_ANGULO_DEFAULT," angulo del paralelogramo");
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
	//result.tipo = elem['tipo'].asString();
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
	this->escenario = NULL;
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

		log("PATH INVALIDO: El archivo en formato JSON especificado no existe, se cargaran los valores por defecto.",LOG_ERROR);
		errorpath = true;
		parseadoOK = true;
		this->CargarDefault();
	}
   


    if(!parseadoOK){

		string errormsg = reader.getFormattedErrorMessages();
		errormsg.erase(std::remove(errormsg.begin(), errormsg.end(), '\n'), errormsg.end());
		string error;
		error = "LOG_ERROR EN ARCHIVO JSON: ";
		error.append(errormsg);
		error.append(" Se cargara la configuracion por defecto.");

        log(error,LOG_ERROR);
		
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
		log("Parser: creando escenario:",DEBUG);
		log("	Dimensiones:" + to_string(long double(miEscenario.anchoun)) + "x" + to_string(long double(miEscenario.altoun)) ,DEBUG);
		log("	Gravedad:" + to_string(long double(miEscenario.gravedad)),DEBUG);	
		log("	Path fondo:" + miEscenario.imagen_fondo,DEBUG);
		this->escenario = new Escenario(miEscenario.anchoun,miEscenario.altoun,CoordenadasR2(0,miEscenario.gravedad),miEscenario.imagen_fondo,NULL);
		log("Parser: creando jugador:",DEBUG);
		log("	Posicion:" + to_string(long double(miEscenario.personajeX)) + "," + to_string(long double(miEscenario.personajeY)),DEBUG);
		this->escenario->agregarJugador(CoordenadasR2(miEscenario.personajeX,miEscenario.personajeY));

		

        //OBJETOS
        if (root["escenario"]["objetos"].isNull()){
            log("no hay objetos declarados",WARNING);
        }

        // Si entra es porque tiene/Existe objetos 
        if (!root["escenario"]["objetos"].isNull())  {

            int objetos_size = root["escenario"]["objetos"].size();  

            string notice = "NOTICE: Hay ";
            notice.append(Funciones::intToString(objetos_size));
            notice.append(" objetos declarados.");
            log(notice,WARNING);

            //   Recorro la lista de objetos
            for(int i = 0; i < objetos_size; ++i)  
            {  
                if(root["escenario"]["objetos"][i]["tipo"].isNull()){
                    log("No es un objeto valido, no se cargara",LOG_ERROR);
                }
                else {

                    if(!root["escenario"]["objetos"][i]["tipo"].isString()){
                        log("tipo DEBE ser un string",LOG_ERROR);
                    } else {

                        string tipo = root["escenario"]["objetos"][i]["tipo"].asString();

                        if( tipo == "poli"){
							log("Parseando poligono",DEBUG);
							poli poli = this->parsearPoligono(root["escenario"]["objetos"][i]);
							log("Parser: creando poligono regular:",DEBUG);
							log("	Lados: " + to_string(long long(poli.lados)),DEBUG);
							log("	Radio: " + to_string(long double(poli.escala)),DEBUG);
							log("	Color: " + to_string(long long(poli.color.r)) + " " + to_string(long long(poli.color.g)) + " " + to_string(long long(poli.color.b)) ,DEBUG);	  
							log("	Estatico: " + to_string(long long(poli.estatico)),DEBUG);
							log("	Masa: " + to_string(long double(poli.masa)),DEBUG);
							log("	Rotacion: " + to_string(long long(poli.rot)),DEBUG);
							log("	Centro de masa: (" + to_string(long double(poli.x))  + ","+  to_string(long double(poli.y)) +")" ,DEBUG);

						this->escenario->agregarPoligono(CoordenadasR2(poli.x,poli.y),
								poli.escala,
								poli.lados,
								poli.rot,
								Color(poli.color.r,poli.color.g,poli.color.b),
								!poli.estatico,
								poli.masa);
							
                        }else if( tipo=="rect"){
							log("Parseando rectangulo",DEBUG);
							rect rectangulo = this->parsearRectangulo(root["escenario"]["objetos"][i]);
							//miEscenario.rectangulos.push_back(rect);
							log("Parser: creando rectangulo:",DEBUG);
							log("	Alto: " + to_string(long double (rectangulo.alto)),DEBUG);
							log("	Ancho: " + to_string(long double (rectangulo.ancho)),DEBUG);
							log("	Color: " + to_string(long long(rectangulo.color.r)) + " " + to_string(long long(rectangulo.color.g)) + " " + to_string(long long(rectangulo.color.b)) ,DEBUG);
							log("	Estatico: " + to_string(long long(rectangulo.estatico)),DEBUG);
							log("	Masa: " + to_string(long double(rectangulo.masa)),DEBUG);
							log("	Rotacion: " + to_string(long long(rectangulo.rot)),DEBUG);
							log("	Centro de masa: (" + to_string(long double(rectangulo.x))  + ","+  to_string(long double(rectangulo.y)) +")" ,DEBUG);

							this->escenario->agregarRectangulo(CoordenadasR2(rectangulo.x,rectangulo.y),
												   rectangulo.alto,
												   rectangulo.ancho,
												   rectangulo.rot,
												   Color(rectangulo.color.r,rectangulo.color.g,rectangulo.color.b),
												   !rectangulo.estatico,
												   rectangulo.masa);
                        }
                        else if( tipo=="circ"){
							log("Parseando circulo",DEBUG);
                            circ circulo = this->parsearCirculo(root["escenario"]["objetos"][i]);
							log("Parser: creando circulo:",DEBUG);
							log("	Radio: " + to_string(long double (circulo.radio)),DEBUG);
							log("	Color: " + to_string(long long(circulo.color.r)) + " " + to_string(long long(circulo.color.g)) + " " + to_string(long long(circulo.color.b)) ,DEBUG);
							log("	Estatico: " + to_string(long long(circulo.estatico)),DEBUG);
							log("	Masa: " + to_string(long double(circulo.masa)),DEBUG);
							log("	Centro de masa: (" + to_string(long double(circulo.x))  + ","+  to_string(long double(circulo.y)) +")" ,DEBUG);


							this->escenario->agregarPelota(CoordenadasR2(circulo.x,circulo.y),
											  circulo.radio,
											  Color(circulo.color.r, circulo.color.g, circulo.color.b),
											  !circulo.estatico,
											  circulo.masa);							
						}
                        else if( tipo=="paralel"){
							log("Parseando paralelogramo",DEBUG);
							paralel paralel = this->parsearParalelogramo(root["escenario"]["objetos"][i]);
                            log("Parser: creando paralelogramo:",DEBUG);
							log("	Lado 1: " + to_string(long double(paralel.lado1)),DEBUG);
							log("	Lado 2: " + to_string(long double(paralel.lado2)),DEBUG);
							log("	Angulo: " + to_string(long double(paralel.angulo)),DEBUG);
							log("	Color: " + to_string(long long(paralel.color.r)) + " " + to_string(long long(paralel.color.g)) + " " + to_string(long long(paralel.color.b)) ,DEBUG);
							log("	Estatico: " + to_string(long long(paralel.estatico)),DEBUG);
							log("	Masa: " + to_string(long double(paralel.masa)),DEBUG);
							log("	Centro de masa: (" + to_string(long double(paralel.x))  + ","+  to_string(long double(paralel.y)) +")" ,DEBUG);
							log("	Rotacion: " + to_string(long long(paralel.rot)),DEBUG);
							this->escenario->agregarParalelogramo(CoordenadasR2(paralel.x,paralel.y),paralel.lado1,paralel.lado2,paralel.angulo,Color(paralel.color.r, paralel.color.g, paralel.color.b),paralel.rot,!paralel.estatico,paralel.masa);
                        }
                        else if( tipo=="trap"){
							log("Parseando trapecio",DEBUG);
                            trap trapecio = this->parsearTrapecio(root["escenario"]["objetos"][i]);                                                    
                            log("Parser: creando trapecio:",DEBUG);
							log("	Lado 1: " + to_string(long double(trapecio.lado1)),DEBUG);
							log("	Lado 2: " + to_string(long double(trapecio.lado2)),DEBUG);
							log("	Lado 3: " + to_string(long double(trapecio.lado3)),DEBUG);
							log("	Color: " + to_string(long long(trapecio.color.r)) + " " + to_string(long long(trapecio.color.g)) + " " + to_string(long long(trapecio.color.b)) ,DEBUG);
							log("	Estatico: " + to_string(long long(trapecio.estatico)),DEBUG);
							log("	Masa: " + to_string(long double(trapecio.estatico)),DEBUG);
							log("	Centro de masa: (" + to_string(long double(trapecio.x))  + ","+  to_string(long double(trapecio.y)) +")" ,DEBUG);
							log("	Rotacion: " + to_string(long long(trapecio.rot)),DEBUG);

							this->escenario->agregarTrapecio(CoordenadasR2(trapecio.x,trapecio.y),trapecio.lado1,trapecio.lado2,trapecio.lado3,trapecio.altura,Color(trapecio.color.r, trapecio.color.g, trapecio.color.b),trapecio.rot,!trapecio.estatico,trapecio.masa);

                        }else{
                            log("Se intento cargar un objeto invalido: " + tipo , LOG_ERROR);
                        }


                    }  
                }
            }

        }
    } 
	catch( exception e) {
		log(" excepcion en la lectura del archivo JSON, cargando escenario por default.",LOG_ERROR);
		log(e.what() ,LOG_ERROR);
		this->CargarDefault();

	}

	}
    archivoJson.close();  
}

void Parser::CargarDefault()
{

		miEscenario.gravedad=-14;
		miEscenario.anchopx=600;
		miEscenario.altopx=600;
        
        miEscenario.altoun=10;
        miEscenario.anchoun=10;
        miEscenario.imagen_fondo="imagenes/default.jpg";
        miEscenario.personajeX=1;
        miEscenario.personajeY=1;
		this->escenario = new Escenario(miEscenario.anchoun,miEscenario.altoun,CoordenadasR2(0,miEscenario.gravedad),miEscenario.imagen_fondo,NULL);
		this->escenario->agregarJugador(CoordenadasR2(6,1));
		this->escenario->agregarPoligono(CoordenadasR2(5,6),
								1,
								5,
								90,
								Color(0,250,250),
								false,
								1);

		this->escenario->agregarPelota(CoordenadasR2(2,8),
							  0.5f,
							  Color(200,232,100),
							  true,
							  1);	
		
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

		this->escenario->agregarRectangulo(CoordenadasR2(5,1.45f),
							   0.5,
							   3,
							   3,
							   Color(100,231,50),
							   false,
							   3);

/*
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
*/
}

DatosPantalla Parser::CargarDatosPantalla() {
	DatosPantalla datos = DatosPantalla(miEscenario.anchopx,miEscenario.altopx,miEscenario.anchoun,miEscenario.altoun);
	return datos;
}

Escenario * Parser::CrearObjetos(){
	return this->escenario;
}

VistaEscenario * Parser::CrearVista() {
	DatosPantalla datos = DatosPantalla(miEscenario.altopx,miEscenario.anchopx,miEscenario.altoun , miEscenario.anchoun);
	VistaEscenario * escenario_vista = new VistaEscenario(this->escenario,&datos);
	return escenario_vista;
}



Parser::~Parser(void)
{
}
