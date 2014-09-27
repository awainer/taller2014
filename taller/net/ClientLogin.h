#pragma once
#include "packet.h"
class ClientLogin :
	public Packet
{
public:
	ClientLogin(void);
	~ClientLogin(void);
	char user[20];
};

