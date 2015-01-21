#pragma once
#include "IRoundState.h"

class RoundFinishedState :	public IRoundState
{
public:
	RoundFinishedState();
	~RoundFinishedState(){}

	void Handle(GameRunningState& context, GameManager& gm);
	eCharacterCard currentRole() { return eCharacterCard(0); }
};

