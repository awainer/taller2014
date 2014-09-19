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

		EventLogger::AgregarEvento("ERROR: PATH INVALIDO: El archivo en formato JSON especificado no existe, se cargaran los valores por defecto.");
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

        EventLogger::AgregarEvento(error);
		
        //TODO:CARGAR JSON POR DEFECTO   
		this->CargarDefault();


    }

    if (parseadoOK && !errorpath)  
    { 
		//agrego try a la lectura
		try{
        // Valores por defecto_?
        /*
        miEscenario.altopx = 0;
        miEscenario.anchopx = 0;
        miEscenario.altoun = 0;
        miEscenario.anchoun = 0;
        miEscenario.imagen_fondo = "";
        miEscenario.personajeX = 0;
        miEscenario.personajeY = 0;	  
        */

			/*************************************************************************************************/ 
        //VALIDACIONES: gravedad
        
        if(!root["escenario"]["gravedad"].isNull()){

            
            if(root["escenario"]["gravedad"].isDouble()){

               
                        miEscenario.gravedad = root["escenario"]["gravedad"].asFloat();                 

            }  else {

                EventLogger::AgregarEvento("ERROR: gravedad del escenario DEBE ser un real, se cargaran los valores por defecto");

              
               miEscenario.gravedad = GRAVEDAD_DEFAULT;
            }

        } else {
            EventLogger::AgregarEvento("ERROR: gravedad del escenario NO existe en el archivo, se cargaran los valores por defecto");

            miEscenario.gravedad = GRAVEDAD_DEFAULT;

        }
        /*************************************************************************************************/ 




        /*************************************************************************************************/ 
        //VALIDACIONES: alto-px 
        //SI EXISTE
        if(!root["escenario"]["alto-px"].isNull()){

            //SI ES UN ENTERO
			if(root["escenario"]["alto-px"].isInt()){

                if(root["escenario"]["alto-px"].asInt()>=0){

                    if(!pxSonDefault)
                        miEscenario.altopx = root["escenario"]["alto-px"].asInt();  

                } else {
                    EventLogger::AgregarEvento("ERROR: alto-px del escenario DEBE ser un entero positivo, se cargaran los valores por defecto");
					//TODO:Cargar valores por defecto... Alto y ancho?
					miEscenario.altopx = ALTO_PX_DEFAULT;
					miEscenario.anchopx = ANCHO_PX_DEFAULT;
					pxSonDefault = true;
                }


            }  else {

                EventLogger::AgregarEvento("ERROR: alto-px del escenario DEBE ser un entero positivo, se cargaran los valores por defecto");

                //TODO:Cargar valores por defecto... Alto y ancho?
                miEscenario.altopx = ALTO_PX_DEFAULT;
                miEscenario.anchopx = ANCHO_PX_DEFAULT;
                pxSonDefault = true;

            }

        } else {
            EventLogger::AgregarEvento("ERROR: alto-px del escenario NO existe en el archivo, se cargaran los valores por defecto");

            //TODO:Cargar valores por defecto... Alto y ancho?
            miEscenario.altopx = ALTO_PX_DEFAULT;
            miEscenario.anchopx = ANCHO_PX_DEFAULT;
            pxSonDefault = true;
        }
        /*************************************************************************************************/ 

        /*************************************************************************************************/ 
        //VALIDACIONES: ancho-px 
        //SI EXISTE
        if(!root["escenario"]["ancho-px"].isNull()){

            //SI ES UN ENTERO
            if(root["escenario"]["ancho-px"].isInt()){

                if(root["escenario"]["ancho-px"].asInt()>=0){
                    if(!pxSonDefault)
                        miEscenario.anchopx = root["escenario"]["ancho-px"].asInt();  
                } else {
                    EventLogger::AgregarEvento("ERROR: ancho-px del escenario DEBE ser un entero positivo, se cargaran los valores por defecto");

					//TODO:Cargar valores por defecto... Alto y ancho?
                miEscenario.altopx = ALTO_PX_DEFAULT;
                miEscenario.anchopx = ANCHO_PX_DEFAULT;
                pxSonDefault = true;

                }

            }  else {

                EventLogger::AgregarEvento("ERROR: ancho-px del escenario DEBE ser un entero positivo, se cargaran los valores por defecto");

                //TODO:Cargar valores por defecto... Alto y ancho?
                miEscenario.altopx = ALTO_PX_DEFAULT;
                miEscenario.anchopx = ANCHO_PX_DEFAULT;
                pxSonDefault = true;

            }

        } else {
            EventLogger::AgregarEvento("ERROR: ancho-px del escenario NO existe en el archivo, se cargaran los valores por defecto");

            //TODO:Cargar valores por defecto... Alto y ancho?
            miEscenario.altopx = ALTO_PX_DEFAULT;
            miEscenario.anchopx = ANCHO_PX_DEFAULT;
            pxSonDefault = true;

        }
        /*************************************************************************************************/ 

        /*************************************************************************************************/ 
        //VALIDACIONES: alto-un 
        //SI EXISTE
        if(!root["escenario"]["alto-un"].isNull()){

            //SI ES UN ENTERO
            if(root["escenario"]["alto-un"].isDouble()){

                if(root["escenario"]["alto-un"].asFloat()>=0){
                    if(!unSonDefault)
                        miEscenario.altoun = root["escenario"]["alto-un"].asFloat();  
                } else {
                    EventLogger::AgregarEvento("ERROR: alto-un del escenario DEBE ser un real positivo, se cargaran los valores por defecto");
					//TODO:Cargar valores por defecto... Alto y ancho?
                miEscenario.altoun = ALTO_UN_DEFAULT;
                miEscenario.anchoun = ANCHO_UN_DEFAULT;
                unSonDefault = true;
                }

            }  else {

                EventLogger::AgregarEvento("ERROR: alto-un del escenario DEBE ser un real positivo, se cargaran los valores por defecto");

                //TODO:Cargar valores por defecto... Alto y ancho?
                miEscenario.altoun = ALTO_UN_DEFAULT;
                miEscenario.anchoun = ANCHO_UN_DEFAULT;
                unSonDefault = true;
            }

        } else {
            EventLogger::AgregarEvento("ERROR: alto-un del escenario NO existe en el archivo, se cargaran los valores por defecto");

            //TODO:Cargar valores por defecto... Alto y ancho?
            miEscenario.altoun = ALTO_UN_DEFAULT;
            miEscenario.anchoun = ANCHO_UN_DEFAULT;
            unSonDefault = true;

        }
        /*************************************************************************************************/ 

        /*************************************************************************************************/ 
        //VALIDACIONES: ancho-un 
        //SI EXISTE
        if(!root["escenario"]["ancho-un"].isNull()){

            //SI ES UN ENTERO
            if(root["escenario"]["ancho-un"].isDouble()){

                if(root["escenario"]["ancho-un"].asFloat()>=0){
                    if(!unSonDefault)
                        miEscenario.anchoun = root["escenario"]["ancho-un"].asFloat();  
                } else {
                    EventLogger::AgregarEvento("ERROR: ancho-un del escenario DEBE ser un real positivo, se cargaran los valores por defecto");
					//TODO:Cargar valores por defecto... Alto y ancho?
                miEscenario.altoun = ALTO_UN_DEFAULT;
                miEscenario.anchoun = ANCHO_UN_DEFAULT;
                unSonDefault = true;
                }

            }  else {

                EventLogger::AgregarEvento("ERROR: ancho-un del escenario DEBE ser un real positivo, se cargaran los valores por defecto");

                //TODO:Cargar valores por defecto... Alto y ancho?
                miEscenario.altoun = ALTO_UN_DEFAULT;
                miEscenario.anchoun = ANCHO_UN_DEFAULT;
                unSonDefault = true;

            }

        } else {
            EventLogger::AgregarEvento("ERROR: ancho-un del escenario NO existe en el archivo, se cargaran los valores por defecto");

            //TODO:Cargar valores por defecto... Alto y ancho?
            miEscenario.altoun = ALTO_UN_DEFAULT;
            miEscenario.anchoun = ANCHO_UN_DEFAULT;
            unSonDefault = true;

        }
        /*************************************************************************************************/ 


        /*************************************************************************************************/ 
        //Validaciones string imagen_fondo


        if(!root["escenario"]["imagen_fondo"].isNull()){

            if(root["escenario"]["imagen_fondo"].isString()){

                miEscenario.imagen_fondo = root["escenario"]["imagen_fondo"].asString();  			

                //Validar si existe o tiene una extension invalida

                if (!Funciones::esUnaImagenValida(miEscenario.imagen_fondo)){
                    EventLogger::AgregarEvento("ERROR: imagen_fondo del escenario NO existe o tiene una extension invalida");
                    //Cargar imagen fondo por defecto

					 if (Funciones::esUnaImagenValida(IMAGEN_DEFAULT)){ 
						 miEscenario.imagen_fondo=IMAGEN_DEFAULT;
					 } else {
					 EventLogger::AgregarEvento("ERROR: imagen_fondo del escenario DEFAULT NO existe o tiene una extension invalida");
					 }
						 

                    
                }


            }  else {
                EventLogger::AgregarEvento("ERROR: imagen_fondo del escenario DEBE ser un string");
                //Cargar imagen fondo por defecto
                miEscenario.imagen_fondo = IMAGEN_DEFAULT;
            }

        }
        else {
            EventLogger::AgregarEvento("ERROR: imagen_fondo del escenario no existe");
            //Cargar imagen fondo por defecto
            miEscenario.imagen_fondo = IMAGEN_DEFAULT;
        }

        /*************************************************************************************************/ 

        /*************************************************************************************************/ 
        //VALIDACIONES: personajeX
        //SI EXISTE
        if(!root["escenario"]["personaje"]["x"].isNull()){

            //SI ES UN ENTERO
            if(root["escenario"]["personaje"]["x"].isDouble()){

                if(root["escenario"]["personaje"]["x"].asFloat()>=0){
                    if(!personajeSonDefault)
                        miEscenario.personajeX = root["escenario"]["personaje"]["x"].asFloat();  
                } else {
                    EventLogger::AgregarEvento("ERROR: personaje x DEBE ser un real positivo, se cargaran los valores por defecto");
					//TODO:Cargar valores por defecto..
                miEscenario.personajeX = PERSONAJE_X_DEFAULT;
                miEscenario.personajeY =	PERSONAJE_Y_DEFAULT;
                personajeSonDefault = true;
                }

            }  else {

                EventLogger::AgregarEvento("ERROR: personaje x DEBE ser un real positivo, se cargaran los valores por defecto");

                //TODO:Cargar valores por defecto..
                miEscenario.personajeX = PERSONAJE_X_DEFAULT;
                miEscenario.personajeY =	PERSONAJE_Y_DEFAULT;
                personajeSonDefault = true;

            }

        } else {
            EventLogger::AgregarEvento("ERROR: personaje x NO existe en el archivo, se cargaran los valores por defecto");

            //TODO:Cargar valores por defecto..
            miEscenario.personajeX = PERSONAJE_X_DEFAULT;
            miEscenario.personajeY =	PERSONAJE_Y_DEFAULT;
            personajeSonDefault = true;

        }
        /*************************************************************************************************/ 


        /*************************************************************************************************/ 
        //VALIDACIONES: personajeY
        //SI EXISTE
        if(!root["escenario"]["personaje"]["y"].isNull()){

            //SI ES UN ENTERO
            if(root["escenario"]["personaje"]["y"].isDouble()){

                if(root["escenario"]["personaje"]["y"].asFloat()>=0){
                    if(!personajeSonDefault)
                        miEscenario.personajeY = root["escenario"]["personaje"]["y"].asFloat();  
                } else {
                    EventLogger::AgregarEvento("ERROR: personaje y DEBE ser un real positivo, se cargaran los valores por defecto");
					//TODO:Cargar valores por defecto..
                miEscenario.personajeX = PERSONAJE_X_DEFAULT;
                miEscenario.personajeY =	PERSONAJE_Y_DEFAULT;
                personajeSonDefault = true;
                }

            }  else {

                EventLogger::AgregarEvento("ERROR: personaje y DEBE ser un real positivo, se cargaran los valores por defecto");

                //TODO:Cargar valores por defecto..
                miEscenario.personajeX = PERSONAJE_X_DEFAULT;
                miEscenario.personajeY =	PERSONAJE_Y_DEFAULT;
                personajeSonDefault = true;

            }

        } else {
            EventLogger::AgregarEvento("ERROR: personaje y NO existe en el archivo, se cargaran los valores por defecto");

            //TODO:Cargar valores por defecto..
            miEscenario.personajeX = PERSONAJE_X_DEFAULT;
            miEscenario.personajeY =	PERSONAJE_Y_DEFAULT;
            personajeSonDefault = true;

        }
        /*************************************************************************************************/ 

        /*************************************************************************************************/ 

        //COUTS ESCENARIO



        /*************************************************************************************************/ 

        //OBJETOS

        if (root["escenario"]["objetos"].isNull()){
            EventLogger::AgregarEvento("WARNING: no hay objetos declarados");

            //TODO:cargar objetos default....


        }

        // Si entra es porque tiene/Existe objetos 
        if (!root["escenario"]["objetos"].isNull())  {

            int objetos_size = root["escenario"]["objetos"].size();  

            string notice = "NOTICE: Hay ";
            notice.append(Funciones::intToString(objetos_size));
            notice.append(" objetos declarados.");

            EventLogger::AgregarEvento(notice);


            //   Recorro la lista de objetos
            for(int i = 0; i < objetos_size; ++i)  
            {  
                if(root["escenario"]["objetos"][i]["tipo"].isNull()){
                    EventLogger::AgregarEvento("ERROR: No es un objeto valido, no se cargara");
                }
                else {

                    if(!root["escenario"]["objetos"][i]["tipo"].isString()){
                        EventLogger::AgregarEvento("ERROR: tipo DEBE ser un string");
                    } else {

                        string tipo = root["escenario"]["objetos"][i]["tipo"].asString();


                        if( tipo == "poli"){

                            poli poli;
                            poli.tipo = tipo;
                            bool pxpEsDefault = false;
							bool errorPoli = false;
							
                            /*************************************************************************************************/ 
                            //VALIDACIONES: poli-x
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["x"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["x"].isDouble()){

                                    if(root["escenario"]["objetos"][i]["x"].asFloat()>=0){

                                        if(!pxpEsDefault)
                                            poli.x = root["escenario"]["objetos"][i]["x"].asFloat();  
                                    } else {
                                        EventLogger::AgregarEvento("ERROR: x del poligono DEBE ser un real positivo, se omitira el elemento");
										//TODO:Cargar valores por defecto..
                                    poli.x = POLIGONO_X_DEFAULT;
                                    poli.y = POLIGONO_Y_DEFAULT;
                                    pxpEsDefault = true;
									errorPoli = true;
                                    }

                                }  else {

                                    EventLogger::AgregarEvento("ERROR: x del poligono DEBE ser un real positivo, se omitira el elemento");

                                    //TODO:Cargar valores por defecto..
                                    poli.x = POLIGONO_X_DEFAULT;
                                    poli.y = POLIGONO_Y_DEFAULT;
                                    pxpEsDefault = true;
									errorPoli = true;

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: x del poligono NO existe en el archivo, se omitira el elemento");

                                //TODO:Cargar valores por defecto..
                                poli.x = POLIGONO_X_DEFAULT;
                                poli.y = POLIGONO_Y_DEFAULT;
                                pxpEsDefault = true;
								errorPoli = true;
                            }
                            /*************************************************************************************************/ 

                            /*************************************************************************************************/ 
                            //VALIDACIONES: poli-y
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["y"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["y"].isDouble()){

                                    if(root["escenario"]["objetos"][i]["y"].asFloat()>=0){
                                        if(!pxpEsDefault)
                                            poli.y = root["escenario"]["objetos"][i]["y"].asFloat();  
                                    } else {
                                        EventLogger::AgregarEvento("ERROR: y del poligono DEBE ser un real positivo, se omitira el elemento");
										//TODO:Cargar valores por defecto..
                                    poli.x = POLIGONO_X_DEFAULT;
                                    poli.y = POLIGONO_Y_DEFAULT;
                                    pxpEsDefault = true;
									errorPoli = true;
                                    }

                                }  else {

                                    EventLogger::AgregarEvento("ERROR: y del poligono DEBE ser un real positivo, se omitira el elemento");

                                    //TODO:Cargar valores por defecto..
                                    poli.x = POLIGONO_X_DEFAULT;
                                    poli.y = POLIGONO_Y_DEFAULT;
                                    pxpEsDefault = true;
									errorPoli = true;

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: y del poligono NO existe en el archivo, se omitira el elemento");

                                //TODO:Cargar valores por defecto..
                                poli.x = POLIGONO_X_DEFAULT;
                                poli.y = POLIGONO_Y_DEFAULT;
                                pxpEsDefault = true;
								errorPoli = true;

                            }
                            /*************************************************************************************************/ 

                            /*************************************************************************************************/ 
                            //VALIDACIONES: poli-escala
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["escala"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["escala"].isDouble()){

                                    if(root["escenario"]["objetos"][i]["escala"].asFloat()>=0){
                                        poli.escala = root["escenario"]["objetos"][i]["escala"].asFloat();  
                                    }else {
                                        EventLogger::AgregarEvento("ERROR: escala del poligono DEBE ser un real positivo, se omitira el elemento");
										 //TODO:Cargar valores por defecto..
                                    poli.escala = POLIGONO_ESCALA_DEFAULT;
									errorPoli = true;
                                    }

                                }  else {

                                    EventLogger::AgregarEvento("ERROR: escala del poligono DEBE ser un float, se omitira el elemento");

                                    //TODO:Cargar valores por defecto..
                                    poli.escala = POLIGONO_ESCALA_DEFAULT;
									errorPoli = true;


                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: escala del poligono NO existe en el archivo, se omitira el elemento");

                                //TODO:Cargar valores por defecto..
                                poli.escala = POLIGONO_ESCALA_DEFAULT;
								errorPoli = true;

                            }
                            /*************************************************************************************************/ 
                            /*************************************************************************************************/ 
                            //VALIDACIONES: poli-lados
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["lados"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["lados"].isInt()){

                                    if (root["escenario"]["objetos"][i]["lados"].asInt() >=3 && root["escenario"]["objetos"][i]["lados"].asInt() <=6){

                                        poli.lados = root["escenario"]["objetos"][i]["lados"].asInt(); }

                                    else {

                                        EventLogger::AgregarEvento("ERROR: lados del poligono DEBE ser entero entre 3 y 6, se omitira el elemento");

                                        //TODO:Cargar valores por defecto..
                                        poli.lados = POLIGONO_LADOS_DEFAULT;
										errorPoli = true;


                                    }


                                }  else {

                                    EventLogger::AgregarEvento("ERROR: lados del poligono DEBE ser un entero, se omitira el elemento");

                                    //TODO:Cargar valores por defecto..
                                    poli.lados = POLIGONO_LADOS_DEFAULT;
									errorPoli = true;


                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: lados del poligono NO existe en el archivo, se omitira el elemento");

                                //TODO:Cargar valores por defecto..
                                poli.lados = POLIGONO_LADOS_DEFAULT;
								errorPoli = true;

                            }
                            /*************************************************************************************************/ 

                            /*************************************************************************************************/ 
                            //VALIDACIONES: poli-color
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["color"].isNull()){

                                //SI ES UN STRING
                                if( root["escenario"]["objetos"][i]["color"].isString()){

                                    if( Funciones::esHEXvalido(root["escenario"]["objetos"][i]["color"].asString()) ){

                                        string colorHEX = root["escenario"]["objetos"][i]["color"].asString();

                                        //Si es un hex valido....
                                        poli.color.r = Funciones::hexToRGB(colorHEX).r;
                                        poli.color.g = Funciones::hexToRGB(colorHEX).g;
                                        poli.color.b = Funciones::hexToRGB(colorHEX).b;


                                    }  else {

                                        EventLogger::AgregarEvento("ERROR: color del poligono DEBE ser un HEX VALIDO, se cargaran los valores por defecto");

                                        //TODO:Cargar valores por defecto..
                                        poli.color.r = R_DEFAULT;
                                        poli.color.g = G_DEFAULT;
                                        poli.color.b = B_DEFAULT;

                                    } }
                                else {

                                    EventLogger::AgregarEvento("ERROR: color del poligono DEBE ser un string, se cargaran los valores por defecto");
                                    //TODO:Cargar valores por defecto..
                                    poli.color.r = R_DEFAULT;
                                    poli.color.g = G_DEFAULT;
                                    poli.color.b = B_DEFAULT;
                                }



                            }  else {
                                EventLogger::AgregarEvento("ERROR: color del poligono NO existe en el archivo, se cargaran los valores por defecto");

                                //TODO:Cargar valores por defecto..
                                poli.color.r = R_DEFAULT;
                                poli.color.g = G_DEFAULT;
                                poli.color.b = B_DEFAULT;

                            }
                            /*************************************************************************************************/ 

                            /*************************************************************************************************/ 
                            //VALIDACIONES: poli-rot
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["rot"].isNull()){



								


                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["rot"].isInt()){

                                    

									if (root["escenario"]["objetos"][i]["rot"].asInt() >=0 && root["escenario"]["objetos"][i]["rot"].asInt() <=359){

                                        poli.rot = root["escenario"]["objetos"][i]["rot"].asInt();  

								} else {

                                        EventLogger::AgregarEvento("ERROR: rot del poligono DEBE ser entero entre 0 y 359, se omitira el elemento");

                                        //TODO:Cargar valores por defecto..
                                        poli.rot= POLIGONO_ROT_DEFAULT;
										errorPoli = true;


                                    }



                                }  else {

                                    EventLogger::AgregarEvento("ERROR: rot del poligono DEBE ser un entero, se omitira el elemento");

                                    //TODO:Cargar valores por defecto..
                                    poli.rot = POLIGONO_ROT_DEFAULT;
									errorPoli = true;
                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: rot del poligono NO existe en el archivo, se omitira el elemento");

                                //TODO:Cargar valores por defecto..
                                poli.rot = POLIGONO_ROT_DEFAULT;
								errorPoli = true;


                            }
                            /*************************************************************************************************/ 


                            /*************************************************************************************************/ 
                            //VALIDACIONES: poli-masa
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["masa"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["masa"].isDouble()){

                                    if(root["escenario"]["objetos"][i]["masa"].asFloat()>=0){

                                        poli.masa = root["escenario"]["objetos"][i]["masa"].asFloat();  
                                    } else {
                                        EventLogger::AgregarEvento("ERROR: masa del poligono DEBE ser un real positivo, se omitira el elemento");
										//TODO:Cargar valores por defecto..
                                    poli.masa = POLIGONO_MASA_DEFAULT;
									errorPoli = true;
                                    }

                                }  else {

                                    EventLogger::AgregarEvento("ERROR: masa del poligono DEBE ser un real positivo, se omitira el elemento");

                                    //TODO:Cargar valores por defecto..
                                    poli.masa = POLIGONO_MASA_DEFAULT;
									errorPoli = true;

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: masa del poligono NO existe en el archivo, se omitira el elemento");

                                //TODO:Cargar valores por defecto..
                                poli.masa = POLIGONO_MASA_DEFAULT;
								errorPoli = true;


                            }
                            /*************************************************************************************************/

                            /*************************************************************************************************/ 
                            //VALIDACIONES: poli-estatico
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["estatico"].isNull()){

                                //SI ES UN booleano
                                if(root["escenario"]["objetos"][i]["estatico"].isBool()){

                                    poli.estatico = root["escenario"]["objetos"][i]["estatico"].asBool();  


                                }  else {

                                    EventLogger::AgregarEvento("ERROR: estatico del poligono DEBE ser un booleano, se omitira el elemento");

                                    //TODO:Cargar valores por defecto..
                                    poli.estatico = POLIGONO_ESTATICO_DEFAULT;
									errorPoli = true;

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: estatico del poligono NO existe en el archivo, se omitira el elemento");

                                //TODO:Cargar valores por defecto..
                                poli.estatico = POLIGONO_ESTATICO_DEFAULT;
								errorPoli = true;


                            }
                            /*************************************************************************************************/ 						
							if (!errorPoli){
                            miEscenario.poligonos.push_back(poli);
							}
                            /*
                            //COUTS POLIGONOS
                            cout << endl << "Objeto Nro: " << i << endl;
                            cout << endl << "tipo " << poli.tipo << endl;
                            cout << endl << "x " << poli.x << endl;
                            cout << endl << "y " << poli.y << endl;
                            cout << endl << "ancho " << poli.ancho << endl;
                            cout << endl << "alto " << poli.alto << endl;

                            //cout << endl << "color HEX " << colorHEX << "color RGB R:" << Funciones::hexToRGB(colorHEX).r << "G:" << Funciones::hexToRGB(colorHEX).g << "B:" << Funciones::hexToRGB(colorHEX).b << endl;
                            cout << endl << "rot " << poli.rot << endl;
                            cout << endl << "masa " << poli.masa << endl;
                            cout << endl << "estatico " << poli.estatico << endl;      
                            */


                        } 

                        else if( tipo=="rect"){

                            rect rect;
                            rect.tipo = tipo;
                            bool pxrEsDefault = false;
                            bool psrEsDefault = false;
							bool errorRect = false;
							
                            /*************************************************************************************************/ 
                            //VALIDACIONES: rect-x
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["x"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["x"].isDouble()){

                                    if(root["escenario"]["objetos"][i]["x"].asFloat()>=0){

                                        if(!pxrEsDefault)
                                            rect.x = root["escenario"]["objetos"][i]["x"].asFloat();  
                                    } else {
                                        EventLogger::AgregarEvento("ERROR: x del rectangulo DEBE ser un real positivo, se omitira el elemento");
										 //TODO:Cargar valores por defecto..
                                    rect.x = RECTANGULO_X_DEFAULT;
                                    rect.y = RECTANGULO_Y_DEFAULT;
                                    pxrEsDefault = true;
									errorRect = true;

                                    }

                                }  else {

                                    EventLogger::AgregarEvento("ERROR: x del rectangulo DEBE ser un real positivo, se omitira el elemento");

                                    //TODO:Cargar valores por defecto..
                                    rect.x = RECTANGULO_X_DEFAULT;
                                    rect.y = RECTANGULO_Y_DEFAULT;
                                    pxrEsDefault = true;
									errorRect = true;

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: x del rectangulo NO existe en el archivo, se omitira el elemento");

                                //TODO:Cargar valores por defecto..
                                rect.x = RECTANGULO_X_DEFAULT;
                                rect.y = RECTANGULO_Y_DEFAULT;
                                pxrEsDefault = true;
								errorRect = true;

                            }
                            /*************************************************************************************************/ 

                            /*************************************************************************************************/ 
                            //VALIDACIONES: rect-y
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["y"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["y"].isDouble()){

                                    if(root["escenario"]["objetos"][i]["y"].asFloat()>=0){

                                        if(!pxrEsDefault)
                                            rect.y = root["escenario"]["objetos"][i]["y"].asFloat();  
                                    } else {
                                        EventLogger::AgregarEvento("ERROR: y del rectangulo DEBE ser un real positivo, se omitira el elemento");
										 //TODO:Cargar valores por defecto..
                                    rect.x = RECTANGULO_X_DEFAULT;
                                    rect.y = RECTANGULO_Y_DEFAULT;
                                    pxrEsDefault = true;
									errorRect = true;

                                    }


                                }  else {

                                    EventLogger::AgregarEvento("ERROR: y del rectangulo DEBE ser un real positivo, se omitira el elemento");

                                    //TODO:Cargar valores por defecto..
                                    rect.x = RECTANGULO_X_DEFAULT;
                                    rect.y = RECTANGULO_Y_DEFAULT;
                                    pxrEsDefault = true;
									errorRect = true;
                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: y del rectangulo NO existe en el archivo, se omitira el elemento");

                                //TODO:Cargar valores por defecto..
                                rect.x = RECTANGULO_X_DEFAULT;
                                rect.y = RECTANGULO_Y_DEFAULT;
                                pxrEsDefault = true;
								errorRect = true;

                            }
                            /*************************************************************************************************/ 

                            /*************************************************************************************************/ 
                            //VALIDACIONES: rect-ancho
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["ancho"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["ancho"].isDouble()){

                                    if(root["escenario"]["objetos"][i]["ancho"].asFloat()>=0){

                                        if(!psrEsDefault)
                                            rect.ancho = root["escenario"]["objetos"][i]["ancho"].asFloat();  
                                    } else {
                                        EventLogger::AgregarEvento("ERROR: ancho del rectangulo DEBE ser un real positivo, se omitira el elemento");
										 
                                   //TODO:Cargar valores por defecto..
                                    rect.ancho = RECTANGULO_ANCHO_DEFAULT;
                                    rect.alto = RECTANGULO_ALTO_DEFAULT;
                                    psrEsDefault = true;
									errorRect = true;

                                    }

                                }  else {

                                    EventLogger::AgregarEvento("ERROR: ancho del rectangulo DEBE ser un real positivo, se omitira el elemento");

                                    //TODO:Cargar valores por defecto..
                                    rect.ancho = RECTANGULO_ANCHO_DEFAULT;
                                    rect.alto = RECTANGULO_ALTO_DEFAULT;
                                    psrEsDefault = true;
									errorRect = true;

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: ancho del rectangulo NO existe en el archivo, se omitira el elemento");

                                //TODO:Cargar valores por defecto..
                                rect.ancho = RECTANGULO_ANCHO_DEFAULT;
                                rect.alto = RECTANGULO_ALTO_DEFAULT;
                                psrEsDefault = true;
								errorRect = true;

                            }
                            /*************************************************************************************************/ 
                            /*************************************************************************************************/ 
                            //VALIDACIONES: rect-alto
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["alto"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["alto"].isDouble()){

                                    if(root["escenario"]["objetos"][i]["alto"].asFloat()>=0){

                                        if(!psrEsDefault)
                                            rect.alto = root["escenario"]["objetos"][i]["alto"].asFloat();  
                                    } else {
                                        EventLogger::AgregarEvento("ERROR: alto del rectangulo DEBE ser un real positivo, se omitira el elemento");
										//TODO:Cargar valores por defecto..
                                    rect.ancho = RECTANGULO_ANCHO_DEFAULT;
                                    rect.alto = RECTANGULO_ALTO_DEFAULT;
                                    psrEsDefault = true;
									errorRect = true;
                                    }

                                }  else {

                                    EventLogger::AgregarEvento("ERROR: alto del rectangulo DEBE ser un real positivo, se omitira el elemento");

                                    //TODO:Cargar valores por defecto..
                                    rect.ancho = RECTANGULO_ANCHO_DEFAULT;
                                    rect.alto = RECTANGULO_ALTO_DEFAULT;
                                    psrEsDefault = true;
									errorRect = true;

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: alto del rectangulo NO existe en el archivo, se omitira el elemento");

                                //TODO:Cargar valores por defecto..
                                rect.ancho = RECTANGULO_ANCHO_DEFAULT;
                                rect.alto = RECTANGULO_ALTO_DEFAULT;
                                psrEsDefault = true;
								errorRect = true;

                            }
                            /*************************************************************************************************/ 

                            /*************************************************************************************************/ 
                            //VALIDACIONES: rect-color
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["color"].isNull()){

                                //SI ES UN STRING
                                if( root["escenario"]["objetos"][i]["color"].isString()){

                                    if( Funciones::esHEXvalido(root["escenario"]["objetos"][i]["color"].asString()) ){

                                        string colorHEX = root["escenario"]["objetos"][i]["color"].asString();

                                        //Si es un hex valido....
                                        rect.color.r = Funciones::hexToRGB(colorHEX).r;
                                        rect.color.g = Funciones::hexToRGB(colorHEX).g;
                                        rect.color.b = Funciones::hexToRGB(colorHEX).b;


                                    }  else {

                                        EventLogger::AgregarEvento("ERROR: color del rectangulo DEBE ser un HEX VALIDO, se cargaran los valores por defecto");

                                        //TODO:Cargar valores por defecto..
                                        rect.color.r = R_DEFAULT;
                                        rect.color.g = G_DEFAULT;
                                        rect.color.b = B_DEFAULT;

                                    } }
                                else {

                                    EventLogger::AgregarEvento("ERROR: color del rectangulo DEBE ser un string, se cargaran los valores por defecto");
                                    //TODO:Cargar valores por defecto..
                                    rect.color.r = R_DEFAULT;
                                    rect.color.g = G_DEFAULT;
                                    rect.color.b = B_DEFAULT;
                                }



                            }  else {
                                EventLogger::AgregarEvento("ERROR: color del rectangulo NO existe en el archivo, se cargaran los valores por defecto");

                                //TODO:Cargar valores por defecto..
                                rect.color.r = R_DEFAULT;
                                rect.color.g = G_DEFAULT;
                                rect.color.b = B_DEFAULT;

                            }
                            /*************************************************************************************************/ 

                            /*************************************************************************************************/ 
                            //VALIDACIONES: rect-rot
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["rot"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["rot"].isInt()){

                                    

									if (root["escenario"]["objetos"][i]["rot"].asInt() >=0 && root["escenario"]["objetos"][i]["rot"].asInt() <=359){

                                        rect.rot = root["escenario"]["objetos"][i]["rot"].asInt();    

								} else {

                                        EventLogger::AgregarEvento("ERROR: rot del poligono DEBE ser entero entre 0 y 359, se omitira el elemento");

                                        //TODO:Cargar valores por defecto..
                                        rect.rot = RECTANGULO_ROT_DEFAULT;  
										errorRect = true;


                                    }


                                }  else {

                                    EventLogger::AgregarEvento("ERROR: rot del rectangulo DEBE ser un entero, se omitira el elemento");

                                    //TODO:Cargar valores por defecto..
                                    rect.rot = RECTANGULO_ROT_DEFAULT;
									errorRect = true;

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: rot del rectangulo NO existe en el archivo, se omitira el elemento");

                                //TODO:Cargar valores por defecto..
                                rect.rot = RECTANGULO_ROT_DEFAULT;
								errorRect = true;


                            }
                            /*************************************************************************************************/ 


                            /*************************************************************************************************/ 
                            //VALIDACIONES: rect-masa
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["masa"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["masa"].isDouble()){

                                    if(root["escenario"]["objetos"][i]["masa"].asFloat()>=0){

                                        rect.masa = root["escenario"]["objetos"][i]["masa"].asFloat();  
                                    } else {
                                        EventLogger::AgregarEvento("ERROR: masa del rectangulo DEBE ser un real positivo, se omitira el elemento");
										//TODO:Cargar valores por defecto..
                                    rect.masa = RECTANGULO_MASA_DEFAULT;
									errorRect = true;
                                    }

                                }  else {

                                    EventLogger::AgregarEvento("ERROR: masa del rectangulo DEBE ser un real positivo, se omitira el elemento");

                                    //TODO:Cargar valores por defecto..
                                    rect.masa = RECTANGULO_MASA_DEFAULT;
									errorRect = true;
                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: masa del rectangulo NO existe en el archivo, se omitira el elemento");

                                //TODO:Cargar valores por defecto..
                                rect.masa = RECTANGULO_MASA_DEFAULT;
								errorRect = true;

                            }
                            /*************************************************************************************************/

                            /*************************************************************************************************/ 
                            //VALIDACIONES: rect-estatico
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["estatico"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["estatico"].isBool()){

                                    rect.estatico = root["escenario"]["objetos"][i]["estatico"].asBool();  


                                }  else {

                                    EventLogger::AgregarEvento("ERROR: estatico del rectangulo DEBE ser un booleano, se omitira el elemento");

                                    //TODO:Cargar valores por defecto..
                                    rect.estatico = RECTANGULO_ESTATICO_DEFAULT;
									errorRect = true;
                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: estatico del rectangulo NO existe en el archivo, se omitira el elemento");

                                //TODO:Cargar valores por defecto..
                                rect.estatico = RECTANGULO_ESTATICO_DEFAULT;
								errorRect = true;

                            }
                            /*************************************************************************************************/ 						
							if(!errorRect){
                            miEscenario.rectangulos.push_back(rect);
							}



                        }
                        else if( tipo=="circ"){
                            circ circulo;
                            circulo.tipo = tipo;
                            bool cxEsDefault = false;
							bool errorCirc = false;

                            /*************************************************************************************************/ 
                            //VALIDACIONES: circulo-x
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["x"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["x"].isDouble()){

                                    if(root["escenario"]["objetos"][i]["x"].asFloat()>=0){

                                        if(!cxEsDefault)
                                            circulo.x = root["escenario"]["objetos"][i]["x"].asFloat();  

                                    } else {
                                        EventLogger::AgregarEvento("ERROR: x del circulo DEBE ser un real positivo, se omitira el elemento");

										//TODO:Cargar valores por defecto..
                                    circulo.x = CIRCULO_X_DEFAULT;
                                    circulo.y = CIRCULO_Y_DEFAULT;
                                    cxEsDefault = true;
									errorCirc = true;

                                    }

                                }  else {

                                    EventLogger::AgregarEvento("ERROR: x del circulo DEBE ser un real positivo, se omitira el elemento");

                                    //TODO:Cargar valores por defecto..
                                    circulo.x = CIRCULO_X_DEFAULT;
                                    circulo.y = CIRCULO_Y_DEFAULT;
                                    cxEsDefault = true;
									errorCirc = true;

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: x del circulo NO existe en el archivo, se omitira el elemento");

                                //TODO:Cargar valores por defecto..
                                circulo.x = CIRCULO_X_DEFAULT;
                                circulo.y = CIRCULO_Y_DEFAULT;
                                cxEsDefault = true;
								errorCirc = true;
                            }
                            /*************************************************************************************************/ 

                            /*************************************************************************************************/ 
                            //VALIDACIONES: circulo-y
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["y"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["y"].isDouble()){

                                    if(root["escenario"]["objetos"][i]["y"].asFloat()>=0){
                                        if(!cxEsDefault)
                                            circulo.y = root["escenario"]["objetos"][i]["y"].asFloat();  
                                    } else {
                                        EventLogger::AgregarEvento("ERROR: y del circulo DEBE ser un real positivo, se omitira el elemento");
										//TODO:Cargar valores por defecto..
                                    circulo.x = CIRCULO_X_DEFAULT;
                                    circulo.y = CIRCULO_Y_DEFAULT;
                                    cxEsDefault = true;
									errorCirc = true;

                                    }

                                }  else {

                                    EventLogger::AgregarEvento("ERROR: y del circulo DEBE ser un real positivo, se omitira el elemento");

                                    //TODO:Cargar valores por defecto..
                                    circulo.x = CIRCULO_X_DEFAULT;
                                    circulo.y = CIRCULO_Y_DEFAULT;
                                    cxEsDefault = true;
									errorCirc = true;

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: y del circulo NO existe en el archivo, se omitira el elemento");

                                //TODO:Cargar valores por defecto..
                                circulo.x = CIRCULO_X_DEFAULT;
                                circulo.y = CIRCULO_Y_DEFAULT;
                                cxEsDefault = true;
								errorCirc = true;

                            }
                            /*************************************************************************************************/ 


                            /*************************************************************************************************/ 
                            //VALIDACIONES: circulo-radio
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["radio"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["radio"].isDouble()){
                                    
									if (root["escenario"]["objetos"][i]["radio"].asFloat() > 0) {
                                        circulo.radio = root["escenario"]["objetos"][i]["radio"].asFloat(); 
									} else {

                                    EventLogger::AgregarEvento("ERROR: radio del circulo DEBE ser un real positivo, se omitira el elemento");

                                    //TODO:Cargar valores por defecto..
                                    circulo.radio = CIRCULO_RADIO_DEFAULT;
									errorCirc = true;


                                }


                                }  else {

                                    EventLogger::AgregarEvento("ERROR: radio del circulo DEBE ser un real positivo, se omitira el elemento");

                                    //TODO:Cargar valores por defecto..
                                    circulo.radio = CIRCULO_RADIO_DEFAULT;
									errorCirc = true;


                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: alto del circulo NO existe en el archivo, se omitira el elemento");

                                //TODO:Cargar valores por defecto..
                                circulo.radio = CIRCULO_RADIO_DEFAULT;
								errorCirc = true;

                            }
                            /*************************************************************************************************/ 

                            /*************************************************************************************************/ 
                            //VALIDACIONES: circulo-color
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["color"].isNull()){

                                //SI ES UN STRING
                                if( root["escenario"]["objetos"][i]["color"].isString()){

                                    if( Funciones::esHEXvalido(root["escenario"]["objetos"][i]["color"].asString()) ){

                                        string colorHEX = root["escenario"]["objetos"][i]["color"].asString();

                                        //Si es un hex valido....
                                        circulo.color.r = Funciones::hexToRGB(colorHEX).r;
                                        circulo.color.g = Funciones::hexToRGB(colorHEX).g;
                                        circulo.color.b = Funciones::hexToRGB(colorHEX).b;


                                    }  else {

                                        EventLogger::AgregarEvento("ERROR: color del circulo DEBE ser un HEX VALIDO, se cargaran los valores por defecto");

                                        //TODO:Cargar valores por defecto..
                                        circulo.color.r = R_DEFAULT;
                                        circulo.color.g = G_DEFAULT;
                                        circulo.color.b = B_DEFAULT;

                                    } }
                                else {

                                    EventLogger::AgregarEvento("ERROR: color del circulo DEBE ser un string, se cargaran los valores por defecto");
                                    //TODO:Cargar valores por defecto..
                                    circulo.color.r = R_DEFAULT;
                                    circulo.color.g = G_DEFAULT;
                                    circulo.color.b = B_DEFAULT;
                                }



                            }  else {
                                EventLogger::AgregarEvento("ERROR: color del circulo NO existe en el archivo, se cargaran los valores por defecto");

                                //TODO:Cargar valores por defecto..
                                circulo.color.r = R_DEFAULT;
                                circulo.color.g = G_DEFAULT;
                                circulo.color.b = B_DEFAULT;

                            }
                            /*************************************************************************************************/ 


                            /*************************************************************************************************/ 
                            //VALIDACIONES: circulo-masa
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["masa"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["masa"].isDouble()){

                                    if(root["escenario"]["objetos"][i]["masa"].asFloat()>=0){

                                        circulo.masa = root["escenario"]["objetos"][i]["masa"].asFloat();  
                                    } else {
                                        EventLogger::AgregarEvento("ERROR: masa del circulo DEBE ser un real positivo, se omitira el elemento");

										//TODO:Cargar valores por defecto..
                                    circulo.masa = CIRCULO_MASA_DEFAULT;
									errorCirc = true;
                                    }

                                }  else {

                                    EventLogger::AgregarEvento("ERROR: masa del circulo DEBE ser un real positivo, se omitira el elemento");

                                    //TODO:Cargar valores por defecto..
                                    circulo.masa = CIRCULO_MASA_DEFAULT;
									errorCirc = true;

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: masa del circulo NO existe en el archivo, se omitira el elemento");

                                //TODO:Cargar valores por defecto..
                                circulo.masa = CIRCULO_MASA_DEFAULT;
								errorCirc = true;


                            }
                            /*************************************************************************************************/

                            /*************************************************************************************************/ 
                            //VALIDACIONES: circulo-estatico
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["estatico"].isNull()){

                                //SI ES UN booleano
                                if(root["escenario"]["objetos"][i]["estatico"].isBool()){

                                    circulo.estatico = root["escenario"]["objetos"][i]["estatico"].asBool();  


                                }  else {

                                    EventLogger::AgregarEvento("ERROR: estatico del circulo DEBE ser un booleano, se omitira el elemento");

                                    //TODO:Cargar valores por defecto..
                                    circulo.estatico = CIRCULO_ESTATICO_DEFAULT;
									errorCirc = true;
                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: estatico del circulo NO existe en el archivo, se omitira el elemento");

                                //TODO:Cargar valores por defecto..
                                circulo.estatico = CIRCULO_ESTATICO_DEFAULT;
								errorCirc = true;

                            }
                            /*************************************************************************************************/ 						
							if(!errorCirc){
                            miEscenario.circulos.push_back(circulo);
							}
                        }
                        else if( tipo=="paralel"){
                            paralel paralel;
                            paralel.tipo = tipo;
                            bool pxrEsDefault = false;
                            bool psrEsDefault = false;
							bool errorParalel = false;
							
                            /*************************************************************************************************/ 
                            //VALIDACIONES: paralel-x
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["x"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["x"].isDouble()){

                                    if(root["escenario"]["objetos"][i]["x"].asFloat()>=0){

                                        if(!pxrEsDefault)
                                            paralel.x = root["escenario"]["objetos"][i]["x"].asFloat();  
                                    } else {
                                        EventLogger::AgregarEvento("ERROR: x del paralelogramo DEBE ser un real positivo, se omitira el elemento");
										//TODO:Cargar valores por defecto..
                                    paralel.x = PARALELOGRAMO_X_DEFAULT;
                                    paralel.y = PARALELOGRAMO_Y_DEFAULT;
                                    pxrEsDefault = true;
									errorParalel = true;
                                    }

                                }  else {

                                    EventLogger::AgregarEvento("ERROR: x del paralelogramo DEBE ser un real positivo, se omitira el elemento");

                                    //TODO:Cargar valores por defecto..
                                    paralel.x = PARALELOGRAMO_X_DEFAULT;
                                    paralel.y = PARALELOGRAMO_Y_DEFAULT;
                                    pxrEsDefault = true;
									errorParalel = true;

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: x del paralelogramo NO existe en el archivo, se omitira el elemento");

                                //TODO:Cargar valores por defecto..
                                paralel.x = PARALELOGRAMO_X_DEFAULT;
                                paralel.y = PARALELOGRAMO_Y_DEFAULT;
                                pxrEsDefault = true;
								errorParalel = true;

                            }
                            /*************************************************************************************************/ 

                            /*************************************************************************************************/ 
                            //VALIDACIONES: paralel-y
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["y"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["y"].isDouble()){

                                    if(root["escenario"]["objetos"][i]["y"].asFloat()>=0){

                                        if(!pxrEsDefault)
                                            paralel.y = root["escenario"]["objetos"][i]["y"].asFloat();  
                                    } else {
                                        EventLogger::AgregarEvento("ERROR: y del paralelogramo DEBE ser un real positivo, se omitira el elemento");
										//TODO:Cargar valores por defecto..
                                    paralel.x = PARALELOGRAMO_X_DEFAULT;
                                    paralel.y = PARALELOGRAMO_Y_DEFAULT;
                                    pxrEsDefault = true;
									errorParalel = true;
                                    }


                                }  else {

                                    EventLogger::AgregarEvento("ERROR: y del paralelogramo DEBE ser un real positivo, se omitira el elemento");

                                    //TODO:Cargar valores por defecto..
                                    paralel.x = PARALELOGRAMO_X_DEFAULT;
                                    paralel.y = PARALELOGRAMO_Y_DEFAULT;
                                    pxrEsDefault = true;
									errorParalel = true;

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: y del paralelogramo NO existe en el archivo, se omitira el elemento");

                                //TODO:Cargar valores por defecto..
                                paralel.x = PARALELOGRAMO_X_DEFAULT;
                                paralel.y = PARALELOGRAMO_Y_DEFAULT;
                                pxrEsDefault = true;
								errorParalel = true;

                            }
                            /*************************************************************************************************/ 

                            /*************************************************************************************************/ 
                            //VALIDACIONES: paralel-lado1
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["lado1"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["lado1"].isDouble()){

                                    if(root["escenario"]["objetos"][i]["lado1"].asFloat()>=0){

                                        if(!psrEsDefault)
                                            paralel.lado1 = root["escenario"]["objetos"][i]["lado1"].asFloat();  
                                    } else {
                                        EventLogger::AgregarEvento("ERROR: lado1 del paralelogramo DEBE ser un real positivo, se omitira el elemento");
										 //TODO:Cargar valores por defecto..
                                    paralel.lado1 = PARALELOGRAMO_LONGLADO1_DEFAULT;
                                    paralel.lado2 = PARALELOGRAMO_LONGLADO2_DEFAULT;
                                    psrEsDefault = true;
									errorParalel = true;
                                    }

                                }  else {

                                    EventLogger::AgregarEvento("ERROR: lado1 del paralelogramo DEBE ser un real positivo, se omitira el elemento");

                                    //TODO:Cargar valores por defecto..
                                    paralel.lado1 = PARALELOGRAMO_LONGLADO1_DEFAULT;
                                    paralel.lado2 = PARALELOGRAMO_LONGLADO2_DEFAULT;
                                    psrEsDefault = true;
									errorParalel = true;

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: lado1 del paralelogramo NO existe en el archivo, se omitira el elemento");

                                //TODO:Cargar valores por defecto..
                                 paralel.lado1 = PARALELOGRAMO_LONGLADO1_DEFAULT;
                                    paralel.lado2 = PARALELOGRAMO_LONGLADO2_DEFAULT;
                                psrEsDefault = true;
								errorParalel = true;

                            }
                            /*************************************************************************************************/ 
                            /*************************************************************************************************/ 
                            //VALIDACIONES: paralel-lado2
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["lado2"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["lado2"].isDouble()){

                                    if(root["escenario"]["objetos"][i]["lado2"].asFloat()>=0){

                                        if(!psrEsDefault)
                                            paralel.lado2 = root["escenario"]["objetos"][i]["lado2"].asFloat();  
                                    } else {
                                        EventLogger::AgregarEvento("ERROR: lado2 del paralelogramo DEBE ser un real positivo, se omitira el elemento");
										 //TODO:Cargar valores por defecto..
                                    paralel.lado1 = PARALELOGRAMO_LONGLADO1_DEFAULT;
                                    paralel.lado2 = PARALELOGRAMO_LONGLADO2_DEFAULT;
                                    psrEsDefault = true;
									errorParalel = true;
                                    }

                                }  else {

                                    EventLogger::AgregarEvento("ERROR: lado2 del paralelogramo DEBE ser un real positivo, se omitira el elemento");

                                    //TODO:Cargar valores por defecto..
                                    paralel.lado1 = PARALELOGRAMO_LONGLADO1_DEFAULT;
                                    paralel.lado2 = PARALELOGRAMO_LONGLADO2_DEFAULT;
                                    psrEsDefault = true;
									errorParalel = true;

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: lado2 del paralelogramo NO existe en el archivo, se omitira el elemento");

                                //TODO:Cargar valores por defecto..
                                paralel.lado1 = PARALELOGRAMO_LONGLADO1_DEFAULT;
                                    paralel.lado2 = PARALELOGRAMO_LONGLADO2_DEFAULT;
                                psrEsDefault = true;
								errorParalel = true;

                            }
                            /*************************************************************************************************/ 
                /*************************************************************************************************/ 
                            //VALIDACIONES: paralel-altura
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["altura"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["altura"].isDouble()){

                                    if(root["escenario"]["objetos"][i]["altura"].asFloat()>=0){

                                        if(!psrEsDefault)
                                            paralel.altura = root["escenario"]["objetos"][i]["altura"].asFloat();  
                                    } else {
                                        EventLogger::AgregarEvento("ERROR: altura del paralelogramo DEBE ser un real positivo, se omitira el elemento");
										
                                    //TODO:Cargar valores por defecto..
                                    
                                    paralel.altura = PARALELOGRAMO_ALTURA_DEFAULT;
									errorParalel = true;
                                    }

                                }  else {

                                    EventLogger::AgregarEvento("ERROR: altura del paralelogramo DEBE ser un real positivo, se omitira el elemento");

                                    //TODO:Cargar valores por defecto..
                                    
                                    paralel.altura = PARALELOGRAMO_ALTURA_DEFAULT;
									errorParalel = true;
                                    

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: altura del paralelogramo NO existe en el archivo, se omitira el elemento");

                                //TODO:Cargar valores por defecto..
                               paralel.altura = PARALELOGRAMO_ALTURA_DEFAULT;
							   errorParalel = true;

                            }
                            /*************************************************************************************************/ 
                            /*************************************************************************************************/ 
                            //VALIDACIONES: paralel-color
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["color"].isNull()){

                                //SI ES UN STRING
                                if( root["escenario"]["objetos"][i]["color"].isString()){

                                    if( Funciones::esHEXvalido(root["escenario"]["objetos"][i]["color"].asString()) ){

                                        string colorHEX = root["escenario"]["objetos"][i]["color"].asString();

                                        //Si es un hex valido....
                                        paralel.color.r = Funciones::hexToRGB(colorHEX).r;
                                        paralel.color.g = Funciones::hexToRGB(colorHEX).g;
                                        paralel.color.b = Funciones::hexToRGB(colorHEX).b;


                                    }  else {

                                        EventLogger::AgregarEvento("ERROR: color del paralelogramo DEBE ser un HEX VALIDO, se cargaran los valores por defecto");

                                        //TODO:Cargar valores por defecto..
                                        paralel.color.r = R_DEFAULT;
                                        paralel.color.g = G_DEFAULT;
                                        paralel.color.b = B_DEFAULT;

                                    } }
                                else {

                                    EventLogger::AgregarEvento("ERROR: color del paralelogramo DEBE ser un string, se cargaran los valores por defecto");
                                    //TODO:Cargar valores por defecto..
                                    paralel.color.r = R_DEFAULT;
                                    paralel.color.g = G_DEFAULT;
                                    paralel.color.b = B_DEFAULT;
                                }



                            }  else {
                                EventLogger::AgregarEvento("ERROR: color del paralelogramo NO existe en el archivo, se cargaran los valores por defecto");

                                //TODO:Cargar valores por defecto..
                                paralel.color.r = R_DEFAULT;
                                paralel.color.g = G_DEFAULT;
                                paralel.color.b = B_DEFAULT;

                            }
                            /*************************************************************************************************/ 

                            /*************************************************************************************************/ 
                            //VALIDACIONES: paralel-rot
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["rot"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["rot"].isInt()){

                                    

									if (root["escenario"]["objetos"][i]["rot"].asInt() >=0 && root["escenario"]["objetos"][i]["rot"].asInt() <=359){

                                        paralel.rot = root["escenario"]["objetos"][i]["rot"].asInt();    

								} else {

                                        EventLogger::AgregarEvento("ERROR: rot del poligono DEBE ser entero entre 0 y 359, se omitira el elemento");

                                        //TODO:Cargar valores por defecto..
                                        paralel.rot = PARALELOGRAMO_ROT_DEFAULT; 
										errorParalel = true;


                                    }


                                }  else {

                                    EventLogger::AgregarEvento("ERROR: rot del paralelogramo DEBE ser un entero, se omitira el elemento");

                                    //TODO:Cargar valores por defecto..
                                    paralel.rot = PARALELOGRAMO_ROT_DEFAULT;
									errorParalel = true;

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: rot del paralelogramo NO existe en el archivo, se omitira el elemento");

                                //TODO:Cargar valores por defecto..
                                paralel.rot = PARALELOGRAMO_ROT_DEFAULT;
								errorParalel = true;


                            }
                            /*************************************************************************************************/ 


                            /*************************************************************************************************/ 
                            //VALIDACIONES: paralel-masa
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["masa"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["masa"].isDouble()){

                                    if(root["escenario"]["objetos"][i]["masa"].asFloat()>=0){

                                        paralel.masa = root["escenario"]["objetos"][i]["masa"].asFloat();  
                                    } else {
                                        EventLogger::AgregarEvento("ERROR: masa del paralelogramo DEBE ser un real positivo, se omitira el elemento");
										//TODO:Cargar valores por defecto..
                                    paralel.masa = PARALELOGRAMO_MASA_DEFAULT;
									errorParalel = true;
                                    }

                                }  else {

                                    EventLogger::AgregarEvento("ERROR: masa del paralelogramo DEBE ser un real positivo, se omitira el elemento");

                                    //TODO:Cargar valores por defecto..
                                    paralel.masa = PARALELOGRAMO_MASA_DEFAULT;
									errorParalel = true;

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: masa del paralelogramo NO existe en el archivo, se omitira el elemento");

                                //TODO:Cargar valores por defecto..
                                paralel.masa = PARALELOGRAMO_MASA_DEFAULT;
								errorParalel = true;


                            }
                            /*************************************************************************************************/

                            /*************************************************************************************************/ 
                            //VALIDACIONES: paralel-estatico
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["estatico"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["estatico"].isBool()){

                                    paralel.estatico = root["escenario"]["objetos"][i]["estatico"].asBool();  


                                }  else {

                                    EventLogger::AgregarEvento("ERROR: estatico del paralelogramo DEBE ser un booleano, se omitira el elemento");

                                    //TODO:Cargar valores por defecto..
                                    paralel.estatico = PARALELOGRAMO_ESTATICO_DEFAULT;
									errorParalel = true;

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: estatico del paralelogramo NO existe en el archivo, se omitira el elemento");

                                //TODO:Cargar valores por defecto..
                                paralel.estatico = PARALELOGRAMO_ESTATICO_DEFAULT;
								errorParalel = true;

                            }
                            /*************************************************************************************************/ 						
							if(!errorParalel){
                            miEscenario.paralelogramos.push_back(paralel);
							}
                        }
                        else if( tipo=="trap"){
                            
                            trap trap;
                            trap.tipo = tipo;
                            bool pxrEsDefault = false;
                            bool psrEsDefault = false;
							bool errorTrap = false;
							
                            /*************************************************************************************************/ 
                            //VALIDACIONES: trap-x
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["x"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["x"].isDouble()){

                                    if(root["escenario"]["objetos"][i]["x"].asFloat()>=0){

                                        if(!pxrEsDefault)
                                            trap.x = root["escenario"]["objetos"][i]["x"].asFloat();  
                                    } else {
                                        EventLogger::AgregarEvento("ERROR: x del trapecio DEBE ser un real positivo, se omitira el elemento");
										       //TODO:Cargar valores por defecto..
                                    trap.x = TRAPECIO_X_DEFAULT;
                                    trap.y = TRAPECIO_Y_DEFAULT;
                                    pxrEsDefault = true;
									errorTrap = true;
                                    }

                                }  else {

                                    EventLogger::AgregarEvento("ERROR: x del trapecio DEBE ser un real positivo, se omitira el elemento");

                                    //TODO:Cargar valores por defecto..
                                    trap.x = TRAPECIO_X_DEFAULT;
                                    trap.y = TRAPECIO_Y_DEFAULT;
                                    pxrEsDefault = true;
									errorTrap = true;

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: x del trapecio NO existe en el archivo, se omitira el elemento");

                                //TODO:Cargar valores por defecto..
                                trap.x = TRAPECIO_X_DEFAULT;
                                trap.y = TRAPECIO_Y_DEFAULT;
                                pxrEsDefault = true;
								errorTrap = true;

                            }
                            /*************************************************************************************************/ 

                            /*************************************************************************************************/ 
                            //VALIDACIONES: trap-y
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["y"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["y"].isDouble()){

                                    if(root["escenario"]["objetos"][i]["y"].asFloat()>=0){

                                        if(!pxrEsDefault)
                                            trap.y = root["escenario"]["objetos"][i]["y"].asFloat();  
                                    } else {
                                        EventLogger::AgregarEvento("ERROR: y del trapecio DEBE ser un real positivo, se omitira el elemento");
										       //TODO:Cargar valores por defecto..
                                    trap.x = TRAPECIO_X_DEFAULT;
                                    trap.y = TRAPECIO_Y_DEFAULT;
                                    pxrEsDefault = true;
									errorTrap = true;
                                    }


                                }  else {

                                    EventLogger::AgregarEvento("ERROR: y del trapecio DEBE ser un real positivo, se omitira el elemento");

                                    //TODO:Cargar valores por defecto..
                                    trap.x = TRAPECIO_X_DEFAULT;
                                    trap.y = TRAPECIO_Y_DEFAULT;
                                    pxrEsDefault = true;
									errorTrap = true;

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: y del trapecio NO existe en el archivo, se omitira el elemento");

                                //TODO:Cargar valores por defecto..
                                trap.x = TRAPECIO_X_DEFAULT;
                                trap.y = TRAPECIO_Y_DEFAULT;
                                pxrEsDefault = true;
								errorTrap = true;

                            }
                            /*************************************************************************************************/ 

                            /*************************************************************************************************/ 
                            //VALIDACIONES: trap-lado1
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["lado1"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["lado1"].isDouble()){

                                    if(root["escenario"]["objetos"][i]["lado1"].asFloat()>=0){

                                        if(!psrEsDefault)
                                            trap.lado1 = root["escenario"]["objetos"][i]["lado1"].asFloat();  
                                    } else {
                                        EventLogger::AgregarEvento("ERROR: long. lado izquierdo del trapecio DEBE ser un real positivo, se omitira el elemento");
										 //TODO:Cargar valores por defecto..
                                    trap.lado1 = TRAPECIO_LONGLADO1_DEFAULT;
                                    trap.lado2 = TRAPECIO_LONGLADO2_DEFAULT;
									trap.lado3 = TRAPECIO_LONGLADO3_DEFAULT;
                                    psrEsDefault = true;
									errorTrap = true;
                                    }

                                }  else {

                                    EventLogger::AgregarEvento("ERROR: long. lado izquierdo del trapecio DEBE ser un entero, se omitira el elemento");

                                    //TODO:Cargar valores por defecto..
                                    trap.lado1 = TRAPECIO_LONGLADO1_DEFAULT;
                                    trap.lado2 = TRAPECIO_LONGLADO2_DEFAULT;
									trap.lado3 = TRAPECIO_LONGLADO3_DEFAULT;
                                    psrEsDefault = true;
									errorTrap = true;

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: long. lado izquierdo del trapecio NO existe en el archivo, se omitira el elemento");

                                //TODO:Cargar valores por defecto..
                                 trap.lado1 = TRAPECIO_LONGLADO1_DEFAULT;
                                    trap.lado2 = TRAPECIO_LONGLADO2_DEFAULT;
									trap.lado3 = TRAPECIO_LONGLADO3_DEFAULT;
                                psrEsDefault = true;
								errorTrap = true;

                            }
                            /*************************************************************************************************/ 
                            /*************************************************************************************************/ 
                            //VALIDACIONES: trap-lado2
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["lado2"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["lado2"].isDouble()){

                                    if(root["escenario"]["objetos"][i]["lado2"].asFloat()>=0){

                                        if(!psrEsDefault)
                                            trap.lado2 = root["escenario"]["objetos"][i]["lado2"].asFloat();  
                                    } else {
                                        EventLogger::AgregarEvento("ERROR: long. techo del trapecio DEBE ser un real positivo, se omitira el elemento");
										 //TODO:Cargar valores por defecto..
                                    trap.lado1 = TRAPECIO_LONGLADO1_DEFAULT;
                                    trap.lado2 = TRAPECIO_LONGLADO2_DEFAULT;
									trap.lado3 = TRAPECIO_LONGLADO3_DEFAULT;
                                    psrEsDefault = true;
									errorTrap = true;
                                    }

                                }  else {

                                    EventLogger::AgregarEvento("ERROR: long. techo del trapecio DEBE ser un entero, se omitira el elemento");

                                    //TODO:Cargar valores por defecto..
                                    trap.lado1 = TRAPECIO_LONGLADO1_DEFAULT;
                                    trap.lado2 = TRAPECIO_LONGLADO2_DEFAULT;
									trap.lado3 = TRAPECIO_LONGLADO3_DEFAULT;
                                    psrEsDefault = true;
									errorTrap = true;

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: long. techo del trapecio NO existe en el archivo, se omitira el elemento");

                                //TODO:Cargar valores por defecto..
                                trap.lado1 = TRAPECIO_LONGLADO1_DEFAULT;
                                    trap.lado2 = TRAPECIO_LONGLADO2_DEFAULT;
									trap.lado3 = TRAPECIO_LONGLADO3_DEFAULT;
                                psrEsDefault = true;
								errorTrap = true;

                            }
                            /*************************************************************************************************/ 
							  /*************************************************************************************************/ 
                            //VALIDACIONES: trap-lado3
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["lado3"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["lado3"].isDouble()){

                                    if(root["escenario"]["objetos"][i]["lado3"].asFloat()>=0){

                                        if(!psrEsDefault)
                                            trap.lado3 = root["escenario"]["objetos"][i]["lado3"].asFloat();  
                                    } else {
                                        EventLogger::AgregarEvento("ERROR: long. lado derecho del trapecio DEBE ser un real positivo, se omitira el elemento");
										 //TODO:Cargar valores por defecto..
                                    trap.lado1 = TRAPECIO_LONGLADO1_DEFAULT;
                                    trap.lado2 = TRAPECIO_LONGLADO2_DEFAULT;
									trap.lado3 = TRAPECIO_LONGLADO3_DEFAULT;
                                    psrEsDefault = true;
									errorTrap = true;
                                    }

                                }  else {

                                    EventLogger::AgregarEvento("ERROR: long. lado derecho del trapecio DEBE ser un entero, se omitira el elemento");

                                    //TODO:Cargar valores por defecto..
                                    trap.lado1 = TRAPECIO_LONGLADO1_DEFAULT;
                                    trap.lado2 = TRAPECIO_LONGLADO2_DEFAULT;
									trap.lado3 = TRAPECIO_LONGLADO3_DEFAULT;
                                    psrEsDefault = true;
									errorTrap = true;

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: long. lado derecho del trapecio NO existe en el archivo, se omitira el elemento");

                                //TODO:Cargar valores por defecto..
                                trap.lado1 = TRAPECIO_LONGLADO1_DEFAULT;
                                    trap.lado2 = TRAPECIO_LONGLADO2_DEFAULT;
									trap.lado3 = TRAPECIO_LONGLADO3_DEFAULT;
                                psrEsDefault = true;
								errorTrap = true;

                            }
                            /*************************************************************************************************/ 
                /*************************************************************************************************/ 
                            //VALIDACIONES: trap-altura
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["altura"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["altura"].isDouble()){

                                    if(root["escenario"]["objetos"][i]["altura"].asFloat()>=0){

                                        if(!psrEsDefault)
                                            trap.altura = root["escenario"]["objetos"][i]["altura"].asFloat();  
                                    } else {
                                        EventLogger::AgregarEvento("ERROR: altura del trapecio DEBE ser un real positivo, se omitira el elemento");
										//TODO:Cargar valores por defecto..
                                    
                                    trap.altura = TRAPECIO_ALTURA_DEFAULT;
									errorTrap = true;
                                    }

                                }  else {

                                    EventLogger::AgregarEvento("ERROR: altura del trapecio DEBE ser un real positivo, se omitira el elemento");

                                    //TODO:Cargar valores por defecto..
                                    
                                    trap.altura = TRAPECIO_ALTURA_DEFAULT;
									errorTrap = true;
                                    

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: altura del trapecio NO existe en el archivo, se omitira el elemento");

                                //TODO:Cargar valores por defecto..
                               trap.altura = TRAPECIO_ALTURA_DEFAULT;
							   errorTrap = true;

                            }
                            /*************************************************************************************************/ 
                            /*************************************************************************************************/ 
                            //VALIDACIONES: trap-color
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["color"].isNull()){

                                //SI ES UN STRING
                                if( root["escenario"]["objetos"][i]["color"].isString()){

                                    if( Funciones::esHEXvalido(root["escenario"]["objetos"][i]["color"].asString()) ){

                                        string colorHEX = root["escenario"]["objetos"][i]["color"].asString();

                                        //Si es un hex valido....
                                        trap.color.r = Funciones::hexToRGB(colorHEX).r;
                                        trap.color.g = Funciones::hexToRGB(colorHEX).g;
                                        trap.color.b = Funciones::hexToRGB(colorHEX).b;


                                    }  else {

                                        EventLogger::AgregarEvento("ERROR: color del trapecio DEBE ser un HEX VALIDO, se cargaran los valores por defecto");

                                        //TODO:Cargar valores por defecto..
                                        trap.color.r = R_DEFAULT;
                                        trap.color.g = G_DEFAULT;
                                        trap.color.b = B_DEFAULT;

                                    } }
                                else {

                                    EventLogger::AgregarEvento("ERROR: color del trapecio DEBE ser un string, se cargaran los valores por defecto");
                                    //TODO:Cargar valores por defecto..
                                    trap.color.r = R_DEFAULT;
                                    trap.color.g = G_DEFAULT;
                                    trap.color.b = B_DEFAULT;
                                }



                            }  else {
                                EventLogger::AgregarEvento("ERROR: color del trapecio NO existe en el archivo, se cargaran los valores por defecto");

                                //TODO:Cargar valores por defecto..
                                trap.color.r = R_DEFAULT;
                                trap.color.g = G_DEFAULT;
                                trap.color.b = B_DEFAULT;

                            }
                            /*************************************************************************************************/ 

                            /*************************************************************************************************/ 
                            //VALIDACIONES: trap-rot
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["rot"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["rot"].isInt()){

                                    

									if (root["escenario"]["objetos"][i]["rot"].asInt() >=0 && root["escenario"]["objetos"][i]["rot"].asInt() <=359){

                                        trap.rot = root["escenario"]["objetos"][i]["rot"].asInt();    

								} else {

                                        EventLogger::AgregarEvento("ERROR: rot del poligono DEBE ser entero entre 0 y 359, se omitira el elemento");

                                        //TODO:Cargar valores por defecto..
                                        trap.rot = TRAPECIO_ROT_DEFAULT;  
										errorTrap = true;


                                    }


                                }  else {

                                    EventLogger::AgregarEvento("ERROR: rot del trapecio DEBE ser un entero, se omitira el elemento");

                                    //TODO:Cargar valores por defecto..
                                    trap.rot = TRAPECIO_ROT_DEFAULT;
									errorTrap = true;

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: rot del trapecio NO existe en el archivo, se omitira el elemento");

                                //TODO:Cargar valores por defecto..
                                trap.rot = TRAPECIO_ROT_DEFAULT;
								errorTrap = true;


                            }
                            /*************************************************************************************************/ 


                            /*************************************************************************************************/ 
                            //VALIDACIONES: trap-masa
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["masa"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["masa"].isDouble()){

                                    if(root["escenario"]["objetos"][i]["masa"].asFloat()>=0){

                                        trap.masa = root["escenario"]["objetos"][i]["masa"].asFloat();  
                                    } else {
                                        EventLogger::AgregarEvento("ERROR: masa del trapecio DEBE ser un real positivo, se omitira el elemento");
										//TODO:Cargar valores por defecto..
                                    trap.masa = TRAPECIO_MASA_DEFAULT;
									errorTrap = true;
                                    }

                                }  else {

                                    EventLogger::AgregarEvento("ERROR: masa del trapecio DEBE ser un real positivo, se omitira el elemento");

                                    //TODO:Cargar valores por defecto..
                                    trap.masa = TRAPECIO_MASA_DEFAULT;
									errorTrap = true;

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: masa del trapecio NO existe en el archivo, se omitira el elemento");

                                //TODO:Cargar valores por defecto..
                                trap.masa = TRAPECIO_MASA_DEFAULT;
								errorTrap = true;


                            }
                            /*************************************************************************************************/

                            /*************************************************************************************************/ 
                            //VALIDACIONES: trap-estatico
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["estatico"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["estatico"].isBool()){

                                    trap.estatico = root["escenario"]["objetos"][i]["estatico"].asBool();  


                                }  else {

                                    EventLogger::AgregarEvento("ERROR: estatico del trapecio DEBE ser un booleano, se omitira el elemento");

                                    //TODO:Cargar valores por defecto..
                                    trap.estatico = TRAPECIO_ESTATICO_DEFAULT;
									errorTrap = true;

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: estatico del trapecio NO existe en el archivo, se omitira el elemento");

                                //TODO:Cargar valores por defecto..
                                trap.estatico = TRAPECIO_ESTATICO_DEFAULT;
								errorTrap = true;


                            }
                            /*************************************************************************************************/ 						
							if(!errorTrap){
                            miEscenario.trapecios.push_back(trap);
							}
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
	// CREARESCENARIO

/*	    cout << "altopx " << miEscenario.altopx << endl;
        cout <<"anchopx " << miEscenario.anchopx << endl;
        cout << "altoun " << miEscenario.altoun << endl;
        cout << "anchoun " << miEscenario.anchoun << endl;
        cout << "imagen_fondo " << miEscenario.imagen_fondo << endl;
        cout << "personajeX " << miEscenario.personajeX << endl;
        cout << "personajeY " << miEscenario.personajeY << endl;
*/	 
	Escenario * esc = new Escenario(miEscenario.anchoun,miEscenario.altoun,CoordenadasR2(0,miEscenario.gravedad),miEscenario.imagen_fondo,NULL);
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

		cout<<"Tipo: " << objetoActualPoli.tipo  << endl;
		cout<<"Lados: " <<objetoActualPoli.lados  << endl;
		cout<<"Escala: " <<objetoActualPoli.escala  << endl;
		cout<<"Color R: " << objetoActualPoli.color.r << endl;
		cout<<"Color G: " << objetoActualPoli.color.g << endl;
		cout<<"Color B: " << objetoActualPoli.color.b << endl;
		cout<<"Estatico: " <<objetoActualPoli.estatico << endl;
		cout<<"Masa: " <<objetoActualPoli.masa << endl;
		cout<<"Rot: " <<objetoActualPoli.rot << endl;
		cout<<"X: " <<objetoActualPoli.x << endl;
		cout<<"Y: " <<objetoActualPoli.y << endl;

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
		objetoActualRect.alto;
		objetoActualRect.ancho;
		objetoActualRect.color;
		objetoActualRect.estatico;
		objetoActualRect.masa;
		objetoActualRect.rot;
		objetoActualRect.tipo;
		objetoActualRect.x;
		objetoActualRect.y;

		cout<<"Tipo: " << objetoActualRect.tipo  << endl;
		cout<<"Alto: " <<objetoActualRect.alto  << endl;
		cout<<"Ancho: " <<objetoActualRect.ancho  << endl;
		cout<<"Color R: " << objetoActualRect.color.r << endl;
		cout<<"Color G: " << objetoActualRect.color.g << endl;
		cout<<"Color B: " << objetoActualRect.color.b << endl;
		cout<<"Estatico: " <<objetoActualRect.estatico << endl;
		cout<<"Masa: " <<objetoActualRect.masa << endl;
		cout<<"Rot: " <<objetoActualRect.rot << endl;
		cout<<"X: " <<objetoActualRect.x << endl;
		cout<<"Y: " <<objetoActualRect.y << endl;

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

		esc->agregarParalelogramo(CoordenadasR2(unParalelogramo.x,unParalelogramo.y),unParalelogramo.lado1,unParalelogramo.lado2,unParalelogramo.altura,Color(unParalelogramo.color.r, unParalelogramo.color.g, unParalelogramo.color.b),unParalelogramo.rot,!unParalelogramo.estatico,unParalelogramo.masa);


	}

	

	list <trap> objetosTrap;	
	objetosTrap = miEscenario.trapecios;
	for (list <trap> ::iterator it= miEscenario.trapecios.begin(); it!= miEscenario.trapecios.end(); it++) {
		trap unTrapecio= *it;

		esc->agregarTrapecio(CoordenadasR2(unTrapecio.x,unTrapecio.y),unTrapecio.lado1,unTrapecio.lado2,unTrapecio.lado3,unTrapecio.altura,Color(unTrapecio.color.r, unTrapecio.color.g, unTrapecio.color.b),unTrapecio.rot,!unTrapecio.estatico,unTrapecio.masa);


	}









	return esc;

}


Parser::~Parser(void)
{
}
