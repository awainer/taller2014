#pragma once
#include "Packet.h"
class ClientEvent :
	public Packet
{
public:
	ClientEvent(void);
	~ClientEvent(void);
	unsigned int action;
};

