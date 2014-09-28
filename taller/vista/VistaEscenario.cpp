#include "VistaEscenario.h"


VistaEscenario::VistaEscenario(Escenario* escenario , DatosPantalla* datos)
{
	m_ancho = datos->getAnchoPixel();
	m_alto = datos->getAltoPixel();
	m_fondo =NULL;
	if( iniciarVentana() == false){
		std::string msg ="No se pudo iniciar correctamente VistaEscenario.";
		log(msg, LOG_ERROR);
	}
	else
	{
		m_escenario = escenario;
		m_datos_pantalla = datos;
		std::string msg ="Vista Escenario. Resolucion de ventana = "+ EventLogger::itos(datos->getAnchoPixel()) + " x " + EventLogger::itos(datos->getAltoPixel());
		log(msg, DEBUG);
		this->agregarFondo(m_escenario->getPathFondo());
		this->cargarFiguras();
		log("VistaEscenario creado correctamente.", DEBUG);
	}
}

bool VistaEscenario::iniciarVentana() { 

	bool success = true; 

	m_window = SDL_CreateWindow( "TP taller", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_ancho, m_alto, SDL_WINDOW_SHOWN );
	if( m_window == NULL ) 
	{ 
		std::string msg ="No se pudo crear ventana - SDL Error: ";
		msg.append(SDL_GetError());
		log(msg, LOG_ERROR);
		success = false; 
	} else { 
		m_renderer = SDL_CreateRenderer( m_window , -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); 
		if( m_renderer == NULL )
		{
			std::string msg ="No se pudo crear Renderer - SDL Error: ";
			msg.append(SDL_GetError());
			log(msg, LOG_ERROR); 
			success = false; 
		}
		else { 

			//Inicializo SDL_IMAGE 
			int imgFlags = IMG_INIT_JPG|IMG_INIT_PNG; 
			if( !( IMG_Init( imgFlags ) & imgFlags ) ) 
			{ 
				std::string msg ="No se pudo iniciar SDL_image - SDL_image Error: ";
				msg.append(IMG_GetError());
				log(msg, LOG_ERROR);
				success = false; 
			} 
		}
	} 

	return success; 
}


void VistaEscenario::agregarFondo(std::string path){
	
	if(m_fondo != NULL){
		SDL_DestroyTexture( m_fondo );
	}
	
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		std::string msg =	"No se pudo cargar la imagen de fondo: " + path + " IMG_image Error: " + IMG_GetError() ;
		log(msg, LOG_ERROR);	
	}
	else
	{
		
        m_fondo = SDL_CreateTextureFromSurface( m_renderer, loadedSurface );
		if( m_fondo == NULL )
		{
			std::string msg =	"No se pudo crear la textura desde " + path + " SDL Error: " + SDL_GetError() ;
			log(msg, LOG_ERROR);
		}else{
			std::string msg ="Se cargo correctamente textura con fondo: " + path ;
			log(msg, LOG_ERROR);
		}

	
		SDL_FreeSurface( loadedSurface );
	}


}

void VistaEscenario::resize(int ancho,int alto){

			
			float ancho_2= (float)ancho;
			float ancho_1= (float)m_ancho;
			float alto_2= (float)alto;
			float alto_1= (float)m_alto;

			float resizeX = ancho_2/ancho_1;
			float resizeY = alto_2/alto_1;

			SDL_RenderSetScale(m_renderer,resizeX,resizeY);
			
			SDL_SetWindowSize(m_window,ancho,alto);
}

void VistaEscenario::mostrar(){
	//Clear screen		
	SDL_SetRenderDrawColor( m_renderer, 255, 255, 255, 255 );
	SDL_RenderClear( m_renderer );
	
	if(m_fondo != NULL){
		SDL_RenderCopy( m_renderer, m_fondo , NULL, NULL );
	}
	//cargo figuras en el pantalla
	for(unsigned int i=0; i<figuras.size() ;i++){
		figuras[i]->render();
	}
	SDL_RenderPresent(m_renderer);
}

VistaEscenario::~VistaEscenario(void)
{
	for(unsigned int i=0; i<figuras.size() ;i++){
		delete figuras[i];
	}
	if(m_fondo !=NULL){
		SDL_DestroyTexture( m_fondo );
	}
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	IMG_Quit();

}

void VistaEscenario::cargarFiguras(){
	std::list<Figura*> poligonos, pelotas;
	poligonos = this->m_escenario->getPoligonos();
	pelotas = this->m_escenario->getPelotas();
	int total_pelotas = pelotas.size();
	int total_poligonos =poligonos.size();
	
	for(std::list<Figura*>::iterator it= pelotas.begin(); it != pelotas.end(); ++it){
		agregarPelota((Pelota*)(*it));
	}
	for(std::list<Figura*>::iterator it=poligonos.begin(); it != poligonos.end(); ++it){
		agregarPoligonos((Poligono*)(*it));
	}
	log("Figuras de la vista generadas:", DEBUG);
	std::string msg ="Circulos generados: " + EventLogger::itos(total_pelotas);
	msg.append(" Poligonos generados: "+ EventLogger::itos(total_poligonos));
	log(msg, DEBUG);
}


void VistaEscenario::agregarPelota(Pelota* pelota){
	this->figuras.push_back(new VistaCirculo(m_renderer,pelota,this->m_datos_pantalla));
}

void VistaEscenario::agregarPoligonos(Poligono* poligono){
	this->figuras.push_back(new VistaPoligono(m_renderer,poligono,this->m_datos_pantalla));
}

bool VistaEscenario::agregarJugador(Jugador* jugador){
	VistaJugador* v_jugador= new VistaJugador(m_renderer,jugador,m_datos_pantalla);
	if( v_jugador->spriteOk() == false){
		delete v_jugador;
		return false;
	}else{
		this->figuras.push_back(v_jugador);
	}
	return true;
}

void VistaEscenario::agregarPelota(DatosCirculo* pelota){
	this->figuras.push_back(new VistaCirculo(m_renderer,pelota,this->m_datos_pantalla));
}

void VistaEscenario::agregarPoligonos(DatosPoligono* poligono){
	this->figuras.push_back(new VistaPoligono(m_renderer,poligono,this->m_datos_pantalla));
}

bool VistaEscenario::agregarJugador(DatosJugador* jugador){
	VistaJugador* v_jugador= new VistaJugador(m_renderer,jugador,m_datos_pantalla);
	if( v_jugador->spriteOk() == false){
		delete v_jugador;
		return false;
	}else{
		this->figuras.push_back(v_jugador);
	}
	return true;
}