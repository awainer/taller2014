#include "CollisionHandler.h"
#include <iostream>
#include "Jugador.h"
#include "constantes.h"
CollisionHandler::CollisionHandler(void){}
CollisionHandler::~CollisionHandler(void){}

void CollisionHandler::BeginContact(b2Contact* contact){
	b2Fixture * A = contact->GetFixtureA();
	b2Fixture * B = contact->GetFixtureB();
	if ((int)A->GetUserData() == FOOT_SENSOR){
		((Jugador*) A->GetBody()->GetUserData())->sumarContacto();
		std::cout << "begin contact A" << std::endl;
	}
	else if((int)B->GetUserData() == FOOT_SENSOR){
		((Jugador*) B->GetBody()->GetUserData())->sumarContacto();
		std::cout << "begin contact B" << std::endl;
	}

}

void CollisionHandler::EndContact(b2Contact* contact){
	b2Fixture * A = contact->GetFixtureA();
	b2Fixture * B = contact->GetFixtureB();
	if ((int)A->GetUserData() == FOOT_SENSOR){
		((Jugador*) A->GetBody()->GetUserData())->restarContacto();
		std::cout << "end contact A" << std::endl;
	}
	else if((int)B->GetUserData() == FOOT_SENSOR){
		((Jugador*) B->GetBody()->GetUserData())->restarContacto();
		std::cout << "end contact B" << std::endl;
	}}
