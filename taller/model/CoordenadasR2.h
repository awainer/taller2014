#pragma once
#include <string>
class CoordenadasR2
{
public:
	CoordenadasR2(float x, float y);
	float x,y;
	~CoordenadasR2(void);
	std::string str();
};

