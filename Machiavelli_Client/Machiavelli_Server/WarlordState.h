#pragma once
#include "IRoundState.h"
class WarlordState :
	public IRoundState
{
public:
	WarlordState();
	~WarlordState(){}
	void Handle(GameRunningState& context, GameManager& gm);
	eCharacterCard currentRole() { return Warlord; }
};

