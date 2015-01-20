#pragma once
#include "IRoundState.h"
class KingState :
	public IRoundState
{
public:
	KingState();
	void Handle(GameRunningState& context, GameManager& gm);
	eCharacterCard currentRole();
	~KingState();
};

