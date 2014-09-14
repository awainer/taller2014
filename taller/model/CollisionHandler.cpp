#include "CollisionHandler.h"
#include <iostream>
#include "Jugador.h"
#include "constantes.h"
CollisionHandler::CollisionHandler(void){}
CollisionHandler::~CollisionHandler(void){}

void CollisionHandler::BeginContact(b2Contact* contact){
	//std::cout << "colision entre "  << std::endl << A->GetBody()->GetPosition().x <<  A->GetBody()->GetPosition().y << std::endl;
	//std::cout <<  B->GetBody()->GetPosition().x <<  B->GetBody()->GetPosition().y << std::endl;
	 if (!contact->IsTouching())
		return;
	Figura * figA  = (Figura*)(contact->GetFixtureA()->GetBody()->GetUserData());
	Figura * figB  = (Figura*)(contact->GetFixtureB()->GetBody()->GetUserData());
	int typeA = int(contact->GetFixtureA()->GetUserData());
	int typeB = int(contact->GetFixtureB()->GetUserData());

	 // No me interesa otra cosa que el FOOT_SENSOR por el momento
	if ( typeA != FOOT_SENSOR && typeB != FOOT_SENSOR)
		return;
	if (typeA == FOOT_SENSOR){
		((Jugador*) figA)->sumarContacto();
	}
	else if(typeB == FOOT_SENSOR){
		((Jugador*) figB)->sumarContacto();
	}

}

void CollisionHandler::EndContact(b2Contact* contact){
	Figura * figA  = (Figura*)(contact->GetFixtureA()->GetBody()->GetUserData());
	Figura * figB  = (Figura*)(contact->GetFixtureB()->GetBody()->GetUserData());
	int typeA = int(contact->GetFixtureA()->GetUserData());
	int typeB = int(contact->GetFixtureB()->GetUserData());

	if ( typeA != FOOT_SENSOR && typeB != FOOT_SENSOR)
		return;
	if (typeA == FOOT_SENSOR){
		((Jugador*) figA)->restarContacto();
	}
	else if(typeB == FOOT_SENSOR){
		((Jugador*) figB)->restarContacto();
	}
}
