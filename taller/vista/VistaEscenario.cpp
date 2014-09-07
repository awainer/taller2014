#include "VistaEscenario.h"


VistaEscenario::VistaEscenario(Escenario* escenario , DatosPantalla* datos)
{
	m_ancho = datos->getAnchoPixel();
	m_alto = datos->getAltoPixel();
	m_fondo =NULL;
	if( iniciarSDL() == false){
		std::cout << "no inicio SDL" << std::endl;
	}
	else
	{
		m_escenario = escenario;
		m_datos_pantalla = datos;
		
		this->cargarFiguras();
	}
}

bool VistaEscenario::iniciarSDL() { 
	//Initialization flag 
	bool success = true; 
	//Initialize SDL 
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) 
	{ 
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false; 
	} else { 
		//window 640x480
		m_window = SDL_CreateWindow( "TP taller", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_ancho, m_alto, SDL_WINDOW_SHOWN );
		if( m_window == NULL ) 
		{ 
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() ); 
			success = false; 
		} else { //creo renderer
			m_renderer = SDL_CreateRenderer( m_window , -1, SDL_RENDERER_SOFTWARE); 
			if( m_renderer == NULL )
			{
					printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() ); 
					success = false; 
			}
			else { 
				
				//Inicializo SDL_IMAGE 
				int imgFlags = IMG_INIT_JPG|IMG_INIT_PNG; 
				if( !( IMG_Init( imgFlags ) & imgFlags ) ) 
				{ 
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false; 
				} 
			}
		} 
	} 
	return success; 
}


void VistaEscenario::agregarFondo(std::string path){
	
	if(m_fondo != NULL){
		SDL_DestroyTexture( m_fondo );
	}
	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        m_fondo = SDL_CreateTextureFromSurface( m_renderer, loadedSurface );
		if( m_fondo == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
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
	for(int i=0; i<figuras.size() ;i++){
		figuras[i]->render();
	}
	SDL_RenderPresent(m_renderer);
}

VistaEscenario::~VistaEscenario(void)
{
	for(int i=0; i<figuras.size() ;i++){
		delete figuras[i];
	}
	if(m_fondo !=NULL){
		std::cout << " entro a destruir fondo" << std::endl;
		SDL_DestroyTexture( m_fondo );
	}
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	IMG_Quit();
	SDL_Quit();
}

void VistaEscenario::cargarFiguras(){
	int total_pelotas =m_escenario->getPelotas().size();
	int total_poligonos =m_escenario->getPoligonos().size();
	for(int i=0; i < total_pelotas ; i++){
		agregarPelota(m_escenario->getPelotas()[i]);
	}
	for(int j=0; j < total_poligonos; j++){
		agregarPoligonos((Poligono*)m_escenario->getPoligonos()[j]);
	}
}


void VistaEscenario::agregarPelota(Pelota* pelota){
	this->figuras.push_back(new VistaCirculo(m_renderer,pelota,this->m_datos_pantalla));
}

void VistaEscenario::agregarPoligonos(Poligono* poligono){
	this->figuras.push_back(new VistaPoligono(m_renderer,poligono,this->m_datos_pantalla));
}

void VistaEscenario::agregarJugador(Jugador* jugador){
	this->figuras.push_back(new VistaJugador(m_renderer,jugador,m_datos_pantalla));
}