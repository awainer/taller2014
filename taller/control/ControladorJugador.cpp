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
