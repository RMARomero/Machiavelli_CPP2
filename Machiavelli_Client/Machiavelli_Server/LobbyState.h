#pragma once
#include "IGameState.h"

class LobbyState : public IGameState
{
public:
	LobbyState(){}
	virtual ~LobbyState(){}

	void Handle(GameManager& gm);
};

