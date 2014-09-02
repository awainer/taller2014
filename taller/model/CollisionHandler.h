#pragma once


#include "../Box2D/Box2D.h"

class CollisionHandler :
	public b2ContactListener
{
public:
	CollisionHandler(void);
	~CollisionHandler(void);
};

