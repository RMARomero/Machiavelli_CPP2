#pragma once
#include "IRoundState.h"
class GameRunningState;
class BishopState :
	public IRoundState
{
public:
	BishopState();
	void Handle(GameRunningState& context, GameManager& gm);
	eCharacterCard currentRole();
	~BishopState();
};

