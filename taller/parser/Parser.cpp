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


void Parser::Inicializar()
{
	bool pxSonDefault = false;
	bool unSonDefault = false;
	bool personajeSonDefault = false;
	

    Json::Reader reader;  
    Json::Value root;    

    //Ubicacion Archivo

    const char* filename= "parser/test.json";;
    std::ifstream archivoJson;  
    archivoJson.open (filename, std::ios::binary );    

    // Devuelvo si hubo error en el parseado a nivel de la libreria!
    bool parseadoOK = reader.parse(archivoJson, root, false);



    if(!parseadoOK){
        EventLogger::AgregarEvento(reader.getFormatedErrorMessages());

        //TODO:CARGAR JSON POR DEFECTO   

    }

    if (parseadoOK)  
    { 
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
        //VALIDACIONES: alto-px 
        //SI EXISTE
        if(!root["escenario"]["alto-px"].isNull()){

            //SI ES UN ENTERO
            if(root["escenario"]["alto-px"].isInt()){
				
				if(!pxSonDefault)
                miEscenario.altopx = root["escenario"]["alto-px"].asInt();  


            }  else {

                EventLogger::AgregarEvento("ERROR: alto-px DEBE ser un entero, se cargaran los valores por defecto");

                //TODO:Cargar valores por defecto... Alto y ancho?
                miEscenario.altopx = ALTO_PX_DEFAULT;
                miEscenario.anchopx = ANCHO_PX_DEFAULT;
				pxSonDefault = true;

            }

        } else {
            EventLogger::AgregarEvento("ERROR: alto-px NO existe en el archivo, se cargaran los valores por defecto");

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

				if(!pxSonDefault)
                miEscenario.anchopx = root["escenario"]["ancho-px"].asInt();  


            }  else {

                EventLogger::AgregarEvento("ERROR: ancho-px DEBE ser un entero, se cargaran los valores por defecto");

                //TODO:Cargar valores por defecto... Alto y ancho?
                miEscenario.altopx = ALTO_PX_DEFAULT;
                miEscenario.anchopx = ANCHO_PX_DEFAULT;
				pxSonDefault = true;

            }

        } else {
            EventLogger::AgregarEvento("ERROR: ancho-px NO existe en el archivo, se cargaran los valores por defecto");

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
            if(root["escenario"]["alto-un"].isInt()){
				
				if(!unSonDefault)
                miEscenario.altoun = root["escenario"]["alto-un"].asInt();  


            }  else {

                EventLogger::AgregarEvento("ERROR: alto-un DEBE ser un entero, se cargaran los valores por defecto");

                //TODO:Cargar valores por defecto... Alto y ancho?
                miEscenario.altoun = ALTO_UN_DEFAULT;
                miEscenario.anchoun = ANCHO_UN_DEFAULT;
				unSonDefault = true;
            }

        } else {
            EventLogger::AgregarEvento("ERROR: alto-un NO existe en el archivo, se cargaran los valores por defecto");

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
            if(root["escenario"]["ancho-un"].isInt()){
				
				if(!unSonDefault)
                miEscenario.anchoun = root["escenario"]["ancho-un"].asInt();  


            }  else {

                EventLogger::AgregarEvento("ERROR: ancho-un DEBE ser un entero, se cargaran los valores por defecto");

                //TODO:Cargar valores por defecto... Alto y ancho?
                miEscenario.altoun = ALTO_UN_DEFAULT;
                miEscenario.anchoun = ANCHO_UN_DEFAULT;
				unSonDefault = true;

            }

        } else {
            EventLogger::AgregarEvento("ERROR: ancho-un NO existe en el archivo, se cargaran los valores por defecto");

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
                    EventLogger::AgregarEvento("ERROR: imagen_fondo NO existe o tiene una extension invalida");
                    //Cargar imagen fondo por defecto
                    miEscenario.imagen_fondo = IMAGEN_DEFAULT;
                }


            }  else {
                EventLogger::AgregarEvento("ERROR: imagen_fondo DEBE ser un string");
                //Cargar imagen fondo por defecto
                miEscenario.imagen_fondo = IMAGEN_DEFAULT;
            }

        }
        else {
            EventLogger::AgregarEvento("ERROR: imagen_fondo no existe");
            //Cargar imagen fondo por defecto
            miEscenario.imagen_fondo = IMAGEN_DEFAULT;
        }

        /*************************************************************************************************/ 

        /*************************************************************************************************/ 
        //VALIDACIONES: personajeX
        //SI EXISTE
        if(!root["escenario"]["personaje"]["x"].isNull()){

            //SI ES UN ENTERO
            if(root["escenario"]["personaje"]["x"].isInt()){
				if(!personajeSonDefault)
                miEscenario.personajeX = root["escenario"]["personaje"]["x"].asInt();  


            }  else {

                EventLogger::AgregarEvento("ERROR: personaje x DEBE ser un entero, se cargaran los valores por defecto");

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
            if(root["escenario"]["personaje"]["y"].isInt()){

				if(!personajeSonDefault)
                miEscenario.personajeY = root["escenario"]["personaje"]["y"].asInt();  


            }  else {

                EventLogger::AgregarEvento("ERROR: personaje y DEBE ser un entero, se cargaran los valores por defecto");

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

                            /*************************************************************************************************/ 
                            //VALIDACIONES: poli-x
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["x"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["x"].isInt()){

									if(!pxpEsDefault)
                                    poli.x = root["escenario"]["objetos"][i]["x"].asInt();  


                                }  else {

                                    EventLogger::AgregarEvento("ERROR: x del poligono DEBE ser un entero, se cargaran los valores por defecto");

                                    //TODO:Cargar valores por defecto..
                                    poli.x = POLIGONO_X_DEFAULT;
                                    poli.y = POLIGONO_Y_DEFAULT;
									pxpEsDefault = true;

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: x del poligono NO existe en el archivo, se cargaran los valores por defecto");

                                //TODO:Cargar valores por defecto..
                                poli.x = POLIGONO_X_DEFAULT;
                                poli.y = POLIGONO_Y_DEFAULT;
								pxpEsDefault = true;
                            }
                            /*************************************************************************************************/ 

                            /*************************************************************************************************/ 
                            //VALIDACIONES: poli-y
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["y"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["y"].isInt()){
									if(!pxpEsDefault)
                                    poli.y = root["escenario"]["objetos"][i]["y"].asInt();  


                                }  else {

                                    EventLogger::AgregarEvento("ERROR: y del poligono DEBE ser un entero, se cargaran los valores por defecto");

                                    //TODO:Cargar valores por defecto..
                                    poli.x = POLIGONO_X_DEFAULT;
                                    poli.y = POLIGONO_Y_DEFAULT;
									pxpEsDefault = true;

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: y del poligono NO existe en el archivo, se cargaran los valores por defecto");

                                //TODO:Cargar valores por defecto..
                                poli.x = POLIGONO_X_DEFAULT;
                                poli.y = POLIGONO_Y_DEFAULT;
								pxpEsDefault = true;

                            }
                            /*************************************************************************************************/ 

                            /*************************************************************************************************/ 
                            //VALIDACIONES: poli-escala
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["escala"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["escala"].isDouble()){

                                    poli.escala = root["escenario"]["objetos"][i]["escala"].asFloat();  


                                }  else {

                                    EventLogger::AgregarEvento("ERROR: escala del poligono DEBE ser un float, se cargaran los valores por defecto");

                                    //TODO:Cargar valores por defecto..
                                    poli.escala = POLIGONO_ESCALA_DEFAULT;


                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: escala del poligono NO existe en el archivo, se cargaran los valores por defecto");

                                //TODO:Cargar valores por defecto..
                                poli.escala = POLIGONO_ESCALA_DEFAULT;

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

                                    EventLogger::AgregarEvento("ERROR: lados del poligono DEBE ser entero entre 3 y 6, se cargaran los valores por defecto");

                                    //TODO:Cargar valores por defecto..
                                    poli.lados = POLIGONO_LADOS_DEFAULT;


                                }


                                }  else {

                                    EventLogger::AgregarEvento("ERROR: lados del poligono DEBE ser un entero, se cargaran los valores por defecto");

                                    //TODO:Cargar valores por defecto..
                                    poli.lados = POLIGONO_LADOS_DEFAULT;


                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: alto del poligono NO existe en el archivo, se cargaran los valores por defecto");

                                //TODO:Cargar valores por defecto..
                                poli.lados = POLIGONO_LADOS_DEFAULT;

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

                                    poli.rot = root["escenario"]["objetos"][i]["rot"].asInt();  


                                }  else {

                                    EventLogger::AgregarEvento("ERROR: rot del poligono DEBE ser un entero, se cargaran los valores por defecto");

                                    //TODO:Cargar valores por defecto..
                                    poli.rot = POLIGONO_ROT_DEFAULT;

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: rot del poligono NO existe en el archivo, se cargaran los valores por defecto");

                                //TODO:Cargar valores por defecto..
                                poli.rot = POLIGONO_ROT_DEFAULT;


                            }
                            /*************************************************************************************************/ 


                            /*************************************************************************************************/ 
                            //VALIDACIONES: poli-masa
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["masa"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["masa"].isInt()){

                                    poli.masa = root["escenario"]["objetos"][i]["masa"].asInt();  


                                }  else {

                                    EventLogger::AgregarEvento("ERROR: masa del poligono DEBE ser un entero, se cargaran los valores por defecto");

                                    //TODO:Cargar valores por defecto..
                                    poli.masa = POLIGONO_MASA_DEFAULT;

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: masa del poligono NO existe en el archivo, se cargaran los valores por defecto");

                                //TODO:Cargar valores por defecto..
                                poli.masa = POLIGONO_MASA_DEFAULT;


                            }
                            /*************************************************************************************************/

                            /*************************************************************************************************/ 
                            //VALIDACIONES: poli-estatico
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["estatico"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["estatico"].isBool()){

                                    poli.estatico = root["escenario"]["objetos"][i]["estatico"].asBool();  


                                }  else {

                                    EventLogger::AgregarEvento("ERROR: estatico del poligono DEBE ser un entero, se cargaran los valores por defecto");

                                    //TODO:Cargar valores por defecto..
                                    poli.estatico = POLIGONO_ESTATICO_DEFAULT;

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: estatico del poligono NO existe en el archivo, se cargaran los valores por defecto");

                                //TODO:Cargar valores por defecto..
                                poli.estatico = POLIGONO_ESTATICO_DEFAULT;


                            }
                            /*************************************************************************************************/ 						

                            miEscenario.poligonos.push_back(poli);

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
							
                            /*************************************************************************************************/ 
                            //VALIDACIONES: rect-x
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["x"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["x"].isInt()){

									if(!pxrEsDefault)
                                    rect.x = root["escenario"]["objetos"][i]["x"].asInt();  


                                }  else {

                                    EventLogger::AgregarEvento("ERROR: x del rectangulo DEBE ser un entero, se cargaran los valores por defecto");

                                    //TODO:Cargar valores por defecto..
                                    rect.x = RECTANGULO_X_DEFAULT;
                                    rect.y = RECTANGULO_Y_DEFAULT;
									pxrEsDefault = true;

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: x del rectangulo NO existe en el archivo, se cargaran los valores por defecto");

                                //TODO:Cargar valores por defecto..
                                rect.x = RECTANGULO_X_DEFAULT;
                                rect.y = RECTANGULO_Y_DEFAULT;
								pxrEsDefault = true;

                            }
                            /*************************************************************************************************/ 

                            /*************************************************************************************************/ 
                            //VALIDACIONES: rect-y
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["y"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["y"].isInt()){

									if(!pxrEsDefault)
                                    rect.y = root["escenario"]["objetos"][i]["y"].asInt();  


                                }  else {

                                    EventLogger::AgregarEvento("ERROR: y del rectangulo DEBE ser un entero, se cargaran los valores por defecto");

                                    //TODO:Cargar valores por defecto..
                                    rect.x = RECTANGULO_X_DEFAULT;
                                    rect.y = RECTANGULO_Y_DEFAULT;
									pxrEsDefault = true;

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: y del rectangulo NO existe en el archivo, se cargaran los valores por defecto");

                                //TODO:Cargar valores por defecto..
                                rect.x = RECTANGULO_X_DEFAULT;
                                rect.y = RECTANGULO_Y_DEFAULT;
								pxrEsDefault = true;

                            }
                            /*************************************************************************************************/ 

                            /*************************************************************************************************/ 
                            //VALIDACIONES: rect-ancho
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["ancho"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["ancho"].isInt()){

									if(!psrEsDefault)
                                    rect.ancho = root["escenario"]["objetos"][i]["ancho"].asInt();  


                                }  else {

                                    EventLogger::AgregarEvento("ERROR: ancho del rectangulo DEBE ser un entero, se cargaran los valores por defecto");

                                    //TODO:Cargar valores por defecto..
                                    rect.ancho = RECTANGULO_ANCHO_DEFAULT;
                                    rect.alto = RECTANGULO_ALTO_DEFAULT;
									psrEsDefault = true;

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: ancho del rectangulo NO existe en el archivo, se cargaran los valores por defecto");

                                //TODO:Cargar valores por defecto..
                                rect.ancho = RECTANGULO_ANCHO_DEFAULT;
                                rect.alto = RECTANGULO_ALTO_DEFAULT;
								psrEsDefault = true;

                            }
                            /*************************************************************************************************/ 
                            /*************************************************************************************************/ 
                            //VALIDACIONES: rect-alto
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["alto"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["alto"].isInt()){

									if(!psrEsDefault)
                                    rect.alto = root["escenario"]["objetos"][i]["alto"].asInt();  


                                }  else {

                                    EventLogger::AgregarEvento("ERROR: alto del rectangulo DEBE ser un entero, se cargaran los valores por defecto");

                                    //TODO:Cargar valores por defecto..
                                    rect.ancho = RECTANGULO_ANCHO_DEFAULT;
                                    rect.alto = RECTANGULO_ALTO_DEFAULT;
									psrEsDefault = true;

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: alto del rectangulo NO existe en el archivo, se cargaran los valores por defecto");

                                //TODO:Cargar valores por defecto..
                                rect.ancho = RECTANGULO_ANCHO_DEFAULT;
                                rect.alto = RECTANGULO_ALTO_DEFAULT;
								psrEsDefault = true;

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

                                    rect.rot = root["escenario"]["objetos"][i]["rot"].asInt();  


                                }  else {

                                    EventLogger::AgregarEvento("ERROR: rot del rectangulo DEBE ser un entero, se cargaran los valores por defecto");

                                    //TODO:Cargar valores por defecto..
                                    rect.rot = RECTANGULO_ROT_DEFAULT;

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: rot del rectangulo NO existe en el archivo, se cargaran los valores por defecto");

                                //TODO:Cargar valores por defecto..
                                rect.rot = RECTANGULO_ROT_DEFAULT;


                            }
                            /*************************************************************************************************/ 


                            /*************************************************************************************************/ 
                            //VALIDACIONES: rect-masa
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["masa"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["masa"].isInt()){

                                    rect.masa = root["escenario"]["objetos"][i]["masa"].asInt();  


                                }  else {

                                    EventLogger::AgregarEvento("ERROR: masa del rectangulo DEBE ser un entero, se cargaran los valores por defecto");

                                    //TODO:Cargar valores por defecto..
                                    rect.masa = RECTANGULO_MASA_DEFAULT;

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: masa del rectangulo NO existe en el archivo, se cargaran los valores por defecto");

                                //TODO:Cargar valores por defecto..
                                rect.masa = RECTANGULO_MASA_DEFAULT;


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

                                    EventLogger::AgregarEvento("ERROR: estatico del rectangulo DEBE ser un entero, se cargaran los valores por defecto");

                                    //TODO:Cargar valores por defecto..
                                    rect.estatico = RECTANGULO_ESTATICO_DEFAULT;

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: estatico del rectangulo NO existe en el archivo, se cargaran los valores por defecto");

                                //TODO:Cargar valores por defecto..
                                rect.estatico = RECTANGULO_ESTATICO_DEFAULT;


                            }
                            /*************************************************************************************************/ 						

                            miEscenario.rectangulos.push_back(rect);




                        }
                        else if( tipo=="circ"){
                           	circ circulo;
							circulo.tipo = tipo;
							bool cxEsDefault = false;

                            /*************************************************************************************************/ 
                            //VALIDACIONES: circulo-x
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["x"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["x"].isInt()){

									if(!cxEsDefault)
                                    circulo.x = root["escenario"]["objetos"][i]["x"].asInt();  


                                }  else {

                                    EventLogger::AgregarEvento("ERROR: x del circulo DEBE ser un entero, se cargaran los valores por defecto");

                                    //TODO:Cargar valores por defecto..
                                    circulo.x = CIRCULO_X_DEFAULT;
                                    circulo.y = CIRCULO_Y_DEFAULT;
									cxEsDefault = true;

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: x del circulo NO existe en el archivo, se cargaran los valores por defecto");

                                //TODO:Cargar valores por defecto..
                                circulo.x = CIRCULO_X_DEFAULT;
                                circulo.y = CIRCULO_Y_DEFAULT;
								cxEsDefault = true;
                            }
                            /*************************************************************************************************/ 

                            /*************************************************************************************************/ 
                            //VALIDACIONES: circulo-y
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["y"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["y"].isInt()){
									if(!cxEsDefault)
                                    circulo.y = root["escenario"]["objetos"][i]["y"].asInt();  


                                }  else {

                                    EventLogger::AgregarEvento("ERROR: y del circulo DEBE ser un entero, se cargaran los valores por defecto");

                                    //TODO:Cargar valores por defecto..
                                    circulo.x = CIRCULO_X_DEFAULT;
                                    circulo.y = CIRCULO_Y_DEFAULT;
									cxEsDefault = true;

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: y del circulo NO existe en el archivo, se cargaran los valores por defecto");

                                //TODO:Cargar valores por defecto..
                                circulo.x = CIRCULO_X_DEFAULT;
                                circulo.y = CIRCULO_Y_DEFAULT;
								cxEsDefault = true;

                            }
                            /*************************************************************************************************/ 

                            
                            /*************************************************************************************************/ 
                            //VALIDACIONES: circulo-radio
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["radio"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["radio"].isInt()){

									if (root["escenario"]["objetos"][i]["radio"].asInt() >=3 && root["escenario"]["objetos"][i]["radio"].asInt() <=6){
										
										circulo.radio = root["escenario"]["objetos"][i]["radio"].asInt(); }

									else {

                                    EventLogger::AgregarEvento("ERROR: radio del circulo DEBE ser entero entre 3 y 6, se cargaran los valores por defecto");

                                    //TODO:Cargar valores por defecto..
                                    circulo.radio = CIRCULO_RADIO_DEFAULT;


                                }


                                }  else {

                                    EventLogger::AgregarEvento("ERROR: radio del circulo DEBE ser un entero, se cargaran los valores por defecto");

                                    //TODO:Cargar valores por defecto..
                                    circulo.radio = CIRCULO_RADIO_DEFAULT;


                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: alto del circulo NO existe en el archivo, se cargaran los valores por defecto");

                                //TODO:Cargar valores por defecto..
                                circulo.radio = CIRCULO_RADIO_DEFAULT;

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
                                if(root["escenario"]["objetos"][i]["masa"].isInt()){

                                    circulo.masa = root["escenario"]["objetos"][i]["masa"].asInt();  


                                }  else {

                                    EventLogger::AgregarEvento("ERROR: masa del circulo DEBE ser un entero, se cargaran los valores por defecto");

                                    //TODO:Cargar valores por defecto..
                                    circulo.masa = CIRCULO_MASA_DEFAULT;

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: masa del circulo NO existe en el archivo, se cargaran los valores por defecto");

                                //TODO:Cargar valores por defecto..
                                circulo.masa = CIRCULO_MASA_DEFAULT;


                            }
                            /*************************************************************************************************/

                            /*************************************************************************************************/ 
                            //VALIDACIONES: circulo-estatico
                            //SI EXISTE
                            if(!root["escenario"]["objetos"][i]["estatico"].isNull()){

                                //SI ES UN ENTERO
                                if(root["escenario"]["objetos"][i]["estatico"].isBool()){

                                    circulo.estatico = root["escenario"]["objetos"][i]["estatico"].asBool();  


                                }  else {

                                    EventLogger::AgregarEvento("ERROR: estatico del circulo DEBE ser un entero, se cargaran los valores por defecto");

                                    //TODO:Cargar valores por defecto..
                                    circulo.estatico = CIRCULO_ESTATICO_DEFAULT;

                                }

                            } else {
                                EventLogger::AgregarEvento("ERROR: estatico del circulo NO existe en el archivo, se cargaran los valores por defecto");

                                //TODO:Cargar valores por defecto..
                                circulo.estatico = CIRCULO_ESTATICO_DEFAULT;


                            }
                            /*************************************************************************************************/ 						

                            miEscenario.circulos.push_back(circulo);
                        }
                        else if( tipo=="paralel"){
                            EventLogger::AgregarEvento("ERROR: paralel aun no implementado");
                        }
                        else if( tipo=="trap"){
                            EventLogger::AgregarEvento("ERROR: trap aun no implementado");
                        }else{
                            EventLogger::AgregarEvento("ERROR: se quiso cargar un objeto invalido");
                        }


                    }  
                }
            }

        }
    } 
    archivoJson.close();  


    







}

Escenario * Parser::CrearObjetos()
{
	// CREARESCENARIO

	    cout << "altopx " << miEscenario.altopx << endl;
        cout <<"anchopx " << miEscenario.anchopx << endl;
        cout << "altoun " << miEscenario.altoun << endl;
        cout << "anchoun " << miEscenario.anchoun << endl;
        cout << "imagen_fondo " << miEscenario.imagen_fondo << endl;
        cout << "personajeX " << miEscenario.personajeX << endl;
        cout << "personajeY " << miEscenario.personajeY << endl;
	 
		Escenario * esc = new Escenario(miEscenario.anchoun,miEscenario.altoun,NULL);
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
							objetoActualPoli.estatico,
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

	}
	return esc;
}


Parser::~Parser(void)
{
}
