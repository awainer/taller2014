#pragma once

class Color
{
public:
	Color(unsigned char a,unsigned char r,unsigned char  g,unsigned char b);
	Color(unsigned char r,unsigned char  g,unsigned char b);
	Color();
	unsigned char a,r,g,b;
	~Color(void);
};

