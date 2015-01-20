#pragma once
#include "IGameState.h"
class LobbyState :
	public IGameState
{
public:
	LobbyState();
	void Handle(GameManager& gm);
	virtual ~LobbyState();
};

