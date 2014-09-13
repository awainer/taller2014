#include "CollisionHandler.h"
#include <iostream>
#include "Jugador.h"
#include "constantes.h"
CollisionHandler::CollisionHandler(void){}
CollisionHandler::~CollisionHandler(void){}

void CollisionHandler::BeginContact(b2Contact* contact){
	b2Fixture * A = contact->GetFixtureA();
	b2Fixture * B = contact->GetFixtureB();
	//std::cout << "colision entre "  << std::endl << A->GetBody()->GetPosition().x <<  A->GetBody()->GetPosition().y << std::endl;
	//std::cout <<  B->GetBody()->GetPosition().x <<  B->GetBody()->GetPosition().y << std::endl;
	 if (!contact->IsTouching())
		return;

	 // No me interesan las paredes
	if ((int)A->GetUserData() == LEFT_WALL ||
		(int)A->GetUserData() == RIGHT_WALL||
		(int)B->GetUserData() == LEFT_WALL ||
		(int)B->GetUserData() == RIGHT_WALL)
			return;


	if ((int)A->GetUserData() == FOOT_SENSOR){
		((Jugador*) A->GetBody()->GetUserData())->sumarContacto();
		//std::cout << "begin contact A" << std::endl;
	}
	else if((int)B->GetUserData() == FOOT_SENSOR){
		((Jugador*) B->GetBody()->GetUserData())->sumarContacto();
		//std::cout << "begin contact B" << std::endl;
	}

}

void CollisionHandler::EndContact(b2Contact* contact){
	b2Fixture * A = contact->GetFixtureA();
	b2Fixture * B = contact->GetFixtureB();

	// No me interesan las paredes
	if ((int)A->GetUserData() == LEFT_WALL ||
		(int)A->GetUserData() == RIGHT_WALL||
		(int)B->GetUserData() == LEFT_WALL ||
		(int)B->GetUserData() == RIGHT_WALL)
			return;

	if ((int)A->GetUserData() == FOOT_SENSOR && !contact->IsTouching()){
		((Jugador*) A->GetBody()->GetUserData())->restarContacto();
		//std::cout << "end contact A" << std::endl;
	}
	else if((int)B->GetUserData() == FOOT_SENSOR && !contact->IsTouching()){
		((Jugador*) B->GetBody()->GetUserData())->restarContacto();
		//std::cout << "end contact B" << std::endl;
	}
}
