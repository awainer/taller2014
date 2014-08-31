#include "Figura.h"


Figura::Figura(void)
{
}


Figura::~Figura(void)
{
	this->world->DestroyBody(this->body);
}
