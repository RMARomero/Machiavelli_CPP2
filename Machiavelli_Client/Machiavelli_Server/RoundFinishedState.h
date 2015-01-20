#pragma once
#include "IRoundState.h"
class RoundFinishedState :
	public IRoundState
{
public:
	RoundFinishedState();
	void Handle(GameRunningState& context, GameManager& gm);
	~RoundFinishedState();

	eCharacterCard currentRole() { return eCharacterCard(0); }
};

