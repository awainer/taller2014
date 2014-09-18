#include "ControladorJugador.h"
#include <iostream>

ControladorJugador::ControladorJugador(Jugador* jugador)
{
	
	this->m_jugador = jugador;
	//this->m_keys = SDL_GetKeyboardState(NULL);
	bloqueoizq = false;
	bloqueoder = false ;
}

void ControladorJugador::actualizar(){
	/*SDL_Event m_evento; 
	SDL_PollEvent( &m_evento);
	switch(m_evento.type)
	{
	case SDL_KEYDOWN:
		sc = m_evento.key.keysym.scancode;
		switch(sc)
		{
		case SDL_SCANCODE_LEFT:
			n++;
			m_jugador->moverIzquierda();
			std::cout << " presiono izq " <<  n << std::endl;
			break;
		case SDL_SCANCODE_RIGHT:
			m_jugador->moverDerecha();
			std::cout << " presiono der" << std::endl;
			break;
		case SDL_SCANCODE_UP:
			m_jugador->saltar();
			std::cout << " presiono saltar" << std::endl;
			SDL_PumpEvents();
			break;
		default:
			m_jugador->frenar();
			break;
		}
	

		//se ejecuta instruccion mientras la tecla esta presionada
		break;
	case SDL_KEYUP:
		//se ejecuta instruccion cuando la tecla deja de ser presionada
		sc = m_evento.key.keysym.scancode;
		switch(sc)
		{
		case SDL_SCANCODE_LEFT:
			m_jugador->frenar();
			std::cout << " solto izq " <<std::endl;
			break;
		case SDL_SCANCODE_RIGHT:
			m_jugador->frenar();
			std::cout << " solto der" << std::endl;
			break;
		case SDL_SCANCODE_UP:
			break;
		default:
			break;
		}
		break;
	default:
			break;
	}
	*/
	SDL_PumpEvents();
	this->m_keys = SDL_GetKeyboardState(NULL);
	if(!m_keys[SDL_SCANCODE_LEFT])
		this->bloqueoder=false;
	if(!m_keys[SDL_SCANCODE_RIGHT])
		this->bloqueoizq=false;
	if(m_keys[SDL_SCANCODE_UP] || m_keys[SDL_SCANCODE_LEFT] || m_keys[SDL_SCANCODE_RIGHT]){

		if (m_keys[SDL_SCANCODE_UP])
		{
			this->m_jugador->saltar();
			this->bloqueoder=false;
			this->bloqueoizq=false;
		}
		if (m_keys[SDL_SCANCODE_LEFT] && this->bloqueoizq == false)
		{
				this->m_jugador->moverIzquierda();
				this->bloqueoder= true;
		}
		if (m_keys[SDL_SCANCODE_RIGHT] && this->bloqueoder == false)
		{		
				this->m_jugador->moverDerecha();
				this->bloqueoizq = true;
		}
	}else{
		this->bloqueoder=false;
		this->bloqueoizq=false;
	}
}

ControladorJugador::~ControladorJugador(void)
{
}
