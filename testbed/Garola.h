/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef GAROLA_H
#define GAROLA_H
#include "Poligono.h"
#include "Pelota.h"
#include "Jugador.h"
// This tests distance joints, body destruction, and joint destruction.
class Garola : public Test
{
public:
	Jugador * j;
	Garola()
	{
		Poligono * p = new Poligono(-8,-3.5,5,6,45,m_world);
		//Poligono * q = new Poligono(4,1,2,4,45,m_world);
		Pelota * pe = new Pelota(0,8,0.7,m_world);
		j = new Jugador(0,5,m_world);

		b2BodyDef bodyDef;
		b2FixtureDef fixtureDef;
		b2EdgeShape shape;
		bodyDef.type=b2_staticBody;
		shape.Set(b2Vec2(-100,0),b2Vec2(100,0));
		fixtureDef.shape=&shape;

		b2Body * piso = m_world->CreateBody(&bodyDef);
		piso->CreateFixture(&fixtureDef);

	}
	void Keyboard(unsigned char key)
	{
		switch (key)
		{

		case 'a':
			{
				j->moverIzquierda();
			}
			break;

		case 'd':
			{
				j->moverDerecha();
			}
			break;
		case 'w':
			{
				j->saltar();
			}
			break;
		}
	}
	static Test* Create()
	{
		return new Garola;
	}

	/*b2Body* m_bodies[4];
	b2Joint* m_joints[8];*/
};

#endif
