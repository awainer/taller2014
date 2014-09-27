#pragma once
#include "packet.h"
class LoginResponse :
	public Packet
{
public:
	LoginResponse(void);
	~LoginResponse(void);
	bool success;
	char msg[200];
};

