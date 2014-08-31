#include "Rectangulo.h"
#include  <Box2d/Box2d.h>

// x e y se refieren a la posicion del centro de masa
Rectangulo::Rectangulo(unsigned int x, unsigned int y, unsigned int alto, unsigned int ancho, b2World * world, bool dinamico)
{
	this->world = world;

	b2BodyDef bd;
	b2FixtureDef fixtureDef;

	bd.position.Set(x,y);

	if (dinamico){
		bd.type = b2_dynamicBody;
		fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.5f;
        fixtureDef.restitution = 1.0f;
	}
	else
		bd.type = b2_staticBody;
		
	this->body = this->world->CreateBody(&bd);
	b2PolygonShape shape;
	shape.SetAsBox(alto/2,ancho/2); //,b2Vec2(x,y)
	fixtureDef.shape = &shape;
	this->body->CreateFixture(&fixtureDef);

}


Rectangulo::~Rectangulo(void)
{
}
