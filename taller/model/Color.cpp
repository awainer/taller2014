#include "Color.h"


Color::Color()
{
	this->a = 0;
	this->r = 0;
	this->g = 0;
	this->b = 0;
}

Color::Color(unsigned char a,unsigned char r,unsigned char  g,unsigned char b)
{
	this->a = a;
	this->r = r;
	this->g = g;
	this->b = b;
}

Color::Color(unsigned char r,unsigned char  g,unsigned char b)
{
	this->a = 255;
	this->r = r;
	this->g = g;
	this->b = b;
}

std::string Color::str(){
	std::string s = "( " + std::to_string((long long)this->r) + " " + std::to_string((long long)this->g) + " " + std::to_string((long long)this->b) + " )";
	return s;
}
Color::~Color(void)
{
}
