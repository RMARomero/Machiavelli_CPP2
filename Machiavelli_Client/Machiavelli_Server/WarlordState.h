#pragma once
#include "IRoundState.h"
class WarlordState :
	public IRoundState
{
public:
	WarlordState();
	void Handle(GameRunningState& context, GameManager& gm);
	eCharacterCard currentRole();
	~WarlordState();
};

