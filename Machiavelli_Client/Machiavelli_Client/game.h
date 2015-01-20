#pragma once
#include "Socket.h"

class game
{
public:
	game();
	~game();
private:
	char* m_IP;
	int m_Portnumber;

	void storeServerInformation();
};

