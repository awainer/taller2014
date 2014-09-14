#include "CoordenadasR2.h"


CoordenadasR2::CoordenadasR2(float x, float y)
{
	this->x = x;
	this->y = y;
}

std::string CoordenadasR2::str(){
	//yay c++!
	return " (" + std::to_string(long double(this->x)) + ", " + std::to_string(long double(this->y)) + ") ";
}

CoordenadasR2::~CoordenadasR2(void)
{
}
